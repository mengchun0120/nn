#!/bin/bash

all_tests="$(ls test/unit/bin)"
for test in $all_tests; do
    echo "Running test/unit/bin/$test ..."
    test/unit/bin/$test
    if [ $? != 0 ]; then
        exit 1
    fi
done

exit 0
