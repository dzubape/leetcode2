## How to add new problem solving unit:

run `./problems.py` using next arguments:
```sh
./problems.py --task 'problem-name-in-dashed-style' --signature 'return_type solutionMethodName(arg1_type, arg2_type, ..., argN_type)'
```

`--signature` - would be used to add task method into Solution class.

`--task` - would be used to name file item task method into Solution class; you could 
omit it, then `solutionMethodName` would be used for a file naming, but being splitted into words with dashes.

As a result you'll get:
- ***problem-name-in-dashed-style.cpp*** file within root project dir
- this file is automatically added into ***CMakeLists.txt*** `SOURCES` variable
- ***problem-name-in-dashed-style.cpp*** contains all setup for implementing solution method, testing it within `int test_solutionMethodName()` and copypasting whole file text into leetcode Code textarea
- `return_type solutionMethodName(arg1_type, arg2_type, ..., argN_type)` is injected into ***Solution.hpp*** file
- git checkout -b `problem-name-in-dashed-style`