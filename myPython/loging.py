#!/usr/bin/env python
# coding=utf-8
import logging
import pdb
logging.basicConfig(level=logging.DEBUG)

s='0'
n=int(s)
logging.debug('n=%d'%n)
pdb.set_trace()
print(10/n)
