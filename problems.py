#!/usr/bin/env python3

import os
import sys
import shutil
import argparse
import re
from pathlib import Path
import json
import tempfile

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

def inject(
    filepath,
    replacement: str,
    substr: str=None,
    pattern: str=None,
):
    assert substr or pattern, 'One of substr or pattern should be provided, both empty is passed'

    with tempfile.NamedTemporaryFile('w+') as fp_tmp:
        with open(filepath, 'r') as fp_src:
            for line in fp_src.readlines():
                if substr:
                    line.replace(substr, replacement)
                elif pattern:
                    line = re.sub(pattern, replacement, line)
                fp_tmp.write(line)
        with open(filepath, 'w') as fp_dst:
            fp_tmp.flush()
            fp_tmp.seek(0)
            fp_dst.write(fp_tmp.read())
    return


def add_problem(args):
    parser = argparse.ArgumentParser()
    parser.add_argument('-s', '--signature', required=True)
    parser.add_argument('-t', '--task', required=False, nargs='+')
    parser.add_argument('-l', '--link', help='Web-reference to the target')
    
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

    gitAddFiles = []

    tasksDir = Path() / 'tasks'
    taskFilePath = tasksDir / f'{taskDashed}.cpp'
    with open(tasksDir / 'tmpl.cpp', 'r') as fp_src, open(taskFilePath, 'w') as fp_dst:
        for line in fp_src.readlines():
            line = line.replace('TASK_LINK', opts.link if opts.link else 'none')
            line = line.replace('LEETCODE_METHOD_NAME', signature['name'])
            line = line.replace('METHOD_NAME', methodName)
            line = line.replace('METHOD_RETURN', methodReturn)
            line = line.replace('METHOD_PARAMS', methodParams)
            fp_dst.write(line)
    gitAddFiles.append(taskFilePath)

    try:
        tmpFileName = 'new.Solution.hpp'
        with open('Solution.hpp', 'r') as fp_src, open(tmpFileName, 'w') as fp_dst:
            insertLine = f'ADD_CASE({methodName}, ESCAPE_COMMAS({methodReturn}), {methodParams});'
            for line in fp_src.readlines():
                if line.find(insertLine) >= 0:
                    print(f'>>{insertLine}<< is already in Solution.hpp')
                    raise int
            fp_src.seek(0)
            for line in fp_src.readlines():
                fp_dst.write(line)
                if line.find('// CASES //') < 0:
                    continue
                matches = re.match(r'^\s+', line)
                indent = matches[0]
                fp_dst.write(indent + f'{insertLine}\n')
        os.rename(tmpFileName, 'Solution.hpp')
    except:
        os.remove(tmpFileName)
    gitAddFiles.append('Solution.hpp')

    solutionSrcFile = 'Solution.cpp'
    inject(
        solutionSrcFile,
        pattern='^((\s+)//<< ADD_SWITCH_CASE)',
        replacement=rf'\2ADD_SWITCH_CASE("{taskDashed}", {methodName});\n\1',
    )
    gitAddFiles.append(solutionSrcFile)

    settingsFilepath = Path() / '.vscode' / 'settings.json'
    with open(settingsFilepath, 'r') as fp:
        settings = json.load(fp)
    settingsDebugConfig = settings.setdefault('cmake.debugConfig', {})
    settingsDebugConfig.setdefault('args', [])[0] = taskDashed
    settingsDebugConfig["cwd"] = r'${workspaceFolder}'
    with open(settingsFilepath, 'w') as fp:
        json.dump(settings, fp, indent=4)
    gitAddFiles.append(settingsFilepath)

    testInputFilepath = Path() / 'test-input' / f'{taskDashed}.json'
    with open(testInputFilepath, 'w') as fp:
        fp.write('["not defined"]')
    gitAddFiles.append(testInputFilepath)

    branchName = f'task/{taskDashed}'
    os.system(f'git checkout -b {branchName}')
    os.system(f'git add {" ".join((str(f) for f in gitAddFiles))}')

    commitMessage = f'task: {taskDashed}, initial'
    if opts.link:
        commitMessage += f'\nlink: {opts.link}'
    os.system(f'git commit -m "{commitMessage}"')
        

if __name__ == '__main__':
    if len(sys.argv) < 2:
        exit(1)

    task = sys.argv[1]
    print(f'{task = }')

    if 'add' == task:
        add_problem(sys.argv[2:])
    else:
        print(f'Unrecognized task <{task}>')
