#!/bin/bash

PATH_TEST='TEST/FINAL_TEST/'
LIST_TEST_FILES='archivide assign biblio case'
RESULTS_DIRECTORY='RESULTS/'

cd ../../
mkdir $PATH_TEST$RESULTS_DIRECTORY
for files in $LIST_TEST_FILES
do
	rm -f $PATH_TEST$RESULTS_DIRECTORY$files.log
	./main -tree -debug -file $PATH_TEST$files.vhd |tee $PATH_TEST$RESULTS_DIRECTORY$files.log
done

cd TEST/FINAL_TEST/
