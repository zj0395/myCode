#!/usr/bin/env python
# coding=utf-8
def flatten(nested):
    '''递归嵌套生成器，可处理任意类型'''
    try:
        #不迭代类似字符串的对象
        try: nested + ''
        except TypeError: pass
        else: raise TypeError
        for sublist in nested:
            for element in flatten(sublist):
                yield element
    except TypeError:
        yield nested
