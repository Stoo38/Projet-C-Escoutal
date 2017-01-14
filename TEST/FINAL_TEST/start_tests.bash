#!/bin/bash
cd ../../

echo "Test 1: Underscore au début d'un identifiant"
./main -tree -error -file TEST/FINAL_TEST/test1.vhd |tee TEST/FINAL_TEST/test1.log

cd TEST/FINAL_TEST/
