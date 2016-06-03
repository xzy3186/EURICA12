#!/bin/bash

for i in `cat calib.list`
do
   ./WASABI2Tr $i
   ./DSSDGeMerge $i $i
   ./DSSDGeCorr $i
done
