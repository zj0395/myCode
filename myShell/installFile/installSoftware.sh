#!/bin/bash
readonly aptFile="softList"
readonly pipFile="pipList"
readonly wgetFile="wgetList"
readonly ppaFile="ppaList"
readonly installPath="$HOME/installFile"
readonly preInstallPath="$installPath"/Pre
readonly LoggingFile="$HOME/install.log"


#日志信息
touch "$LoggingFile"
exec 2> "$LoggingFile"

#放置下载de soft
if [[ ! -d $installPath ]];then
    mkdir "$installPath"
fi

function update()
{
    sudo apt-get update -y
    sudo apt-get upgrade -y
}

#从网上下载安装包再安装的软件，文件中以 1 开头表示此包将在其它包之前安装
function wgetInstall()
{
    if [ -n "$installPath" ];then
        rm "$installPath"/*.deb
    fi
    while read -r Line
    do
        next=false
        Path="$installPath"
        url="$Line"
        for s in $Line
        do
            if [[ "$s" = "1"  ]];then
                Path="$preInstallPath"
                next=true
            fi
            if [ $next ];then
                url=$s;
            fi
        done
        wget "$url" -P "$Path"
        if [ $? ];then
            echo "Download $Line Fail" >&2
        fi
    done < $wgetFile
    cd "$preInstallPath" && sudo dpkg -i ./*.deb -y
    cd "$installPath" && sudo dpkg -i ./*.deb -y
    sudo apt-get install -f
    update
}

function ppaAdd()
{
	while read -r Line 
	do
        sudo add-apt-repository "$Line" -y
    done < $ppaFile
    update
}

#用pip安装的库
function  pipInstall()
{
	while read -r Line 
	do
	    for soft in $Line
	    do
	        pip install "$soft"
	        if [ $? ];then
	            echo "Pip Install $soft Fail" >&2
	        fi
	    done
	done < $pipFile
}

function pipAfterInstall()
{
    echo "source `which activate.sh`" >> ~/.bashrc
}

#用apt-get安装的软件
function aptInstall()
{
	while read -r Line 
	do
	    for soft in $Line
	    do
	        sudo apt-get install "$soft" -y
	        if [ $? ];then
	            echo "Install $soft Fail" >&2
	        fi
	    done
	done < "$aptFile"
	update
}

function removeSoft()
{
    sudo apt-get remove libreoffice-common thunderbird totem \
        rhythmbox simple-scan aisleriot cheese transmission-common\
        gnome-orca deja-dup -y
    sudo apt autoremove -y
}

function setSoftSource()
{
    #把源设置为清华大学源
    cd sources && sudo ./setSource.sh
    sudo apt-get update -y
    sudo apt-get upgrade -y
    sudo apt-get dist-upgrade -y
    sudo apt autoremove -y
}

function setVim()
{
    #安装vim配置文件
    curl https://j.mp/spf13-vim3 -L > spf13-vim.sh && sh spf13-vim.sh
}

function setPyenv()
{
    #1.pyenv，python环境管理
    git clone https://github.com/pyenv/pyenv.git ~/.pyenv
    echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.bashrc
    echo 'export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.bashrc
    echo -e 'if command -v pyenv 1>/dev/null 2>&1; then\n  eval "$(pyenv init -)"\nfi' >> ~/.bashrc
    #2.安装python3.6
    pyenv install 3.6.3
    #pip设为清华大学源
    mkdir ~/.pip
    echo "[global]
    index-url = https://pypi.tuna.tsinghua.edu.cn/simple
    [install]
    trusted-host = https://pypi.tuna.tsinghua.edu.cn/simple" > ~/.pip/pip.conf
}

function setHost()
{
    #更新ipv6 host
    wget https://raw.githubusercontent.com/lennylxx/ipv6-hosts/master/hosts -P "$installPath"/ &&\
        cd $installPath/ && sudo cp hosts /etc/hosts && rm hosts
}

function gitInstall()
{
    #安装autojump
    rm -rf "$installPath"/autojump && git clone git://github.com/joelthelion/autojump.git "$installPath"/autojump && cd "$installPath"/autojump && ./install.py
    echo '[[ -s /home/zj/.autojump/etc/profile.d/autojump.sh ]] && source /home/zj/.autojump/etc/profile.d/autojump.sh' >> $HOME/.bashrc
    #终端的颜色表
    wget -O xt  http://git.io/v3Dll && sudo chmod +x xt && sudo  ./xt && sudo rm xt
    #安装oh-my-git
    rm -rf ~/.oh-my-git && git clone https://github.com/arialdomartini/oh-my-git.git ~/.oh-my-git && echo 'source ~/.oh-my-git/prompt.sh' >> ~/.bashrc
    #oh-my-git需要的字体，需手动设置终端字体为SourceCodePro+Powerline+Awesome Regular
    cd /tmp && git clone http://github.com/gabrielelana/awesome-terminal-fonts &&\
        cd awesome-terminal-fonts && git checkout patching-strategy &&\
        mkdir -p ~/.fonts && cp patched/*.ttf ~/.fonts
    sudo fc-cache -fv ~/.fonts

    #tmux自动保存和恢复
    mkdir ~/.tmux
    cd ~/.tmux/ && \
        sudo git clone https://github.com/tmux-plugins/tmux-resurrect.git &&\
        echo "run-shell ~/.tmux/tmux-resurrect/reurrect.tmux" >> ~/.tmux.conf
}

#removeSoft
#setSoftSource
#setHost
#ppaAdd
#aptInstall
#wgetInstall
#setPyenv
#gitInstall
#pipInstall
#pipAfterInstall
#setVim

#搜狗输入法
#官网下载，使用dpkg -i命令安装，再sudo apt install -f
#设置模式从 ibus 到 fcitx，重登录，搜索fcitx configure，打开，添加搜狗输入法

