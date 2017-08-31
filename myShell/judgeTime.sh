#!/bin/sh

resultSavedFile=jugerTResult
fileToFind=result*

PERIOD=105000
DEVIATION=10

MIN=$[$PERIOD-$DEVIATION]
MAX=$[$PERIOD+$DEVIATION]

if [ -f "$resultSavedFile" ];then
    rm -f "$resultSavedFile"
fi

for files in $fileToFind
do
    chnIdBegin=`echo "$files" | cut -d'-' -f 2`
    chnIdEnd=`echo "$files" | cut -d'-' -f 3`
    for chnId in $(seq $chnIdBegin $chnIdEnd)
    do
        myTimes=`cat "$files" | grep "^$chnId" | cut -d" " -f 2,4,5`
        for period in $myTimes
        do
            if [ $period -lt 256 ];then
                label=$period
                continue
            fi
            if [ $period -gt $MAX ] || [ $period -lt $MIN ];then
                printf "label:%-3d  chnId:%-3d  period:%-7d $files\n" "$label" "$chnId" "$period"  >>"$resultSavedFile"
#                echo "label:$label  chnId:$chnId  period:$period   $files">>"$resultSavedFile"
            fi
        done
    done
done

