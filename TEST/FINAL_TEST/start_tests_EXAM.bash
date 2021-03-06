#!/bin/bash

PATH_TEST='EXAM_APP/'
LIST_TEST_FILES='archivide assign base_bit base_ports base biblio case entite_noarchi entite_seule erreur instances latch process_clk2 process_clk3 process_clk4 process_clk proc proc_vide sensibilite signaux typage variables vide'
RESULTS_DIRECTORY='EXAM_RESULTS/'

cd ../../
mkdir $PATH_TEST$RESULTS_DIRECTORY
for files in $LIST_TEST_FILES
do
	rm -f $PATH_TEST$RESULTS_DIRECTORY$files.log
	./escoutal_synth -presynthesis -debug -file $PATH_TEST$files.vhd >> $PATH_TEST$RESULTS_DIRECTORY$files.log
done

grep -c ERR $PATH_TEST$RESULTS_DIRECTORY*
cd TEST/FINAL_TEST/
