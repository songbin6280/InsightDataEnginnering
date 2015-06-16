# -*- coding: utf-8 -*-
"""
Created on Fri Jun 12 10:50:02 2015

@author: Bin Song
"""

from os import listdir
from os.path import isfile, join
import sys
from numpy import median

#take the two directories for input and output
inputpath = sys.argv[1]

#create two empty lists. l for number of words in each, and m for correspoding median value
l = []
m = []

#only read txt files in the inputpath
onlytxt = [ f for f in listdir(inputpath) if isfile(join(inputpath, f)) and f[-4:] == ".txt"]
#sort input files alphabetically
inputfiles = sorted(onlytxt, key=str.lower)
for eachf in inputfiles: 
    infile = open(join(inputpath, eachf), "r")
    for line in infile:
        item = line.split()
        word_num = len(item)  #compute the number of words in a line
        l.append(word_num)   #append the number of words to l
        m.append(median(l)) #append the median to m
    infile.close()
#write out the computed results
out = open(sys.argv[2], "w")
for i in m:
    out.write(str(i)+"\n")
out.close()
print "running_median code has successfully completed."
