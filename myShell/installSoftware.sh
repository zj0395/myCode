#!/bin/bash

#放置安装文件
installPath="~/installFile"
mkdir $installFile
#日志信息
LoggingFile="~/install.log"
exec 2>$LoggingFile

#首先删除不必要的软件
sudo apt-get remove libreoffice-common unity-webapps-common thunderbird totem rhythmbox empathy brasero simple-scan gnome-mahjongg aisleriot gnome-mines cheese transmission-common gnome-orca webbrowser-app gnome-sudoku  landscape-client-ui-install onboard deja-dup
sudo apt autoremove

#把源设置为阿里云源
sudo ./installFile/setSource.sh
sudo apt-get update
sudo apt-get upgrade
sudo apt-get dist-upgrade
sudo apt autoremove


#安装vim
sudo apt-get install vim
#安装vim配置文件
wget -qO- https://raw.github.com/ma6174/vim/master/setup.sh | sh -x
cp installFile/.vimrc ~/.vimrc


#开始安装python相关
#1.pyenv，python环境管理
git clone https://github.com/pyenv/pyenv.git ~/.pyenv
echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.bashrc
echo 'export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.bashrc
echo -e 'if command -v pyenv 1>/dev/null 2>&1; then\n  eval "$(pyenv init -)"\nfi' >> ~/.bashrc
#2.安装python3.6
sudo pyenv install 3.6.1
#3.安装python测试相关
sudo apt-get install python-nose


#安装chromium
sudo apt-get install chromium-browser
#安装菜单指示器
sudo apt-get install syspeek
#安装git
sudo apt-get install git
#安装ExFat文件系统驱动
sudo apt-get install exfat-fuse
#安装unrar
sudo apt-get install unrar
#安装markdown编辑器
sudo apt-get install moeditor
#安装tumx
sudo apt-get install tmux
#安装lantern，翻墙软件
sudo apt-get install lantern
#安装wps
sudo apt-get install wps-office
#安装autojump
git clone git://github.com/joelthelion/autojump.git $installPath/autojump && cd $installPath/autojump && ./install.py
#安装oh-my-git
git clone https://github.com/arialdomartini/oh-my-git.git ~/.oh-my-git && echo source ~/.oh-my-git/prompt.sh >> ~/.bashrc

