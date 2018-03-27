# Jordan Judt
# CSC 492
# 
# Lab 8, Question 2
# 3-23-2018

#!/bin/bash
for file in *.txt
do
mv $file ${file%.txt}.sh
done

