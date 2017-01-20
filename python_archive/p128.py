import os
import fnmatch

def find_files(topdir,pattern):
    for path, dirname,filelist in os.walk(topdir):
        for name in fiellist:
            if fnmatch.fnmatch(name,pattern):
                yield os.path.join(path,name)

import gzip, bz2

def opener(filenames):
    for name in filenames:
        if name.endswitch(".gz"): f = gzip.open(name)
        elif name.endswitch(".bz2"): f = bz2.BZ2File(name)
        else: f = open(name)
        yield f


def cat(filelist):
    for f in filelist:
        for line in f:
            yield line


def grep(pattern,lines):
    for line in lines:
        if pattern in line:
            yield line

