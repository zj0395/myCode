#!/bin/bash

WRONG_NOFILE="Please Call With At Least One Parameter."
if [[  -z "$1" ]];then
    echo $WRONG_NOFILE
    exit 0
fi

for file in $*
do
    if [ ! -f $file ];then
        cat>>$file<<EOF
#!/bin/bash
#Author:
#Date & Time: `date +"%F %T"`
#Description:

EOF
    fi
vi +5 $file
done
