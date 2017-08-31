#!/usr/bin/env python
# coding=utf-8

import numpy as np

def npSum():
    a=np.array([0,1,2,3,4,5])
    b=np.array([3,4,5,6,7,8])
    c=a**2+b**3
    return c

print( npSum() )
