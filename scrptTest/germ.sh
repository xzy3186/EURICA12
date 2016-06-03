#!/bin/bash

echo Start at run no,:

read RUNSTART

echo End at run no.: 

read RUNEND 

for (( RUNNUM = ${RUNSTART} ; RUNNUM < ${RUNEND}+1 ; RUNNUM = ${RUNNUM}+1 ))
do
    if [ -f /raid/01/home/ur12/lmdfiles/ni78data/run_${RUNNUM}.lmd ] ;then 
	echo Unpacking run number: ${RUNNUM}
	go4analysis -lib /raid/01/home/ur12/analysis/users/frank/Go4EURICA/libGo4UserAnalysis.so -disable-asf -file /raid/01/home/ur12/analysis/users/frank/go4/lmdfiles/pd128data/run_${RUNNUM}.lmd 
	mv -f go4.root ~/treefiles/euroball/go4_${RUNNUM}.root
    fi 
done
