#!/bin/sh

echo ha > newFile
echo hello > newFile
ls -l >> newFile
cat < tests/exit.sh
cat < tests/exit.sh > newFile2
echo a && echo b > newFile3
cat < src/3Or.h >> newFile3