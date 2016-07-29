#!/usr/bin/env python

from distutils.core import setup

NAME = 'gen-symver-map'
DESC = '''
A simplistic linker version script generator which works by scanning
your source for certain annotations.
'''

setup(name=NAME, description=DESC.strip(),
    version='1.0',
    author='Evan Powers',
#    author_email='MPSSBUGBUG FIXME',
    scripts=[NAME])
