#!/bin/bash
CALCULETTE_PATH="../calculette"
run_test() {
    test_file="$1"
    result=$("$CALCULETTE_PATH" "$test_file")
    echo "Test in $test_file: $result"
}
print_separator() {
    echo "---------------------------------------"
}
for test_file in Test_*.test; do
    run_test "$test_file"
    print_separator
done
