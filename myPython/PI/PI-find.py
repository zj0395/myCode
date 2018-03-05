#!/usr/bin/env python
# coding=utf-8

def PIFind( LEN, PIPath, resultPath ):
    '''
    LEN为整数
    在PI的文件中找到所有的LEN位数
    '''
    DEST = 10**LEN
    print(PIPath)
    with open (PIPath, "r") as f:
        pi = f.read()

    dic = {}
    for num in range(DEST):
        dic["0"*(LEN-len(str(num)))+str(num)] = 0

    count = DEST
    for i in range( 2, len(pi)-LEN ):
        now = pi[i:i+LEN]
        if dic[now] == 0:
            dic[now] = i
            count=count-1
            if count % 10000 == 0:
                print(count)
            if count == 0:
                break
    print(i)

    with open(resultPath, "w") as f:
        for num in range(DEST):
            now = "0"*(LEN-len(str(num)))+str(num)
            if dic[now] == 0:
                f.write(str(now)+":"+"FAIL"+"\n")
            else:
                f.write(str(now)+":"+str(dic[now]-1)+"\n")

if __name__ == "__main__":
    LEN = 6
    fromPath   = "test-PI.txt"
    resultPath = "test-" + str(LEN) + ".txt"
    PIFind( LEN, fromPath, resultPath )

