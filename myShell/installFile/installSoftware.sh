#!/bin/bash
readonly aptFile="softListTmp"

#放置安装文件
readonly installPath="$HOME/installFile"
if [[ ! -d $installPath ]];then
    mkdir "$installPath"
fi

#日志信息
readonly LoggingFile="$HOME/install.log"
touch "$LoggingFile"
exec 2> "$LoggingFile"

#首先删除不必要的软件
sudo apt-get remove libreoffice-common thunderbird totem rhythmbox simple-scan aisleriot gnome-mines cheese transmission-common gnome-orca gnome-sudoku deja-dup -y
sudo apt autoremove -y

#开始安装文件列表中软件
while read -r Line 
do
    for soft in $Line
    do
        sudo apt-get install "$soft" -y
        if [[ $? ]];then
            echo "Install $soft Fail" >&2
        fi
    done
done < $aptFile

#把源设置为清华大学源
cd sources && sudo ./setSource.sh
sudo apt-get update -y
sudo apt-get upgrade -y
sudo apt-get dist-upgrade -y
sudo apt autoremove -y

#搜狗输入法
#官网下载，使用dpkg -i命令安装，再sudo apt install -f
#设置模式从 ibus 到 fcitx，重登录，搜索fcitx configure，打开，添加搜狗输入法

#网易云音乐
wget http://s1.music.126.net/download/pc/netease-cloud-music_1.0.0-2_amd64_ubuntu16.04.deb -P "$installPath"/ && cd "$installPath" && sudo dpkg -i netease-cloud-music*.deb
sudo apt install -f -y

#安装docky, 一个底部图标栏
sudo add-apt-repository ppa:docky-core/stable -y
sudo apt-get update -y
sudo apt-get install docky -y

#安装vim配置文件
curl https://j.mp/spf13-vim3 -L > spf13-vim.sh && sh spf13-vim.sh

#python
#1.pyenv，python环境管理
git clone https://github.com/pyenv/pyenv.git ~/.pyenv
echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.bashrc
echo 'export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.bashrc
echo -e 'if command -v pyenv 1>/dev/null 2>&1; then\n  eval "$(pyenv init -)"\nfi' >> ~/.bashrc
#2.安装python3.6
pyenv install 3.6.3
pip install autoenv
echo "source `which activate.sh`" >> ~/.bashrc

#更新ipv6 host
wget https://raw.githubusercontent.com/lennylxx/ipv6-hosts/master/hosts -P "$installPath"/ && cd $installPath/ && sudo cp hosts /etc/hosts && rm hosts

#lantern，翻墙
wget https://raw.githubusercontent.com/getlantern/lantern-binaries/master/lantern-installer-64-bit.deb -P "$installPath" && cd $installPath/ && sudo dpkg -i lantern-installer*.deb

#安装autojump
rm -rf "$installPath"/autojump && git clone git://github.com/joelthelion/autojump.git "$installPath"/autojump && cd "$installPath"/autojump && ./install.py
echo '[[ -s /home/zj/.autojump/etc/profile.d/autojump.sh ]] && source /home/zj/.autojump/etc/profile.d/autojump.sh' >> $HOME/.bashrc
#终端的颜色表
wget -O xt  http://git.io/v3Dll && chmod +x xt && ./xt && rm xt
#安装oh-my-git
rm -rf ~/.oh-my-git && git clone https://github.com/arialdomartini/oh-my-git.git ~/.oh-my-git && echo 'source ~/.oh-my-git/prompt.sh' >> ~/.bashrc
#oh-my-git需要的字体，需手动设置终端字体为SourceCodePro+Powerline+Awesome Regular
cd /tmp && git clone http://github.com/gabrielelana/awesome-terminal-fonts && cd awesome-terminal-fonts && git checkout patching-strategy && mkdir -p ~/.fonts && cp patched/*.ttf ~/.fonts
sudo fc-cache -fv ~/.fonts
