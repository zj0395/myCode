#!/usr/bin/env python
# coding=utf-8

'''
testFile 目录下的 templatesDefine.txt 和 templatesInstance.txt 为测试文件
将这个文件作为参数调用本脚本，即可看到结果
该脚本至少需要两个文件作为参数，最后一个为实例文件，其它文件均视为定义文件
'''

import fileinput, re
from sys import argv

def main(params):
    #本函数可以在实例文件里放可执行语句，如不需要，可使用最下方的replacement2函数
    def replacement(match):
        code = match.group(1)
        try:
            #如果可以求值，就返回它
            return str( eval(code, scope) )
        except SyntaxError:
            #否则就执行作用域内的赋值语句
            exec (code, scope)
            #返回空字符串
            return ''
    
    #匹配 中括号 内的字段
    fieldPat = re.compile(r'\[(.+?)\]')

    #变量收集到这里
    scope = {}
    
    #读取定义文件
    for file in params[1:-1]:
        exec(open(file).read(), scope)
    
    #读取文本文件
    lines = []
    for line in fileinput.input(params[-1]):
        lines.append(line)
    text = ''.join(lines)
    
    #开始替换
    print( fieldPat.sub(replacement, text) )

if __name__=='__main__':
    main(argv)

#此函数更简练
def replacement2(match):
    code = match.group(1)
    return str( eval(code, scope) )
