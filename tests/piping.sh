#!/bin/sh

cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z 
        A-Z > newOutputFile2
ls | head -3 | tail -1
echo a | echo b
echo -e orange \npeach \ncherry | sort > fruit
du | sort -nr
