#!/bin/bash

function addIncludePath()
{
    allFiles=$(ls)
	for file in $allFiles
	do
	    if [[ -d $file  ]];then
	        Paths+=" $file "
	    fi
	done
}

nowPath=$(pwd)
fileName="$nowPath/makefile"
distargetName=test

while getopts ":r" opt 
do
    addIncludePath "$nowPath"
	for path in $Paths
	do
	    includePath+=" -I./$path/"
	done
done

exec 1>"$fileName"

echo -e "#This makefile is generate automatically."
echo -e "#You can change it free as you want."
echo -e ""
echo -e "DISTARGET = $distargetName"
echo -e "SRC = \$(wildcard *.cpp)"
for path in $Paths
do
    echo -e "SRC += \$(wildcard $path/*.cpp)"
done
echo -e "OBJECT = \$(SRC:.cpp=.o)"
echo -e "DEPENDENCE = \$(SRC:.cpp=.d)"
echo -e "INCLUDES =$includePath"
echo -e "LIBS = "
echo -e "CC = g++"
echo -e "CFLAGS = -Wall"
echo -e "LFLAGS = -Wall"
echo -e ""
echo -e "all : \$(DISTARGET)"
echo -e ""
echo -e "%.d : %.cpp"
#不要细看以下5行了，有三层转义字符，shell脚本一层，makefile一层，还有sed一层。它只是把依赖关系保存到.d文件里
echo -e "	@set -e;rm -f \$@;\\"
echo -e "	\$(CC) -MM \$(INCLUDES) \$< >\$@.\$\$\$\$;\\"
echo -e "	sed 's,\(\$*\)\.o[ :]*,\1.o \$@ : ,g' <\$@.\$\$\$\$ >\$@;\\"
echo -e "	rm -f \$@.\$\$\$\$"
echo -e ""
echo -e "\$(DISTARGET) : \$(OBJECT)"
echo -e "	\$(CC) \$(LFLAGS) -o \$@ $^"
echo -e ""
echo -e "sinclude \$(SRC:.cpp=.d)"
echo -e "%.o : %.cpp"
echo -e "	\$(CC) \$(INCLUDES) \$(CFLAGS) -c \$< -o \$@"
echo -e ""
echo -e ".PHONY:clean"
echo -e "clean:"
echo -e "	@rm -f \$(DISTARGET) \$(OBJECT) \$(DEPENDENCE)"
echo -e ""
