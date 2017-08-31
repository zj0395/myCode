#!/usr/bin/env python
# coding=utf-8
'A test PY file'
__author__='ZJ'
import sys
def test():
    args=sys.argv
    if(len(args)==1):
        print('Hello World')
    elif(len(args)==2):
        print('Hello, %s!'%args[1])
    else:
        print('FUCKING',end=' ')
        for x in args[1:-1]:
            print(x,end=' ')
        print()

if __name__=='__main__':
    test()
def trang(max):
    n=0
    l=[1]
    while n<max:
        yield l
        n+=1
        l=[1]+[l[x]+l[x+1] for x in range(len(l)-1)]+[1]

def normalize(name):
    return name.capitalize()

from functools import reduce
def prod(L):
    return reduce(lambda x,y:x*y, ( map(lambda x:int(x), L) ))

def allnumber():
    n=1;
    while n<10000:
        n+=1
        yield n

def back_number(s):
    if str(s)==str(s)[::-1]:
        return True
    else:
        return False
#print (list(filter(back_number,list(allnumber()))))
import functools
def by_name(t):
    return t[0].lower()
def log(f):
    @functools.wraps(f)
    def wrapper(*args,**lw):
        print('call %s'%f.__name__)
        print(args)
        print(lw)
        return f(*args,**lw)
    return wrapper
@log
def by_score(t):
    return t[1]
L=[('BOB',75),('adam',92),('Bart',65),('Lisa',88)]
#print(sorted(L,key=by_score,reverse=False))
#print(by_score.__name__)
