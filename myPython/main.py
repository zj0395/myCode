#!/usr/bin/env python
# coding=utf-8


def fact(n):
    '''
    >>> fact(3)
    6
    >>> fact(0)
    Traceback (most recent call last):
        ...
    ValueError: n<1
    >>> fact(1)
    1
    >>> fact(3)
    6
    '''
    if n < 1:
        print('n<1')
        raise ValueError('n<1')
    elif n == 1:
        return 1
    return n * fact(n - 1)


if __name__ == '__main__':
    print('test')
    import doctest
    doctest.testmod()
print(fact(1))
