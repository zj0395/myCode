#!/bin/bash
readonly defaultFromPath=~/myMd/
readonly defaultToPath=~/myBlog/blog/web/md

if [[ $# -ge 1 ]];then
    fromPath=$1
fi
if [[ $# -ge 2 ]];then
    toPath=$2
fi

#使用-d选项时的默认路径
while getopts ":d" opt
do
    fromPath=$defaultFromPath
    toPath=$defaultToPath
done

#检查错误信息
if [[ $fromPath == "" ]] || [[ $toPath == "" ]];then
    echo Please call with fromPath and toPath.
    echo Or \"-d\" to use default path.
    exit
fi
if [[ ! -d $fromPath ]];then
    echo Sorry, \""$fromPath"\" is not a vaild path.
    exit
fi

function linkPath()
{
    if [ ! -d $2 ];then
        mkdir $2
    fi
    files=`cd $1;ls`
    for file in $files
    do
        if [ -d $1/$file ];then
            linkPath $1/$file $2/$file
        fi
        if [ -f $1/$file ];then
            linkFile $1/$file $2/$file
        fi
    done
}
function linkFile()
{
    if [ ! -f $2 ];then
        ln $1 $2
    fi
}
function checkPath()
{
    if [ ! -d $1 ];then
        rm -r $2
        return
    fi
    files=`cd $2;ls`
    for file in $files
    do
        if [ -d $2/$file ];then
            checkPath $1/$file $2/$file
        fi
        if [ -f $2/$file ];then
            checkFile $1/$file $2/$file
        fi
    done
}
function checkFile()
{
    if [ ! -f $1 ];then
        rm -f $2
    fi
}

linkPath $fromPath $toPath
checkPath $fromPath $toPath
