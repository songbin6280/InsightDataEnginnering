#!/bin/bash

#complie cpp code to count frequency of words
g++ ./src/word_count.cpp -o ./src/word_count

#install numpy package for running_median code
sudo apt-get install python-numpy

#run the words
./src/word_count wc_input wc_output/wc_result.txt
python ./src/running_median.py ./wc_input ./wc_output/med_result.txt

echo "Mission Acommplished."
