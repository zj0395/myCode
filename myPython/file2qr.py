#-*- Coding: UTF-8 -*-
__author = 'zj'

import base64, sys, qrcode
from PIL import Image
from pyzbar import pyzbar

def file2QrCode(file):
    MAX_LENGTH = 2300 # 最大为2331
    f = open(file, 'rb')
    code = f.read()
    f.close()
    # code = base64.b64encode(code)
    idx = 0
    fileList = []
    while idx < len(code):
        oneCode = code[idx:idx+MAX_LENGTH]
        # qr = qrcode.QRCode()
        # qr.add_data(oneCode)
        # qr.make()
        # oneImg=qr.make_image()
        oneImg = qrcode.make(oneCode)
        onePath = '%s%d.png' %(file, idx/MAX_LENGTH+1)
        oneImg.save( onePath )
        idx = idx + MAX_LENGTH
        fileList.append(onePath)
    return fileList

def qr2file(img):
    im = Image.open(img)
    ret = pyzbar.decode(im)
    return ret[0].data

def __test__():
    result = b''
    for file in file2QrCode( 'test.py' ):
        result = result + qr2file( file )
    # result = base64.b64decode(result)
    f = open('test_result.py', 'wb')
    f.write(result)
    f.close()


if __name__ == '__main__':
    if len(sys.argv)==1:
        print('请附带参数')
        exit(0)
    file = sys.argv[1]
    if file == 'test':
        __test__()
    elif file[-3:] == 'png':
        qr2file( file )
    else:
        file2QrCode( file )