#!/bin/bash

EDF=`echo "tst-*"`

for i in $EDF
do
gcc $i -o l
./l
done
