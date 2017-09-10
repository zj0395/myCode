#!/bin/bash

#安装vim配置文件
wget -qO- https://raw.github.com/ma6174/vim/master/setup.sh | sh -x;
cp installFile/.vimrc ~/.vimrc;

#开始安装python相关
sudo apt-get install python-nose;
