#!/usr/bin/env python3

import os
import sys
import shutil
import argparse
import re

def splitToWords(value):
    if tuple == type(value) or list == type(value):
        words = []
        for word in value:
            words.extend(splitToWords(word))
        return words
    value = value.lower()
    value = re.sub(r'[ -_]+', value, ' ')
    words = value.split(' ')
    return words

def joinWithCamel(words):
    if str == type(words):
        words = words.split(' ')
    camel = words[0]
    for word in words[1:]:
        word = word.lower()
        camel += word[0].upper() + word[1:]
    return camel

def joinWithUnderscore(words):
    if str == type(words):
        words = words.split(' ')
    return '_'.join((word.lower() for word in words))

def joinWithDashes(words):
    return '-'.join(words)


def add_problem(args):
    parser = argparse.ArgumentParser()
    parser.add_argument('-t','--task', required=True, nargs='+')
    
    opts = parser.parse_args(args)
    print(f'{opts = }')

    taskInWords = splitToWords(opts.task)
    print(f'{taskInWords = }')
    taskCamel = joinWithCamel(taskInWords)
    print(f'{taskCamel = }')
    taskUnderscored = joinWithUnderscore(taskInWords)
    print(f'{taskUnderscored = }')
    taskDashed = joinWithDashes(taskInWords)
    print(f'{taskDashed = }')

    with open('CMakeLists.txt', 'r+') as fp_src, open('new.CMakeLists.txt', 'w') as fp_dst:
        for line in fp_src.readlines():
            # print(f'{line = }')
            print(line, end='')
            fp_dst.write(line)
            if line.find("tmpl.cpp") < 0:
                continue
            line = line.replace('tmpl.cpp', f'{taskDashed}.cpp')
            fp_dst.write(line)
            print(line, end='')
        os.unlink()
    

if __name__ == '__main__':
    if len(sys.argv) < 2:
        exit(1)

    task = sys.argv[1]
    print(f'{task = }')

    testPhrase = 'hello this is me PEtya'

    if 'add' == task:
        add_problem(sys.argv[2:])
    elif 'camel' == task:
        camel = joinWithCamel(testPhrase)
        print(f'{camel = }')
    elif 'underscore' == task:
        underscored = joinWithUnderscore(testPhrase)
        print(f'{underscored = }')
    else:
        print(f'Unrecognized task <{task}>')