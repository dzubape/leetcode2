#!/bin/bash

FILE_ONE=$1
FILE_TWO=$2

if [ `md5sum $FILE_ONE -z | awk '{print $1}'`  == `md5sum $FILE_TWO -z | awk '{print $1}'` ]
then
    echo '>> equal'
else
    echo '>> non-equal'
fi