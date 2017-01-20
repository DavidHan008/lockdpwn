import os
import fnmatch

@coroutine
def find_files(target):
    while True:
        topdir,pattern = (yield)
        for path, dirname,filelist in os.walk(topdir):
            for name in fiellist:
                if fnmatch.fnmatch(name,pattern):
                    target.send(os.path.join(path,name))
                    

import gzip, bz2

@coroutine
def opener(target):
    while True:
        name = (yield)
        if name.endswitch(".gz"): f = gzip.open(name)
        elif name.endswitch(".bz2"): f = bz2.BZ2File(name)
        else: f = open(name)
        target.send(f)

@coroutine
def cat(target):
    while True:
        f = (yield)
        for line in f:
            target.send(line)

@coroutine
def grep(pattern,target):
    while True:
        line = (yield)
        if pattern in line:
            target.send(line)

@coroutine
def printer():
    while True:
        line = (yield)
        sys.stdout.write(line)
        

