#!/bin/bash
ldd $1 >/dev/null 2>&1
if [[ 1 -eq $? ]];then
echo "Please call with a dynamic executable file."
exit 0
fi
libPath="$(dirname $1)/lib"
if [[ ! -d "$libPath" ]];then
mkdir "$libPath"
fi
ldd $1 | grep -o "/.*/[^[:space:]]*" | xargs -i cp {} "$libPath"
