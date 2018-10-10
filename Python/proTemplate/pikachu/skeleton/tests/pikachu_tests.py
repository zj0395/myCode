#!/usr/bin/env python
# coding=utf-8
from nose.tools import *
import pikachu
def setup():
    print("setup!")

def teardown():
    print("Tear Down")

def test_basic():
    print("Run!")
