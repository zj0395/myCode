#!/bin/bash
dirPath=$(dirname "$0")
basePath=$(cd "$dirPath"; pwd)
cd "$basePath"
for configFile in *.local
do
    dstFile=.$configFile
    cp "$configFile" ~/"$dstFile"
done
grep "source ~/.bashrc.local" ~/.bashrc > /dev/null
if [ $? -eq 1 ];then
    echo "source ~/.bashrc.local" >> ~/.bashrc
fi
