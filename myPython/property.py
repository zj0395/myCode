#!/usr/bin/env python
# coding=utf-8
class Student:
    __slots__=('name','age','__score')
    def __len__(self):
        return 5
    def __call__(self):
        print('you called __call__ %s'%self.name)
    def __init__(self,name):
        self.name=name
    def __str__(self):
        return 'The str is %s'%self.name

    @property
    def score(self):
        return self.__score
    @score.setter
    def score(self,value):
        print("score.setter called")
        self.__score=value

if(__name__=='__main__'):

    s=Student('zj')
    s.score=21
    print(len(s))
    print(s)
    s()
    print( callable(1))
    print(callable(s()))
