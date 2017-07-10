#!/bin/sh

for i in $(seq 0 22)
do
    sh exceptions/$i.sh > exceptions/$i.out
    diff exceptions/$i.out exceptions/$i.ans
    if [ $? = 0 ]; then
        echo "exception $i: Accepted"
    else
        echo "exception $i: Wrong Answer"
    fi
done
