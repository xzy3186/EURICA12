#!/bin/sh

function mapp() {
#  This is from, http://prll.sourceforge.net/shell_parallel.html
  if [[ -z $MAPP_NR_CPUS ]] ; then
#	local MAPP_NR_CPUS=$(grep "processor	:" < /proc/cpuinfo | wc -l)
#   max core for calculation; modified by Toshiyuki Sumikama
      local MAPP_NR_CPUS=4
  fi
  local mapp_pid=$(exec bash -c 'echo $PPID')
  local mapp_funname=$1
  local -a mapp_params
  mapp_params=("$@")
#   mapp_nr_args; modified by Toshiyuki Sumikama
#  local mapp_nr_args=${#mapp_params[@]}
  local mapp_nr_args=`expr ${#mapp_params[@]} - 1`
  local mapp_current=0
  function mapp_trap() {
#	echo "MAPP PROGRESS: $((mapp_current*100/mapp_nr_args))%" 1>&2
	if [[ $mapp_current -lt $mapp_nr_args ]] ; then
	    let mapp_current+=1
	    (
		$mapp_funname "${mapp_params[$mapp_current]}"
		kill -USR1 $mapp_pid
	    ) &
	fi
  }

  trap mapp_trap SIGUSR1
  while [[ $mapp_current -lt $mapp_nr_args ]]; do
	wait
	if [[ $mapp_current -lt $mapp_nr_args && $? -lt 127 ]] ; then
	    sleep 1
	    local mapp_tmp_count=$mapp_current
	    wait
	    if [[ $mapp_tmp_count -eq $mapp_current ]] ; then
		echo "   MAPP_FORCE" 1>&2
		for i in $(seq 1 ${MAPP_NR_CPUS}) ; do
		    mapp_trap
		done
	    fi
	fi
  done
  for i in $(seq 1 ${MAPP_NR_CPUS}) ; do
	wait
  done
  trap - SIGUSR1
  unset -f mapp_trap
}

myfun()
{
(
    cd /home/ribf10/analysis/users/xuzy/script_123rh
    #nice ./WASABI2Tr $1 >> /dev/null
    #nice ./DSSDGeMerge $1 $1 >> /dev/null
    #nice ./separate $1 $1 >> /dev/null
    #nice ./BuildDecay $1 >> /dev/null
    #nice ./MakeGGMatrixDecay $1 >> /dev/null
    #nice ./MakeGGMatrix $1 >> /dev/null
    #./WASABI2Tr $1 >> /dev/null
    #./DSSDGeMerge $1 $1 >> /dev/null
    ./separate $1 $1 >> /dev/null
    ./BuildDecay $1 >> /dev/null
    #./MakeGGMatrixDecay $1 >> /dev/null
    #./MakeGGMatrix $1 >> /dev/null
    echo $1' was finished.'
)
}

for eachrun in {4041..4042}
do
    list=$list' '$eachrun
done

echo $list
#anarootlogin
source /home/ribf10/analysis/scripts/anarootlogin.sh xuzy >> /dev/null

(mapp myfun $list)

