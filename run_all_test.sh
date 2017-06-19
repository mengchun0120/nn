#!/bin/bash

all_tests="$(ls test/bin)"
for test in $all_tests; do
    echo "Running test/bin/$test ..."
    test/bin/$test
    if [ $? != 0 ]; then
        exit 1
    fi
done

exit 0
