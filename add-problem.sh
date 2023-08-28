#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

function print_error {
    msg=$1
    echo -e $RED$msg$NC
}

function print_ok {
    msg=$1
    echo -e $GREEN$msg$NC
}

if (( $# < 1 ))
then
    print_error "assign problem name as first parameter"
    exit -1
fi

PROBLEM_RETURN=int
PROBLEM_PARAMS=void

if (( $# > 1))
then
    PROBLEM_RETURN=$2
fi

if (( $# > 2))
then
    PROBLEM_PARAMS=${@:3}
    PROBLEM_PARAMS=$(printf "%q" "$PROBLEM_PARAMS")
fi

PROBLEM_NAME=$1
PROBLEM_NAME_FORMATTED=$(echo $PROBLEM_NAME | tr '-' '_')

cp tmpl.cpp $PROBLEM_NAME.cpp

sed -i "s/tmpl/$PROBLEM_NAME_FORMATTED/g" $PROBLEM_NAME.cpp
sed -i "s/int Solution::$PROBLEM_NAME_FORMATTED(void)/$PROBLEM_RETURN Solution::$PROBLEM_NAME_FORMATTED($PROBLEM_PARAMS)/g" $PROBLEM_NAME.cpp
sed -i "s/int $PROBLEM_NAME_FORMATTED(void)/$PROBLEM_RETURN $PROBLEM_NAME_FORMATTED($PROBLEM_PARAMS)/g" $PROBLEM_NAME.cpp

sed -zEi "s/tmpl\.cpp\n/\0    $PROBLEM_NAME.cpp\n/g" CMakeLists.txt

sed -zEi "s/ADD_CASE\(tmpl, int, void\);\n/\0    ADD_CASE($PROBLEM_NAME_FORMATTED, $PROBLEM_RETURN, $PROBLEM_PARAMS);\n/g" Solution.hpp

print_ok "<$PROBLEM_NAME> successfully has been added"
