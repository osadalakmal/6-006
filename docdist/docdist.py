#!/usr/bin/python
# Author: Osada Paranaliyanage
# Usage:
#    docdist1.py filename1 filename2
#
# This program computes the "distance" between two text files
# as the angle between their word frequency vectors (in radians).
#
# For each input file, a word-frequency vector is computed as follows:
#    (1) the specified file is read in
#    (2) it is converted into a list of alphanumeric "words"
#        Here a "word" is a sequence of consecutive alphanumeric
#        characters.  Non-alphanumeric characters are treated as blanks.
#        Case is not significant.
#    (3) for each word, its frequency of occurrence is determined
#    (4) the word/frequency lists are sorted into order alphabetically
#
# The "distance" between two vectors is the angle between them.
# If x = (x1, x2, ..., xn) is the first vector (xi = freq of word i)
# and y = (y1, y2, ..., yn) is the second vector,
# then the angle between them is defined as:
#    d(x,y) = arccos(inner_product(x,y) / (norm(x)*norm(y)))
# where:
#    inner_product(x,y) = x1*y1 + x2*y2 + ... xn*yn
#    norm(x) = sqrt(inner_product(x,x))

import cProfile
import re
import math
import string
import sys

def read_file(filename):
    """
    Read the text file with the given filename;
    return a list of the lines of text in the file.
    """
    try:
        fp = open(filename)
        L = fp.readlines()
    except IOError:
        print "Error opening or reading input file: ",filename
        sys.exit()
    return L

#################################################
# Operation 2: split the text lines into words ##
#################################################
def get_words_from_line_list(L):
    """
    Parse the given list L of text lines into words.
    Return list of all words found.
    """

    word_list = []
    for line in L:
        words_in_line = [ x.lower() for x in re.split("[^A-Za-z0-9]",line) if x]
        word_list.extend(words_in_line)
    return word_list

##############################################
# Operation 3: count frequency of each word ##
##############################################
def count_frequency(word_list):
    """
    Return a list giving pairs of form: (word,frequency)
    """
    D = dict() 
    for new_word in word_list:
        if new_word in D:
            D[new_word] = D[new_word]+1
        else:
            D[new_word] = 1
    return D

#############################################
## compute word frequencies for input file ##
#############################################
def word_frequencies_for_file(filename):
    """
    Return alphabetically sorted list of (word,frequency) pairs
    for the given file.
    """

    line_list = read_file(filename)
    word_list = get_words_from_line_list(line_list)
    freq_mapping = count_frequency(word_list)

    print "File",filename,":",
    print len(line_list),"lines,",
    print len(word_list),"words,",
    print len(freq_mapping),"distinct words"

    return freq_mapping

def inner_product(L1,L2):
    """
    Inner product between two vectors, where vectors
    are represented as dictionary of (word,freq) pairs.

    Example: inner_product([["and",3],["of",2],["the",5]],
                           [["and",4],["in",1],["of",1],["this",2]]) = 14.0
    """
    c1 = [ item for item in L1.items() ]
    common_items = [ L2[item[0]] * item[1] for item in L1.items() if item[0] in L2 ]
    total = sum(common_items)
    print "total is " + str(total) + "\n"
    return total

def vector_angle(L1,L2):
    """
    The input is a list of (word,freq) pairs, sorted alphabetically.

    Return the angle between these two vectors.
    """
    numerator = inner_product(L1,L2)
    print "numerator" + str(numerator)
    denominator = math.sqrt(inner_product(L1,L1)*inner_product(L2,L2))
    return math.acos(numerator/denominator)

def main():
    if len(sys.argv) != 3:
        print "Usage: docdist1.py filename_1 filename_2"
    else:
        filename_1 = sys.argv[1]
        filename_2 = sys.argv[2]
        sorted_word_dict_1 = word_frequencies_for_file(filename_1)
        #for word in sorted_word_dict_1:
        #    print "'" + word + "' " + str(sorted_word_dict_1[word])
        sorted_word_dict_2 = word_frequencies_for_file(filename_2)
        #for word in sorted_word_dict_2:
        #    print "'" + word + "' " + str(sorted_word_dict_2[word])
        distance = vector_angle(sorted_word_dict_1,sorted_word_dict_2)
        print "The distance between the documents is: %0.6f (radians)"%distance

if __name__ == "__main__":
    #cProfile.run("main()")
    main()
