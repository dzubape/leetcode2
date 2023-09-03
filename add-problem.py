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
    value = re.sub(r'[ -_]+', ' ', value)
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

def parse_signature(value):
    matches = re.match(
        r'^\s*(.+)\s+([_a-zA-Z][_a-zA-Z]*)\((.+)\)\s*$',
        value,
    )
    # print(f'{matches = }')
    METHOD_RETURN = matches[1]
    METHOD_NAME = matches[2]
    METHOD_PARAMS = matches[3]
    METHOD_PARAMS = re.sub(r'^\s+|\s+$', '', METHOD_PARAMS)

    print(f'{METHOD_RETURN = }')
    print(f'{METHOD_NAME = }')
    print(f'{METHOD_PARAMS = }')
    return {
        'name': METHOD_NAME,
        'return': METHOD_RETURN,
        'params': METHOD_PARAMS,
    }


def add_problem(args):
    parser = argparse.ArgumentParser()
    parser.add_argument('-s', '--signature', required=True)
    parser.add_argument('-t','--task', required=False, nargs='+')
    
    opts = parser.parse_args(args)
    # print(f'{opts = }')

    signature = parse_signature(opts.signature)

    methodName = signature['name']
    methodReturn = signature['return']
    methodParams = signature['params']

    if opts.task:
        taskInWords = splitToWords(opts.task)
        methodName = joinWithCamel(taskInWords)
    else:
        taskInWords = splitToWords(signature['name'])
    taskDashed = joinWithDashes(taskInWords)

    print(f'{methodName = }')
    print(f'{taskInWords = }')
    print(f'{taskDashed = }')

    with open('CMakeLists.txt', 'r+') as fp_src, open('new.CMakeLists.txt', 'w') as fp_dst:
        for line in fp_src.readlines():
            # print(f'{line = }')
            # print(line, end='')
            fp_dst.write(line)
            if line.find("tmpl.cpp") < 0:
                continue
            line = line.replace('tmpl.cpp', f'{taskDashed}.cpp')
            fp_dst.write(line)
            # print(line, end='')
    # os.rename('new.CMakeLists.txt', 'CMakeLists.txt')

    with open('tmpl.cpp', 'r') as fp_src, open(f'{taskDashed}.cpp', 'w') as fp_dst:
        for line in fp_src.readlines():
            line = line.replace('LEETCODE_METHOD_NAME', signature['name'])
            line = line.replace('METHOD_NAME', methodName)
            line = line.replace('METHOD_RETURN', methodReturn)
            line = line.replace('METHOD_PARAMS', methodParams)
            fp_dst.write(line)
    # os.rename('new.tmpl.cpp', 'tmpl.cpp')

    with open('Solution.hpp', 'r') as fp_src, open('new.Solution.hpp', 'w') as fp_dst:
        for line in fp_src.readlines():
            fp_dst.write(line)
            if line.find('// CASES //') < 0:
                continue
            matches = re.match(r'^\s+', line)
            indent = matches[0]
            # fp_dst.write(indent + f'{methodReturn} {methodName}({methodParams});\n')
            fp_dst.write(indent + f'ADD_CASE({methodName}, {methodReturn}, {methodParams});\n')
    # os.rename('new.Solution.hpp', 'Solution.hpp')

    

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