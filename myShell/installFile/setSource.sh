#!/bin/bash
ubuntuVersion=`cat /etc/issue | grep -o "[0-9]*\.[0-9]*"`
sudo cp "sources/$ubuntuVersion" /etc/apt/sources.list
