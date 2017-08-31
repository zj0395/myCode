#!/bin/sh

resultSavedFile=judgeAresult
fileToFind=result*
if [ -f "$resultSavedFile" ];then
    rm -f "$resultSavedFile"
fi

for files in $fileToFind
do
    chnIdBegin=`echo "$files" | cut -d'-' -f 2`
    chnIdEnd=`echo "$files" | cut -d'-' -f 3`
    for chnId in $(seq $chnIdBegin $chnIdEnd)
    do
        timesPreChn=0
        myDatas=`cat "$files" | grep "^$chnId" | cut -d' ' -f 2`
        for myData in $myDatas
        do
            timesPreChn=$[$timesPreChn+1]
            if [ $timesPreChn -eq 1 ];then
                myDataPre=$myData
                continue
            fi
            if [ ! $myData -eq $[$myDataPre+1] ];then
                printf "chnId:%-3d   Data:%-7d Last:%-7d $files\n" "$chnId" "$myData" "$myDataPre">>"$resultSavedFile"
#                echo "chnId:$chnId  Data:$myData   $files">>"$resultSavedFile"
            fi
            myDataPre=$myData
        done
    done
done
