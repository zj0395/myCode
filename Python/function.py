#!/usr/bin/env python
# coding=utf-8

from subprocess import Popen, PIPE
from urllib.request import urlopen
from bs4 import BeautifulSoup
from configparser import ConfigParser

def tidyTest():
    '''用来规范HTML代码'''
    text = open("testFile/function-messy.html", 'rb').read()
    tidy = Popen('tidy', stdin=PIPE, stdout=PIPE, stderr=PIPE)
    
    tidy.stdin.write(text)
    tidy.stdin.close()
    
    print( tidy.stdout.read().decode('utf-8') )

def BeautifulSoupTest():
    '''用来不关心HTML格式和混乱程度来读取数据'''

    url = 'http://python.org/jobs'
    urlHome = 'http://python.org'

    text = urlopen('http://python.org/jobs').read().decode('utf-8')
    soup = BeautifulSoup(text, 'html.parser')

    jobs = set()
    for header in soup('h2'):
        links = header('a')
        if not links : continue
        link = links[0]
        jobs.add('%s(%s%s)' % (link.string, urlHome, link['href']))

    print( '\n'.join( sorted( jobs, key = lambda x: x.lower() ) ) )

def ConfigParserTest():
    CONFIGFILE = 'testFile/function-test.ini'
    config = ConfigParser()
    #读取配置文件
    config.read(CONFIGFILE)

    #访问 message 区段下的 greeting 的值
    print( config.get('message', 'greeting') )

    #访问 numbers 区段下的 pi 值，并转换为 float
    print( config.getfloat('numbers', 'pi')  )


if __name__=='__main__':
    ConfigParserTest()
