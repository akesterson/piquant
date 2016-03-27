#!/bin/bash

for testfile in *.c
do
    filebase=$(basename $testfile | sed 's/\.c$//')
    compile_def=$(cat <<EOF
function shunittest_compile_${filebase} {
    set -e ; make ${filebase}.elf >&2 ; test -e ${filebase}.elf ; set +e
}
EOF
)
    eval "$compile_def"
    run_def=$(cat <<EOF
function shunittest_run_${filebase} {
    set -e ; ./${filebase}.elf >&2 ; set +e
}
EOF
)
    eval "$run_def"
done
