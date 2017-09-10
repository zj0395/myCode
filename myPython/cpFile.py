#!/usr/bin/env python
# coding=utf-8
from sys import argv
fromFile = 'loging.py'
destFile = "dest.txt"
inFile = open(fromFile)
inData = inFile.read()
outFile = open(destFile, 'w')
outFile = outFile.write(inData)
