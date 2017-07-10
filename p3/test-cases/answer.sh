#!/bin/sh

for i in $(seq 0 22)
do
    sh exceptions/$i.sh > exceptions/$i.ans
done
