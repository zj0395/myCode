#-*- coding: UTF-8 -*-
__author = 'zj'

import base64, os, sys, qrcode, math, getopt
from PIL import Image
from pyzbar import pyzbar

# 一个二维码最多保存2331字节，适当减少
MAX_LENGTH = 500
TEST_FILE = './file2qr.py'
SPLIT_SYMBOL_FINAL = b'____'
SPLIT_SYMBOL = b'__'


class FileManager(object):
    class OneFile(object):
        def __init__(self, name):
            self._name = 'temp'+name
            self._count = 0
            self._list = []
            self._result = []

        @property
        def count(self):
            return self._count
        @count.setter
        def count(self, count):
            self._count=count
            self._list = [None]*count
            self._result = [None]*count

        def addIdx(self, idx, result):
            self._list[idx] = 1
            self._result[idx] = result
            if None not in self._list:
                self._save()

        def _save(self):
            result = b''.join(self._result)
            print(len(result), result)
            f = open(self._name, 'wb')
            f.write(result)
            f.close()

    _map = {}

    def __init__(self):
        pass

    def addFile(self, name, idx, count, result):
        if name not in self._map:
            newFile = self.OneFile(name)
            newFile.count = count
            self._map[name] = newFile
        self._map[name].addIdx(idx, result)


def encodeName(name, idx, count):
    ret = b'%s%s%d%s%d%s' %(name.encode(), SPLIT_SYMBOL, idx, SPLIT_SYMBOL, count, SPLIT_SYMBOL_FINAL)
    return ret

def decodeName(str):
    countIdx = str.find(SPLIT_SYMBOL_FINAL)
    result = str[ countIdx+len(SPLIT_SYMBOL_FINAL) : ]
    str = str[:countIdx]
    countIdx = str.rfind(SPLIT_SYMBOL)
    count = str[ countIdx+len(SPLIT_SYMBOL): ]
    str = str[:countIdx]
    countIdx = str.rfind(SPLIT_SYMBOL)
    idx = str[ countIdx+len(SPLIT_SYMBOL): ]
    name = str[:countIdx]
    return name.decode(), int(idx), int(count), result


def file2QrCode(file):
    f = open(file, 'rb')
    code = f.read()
    f.close()
    print(len(code),code)
    idx = 0
    filePath, fileName = os.path.split(file)
    fileList = []
    fileSplitNum = math.ceil(len(code)/MAX_LENGTH)
    while idx < fileSplitNum:
        oneCode = encodeName(fileName, idx, fileSplitNum) + code[idx*MAX_LENGTH:(idx+1)*MAX_LENGTH]
        oneCode = base64.b64encode(oneCode)
        qr = qrcode.QRCode()
        qr.add_data(oneCode)
        qr.make()
        oneImg=qr.make_image()
        # oneImg = qrcode.make(oneCode)
        onePath = '%s_%d.png' %(file, idx+1)
        oneImg.save( onePath )
        idx = idx + 1
        fileList.append(onePath)
    return fileList

def QRImg2File(img):
    im = Image.open(img)
    ret = pyzbar.decode(im)
    return ret[0].data

def QRData2File(file):
    f = open(file, 'r')
    qrDatas = f.read()
    fmanager = FileManager()
    for oneResult in qrDatas.split('\n'):
        oneResult = base64.b64decode(oneResult)
        fmanager.addFile( *decodeName(oneResult) )
    pass

def __test__():
    fmanager = FileManager()
    for file in file2QrCode( TEST_FILE ):
        oneResult = QRImg2File(file)
        oneResult = base64.b64decode(oneResult)
        fmanager.addFile( *decodeName(oneResult) )


if __name__ == '__main__':

    def GetArg():
        if len(args) != 1:
            print('最多接受一个参数')
            exit(0)
        return args[0]

    opt, args = getopt.getopt(sys.argv[1:], '-edt', ['--encode', '--decode', '--test'])
    print(opt, args)
    for name, value in opt:
        if name in ('-t', '--test'):
            __test__()
        elif name in ('-e', '--encode'):
            file2QrCode( GetArg() )
        elif name in ('-d', '--decode'):
            QRImg2File( GetArg() )