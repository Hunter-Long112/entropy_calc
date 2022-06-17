#!/usr/bin/env python3

import sys
from optparse import OptionParser
import math

class entropy_calc():

    def __init__(self) -> None:
        pass

    # get filename 
    def parse_args(self):
        usage = "usage: ./entropy_calc.py [options] arg1"
        parser = OptionParser(usage=usage)
        parser.add_option("-f", "--file", dest="filename",
                        help="calculate entropy of FILE", metavar="FILE")
        (options, args) = parser.parse_args()
        if options.filename == None:
            print('Filename is required, exiting...')
            sys.exit(-1)
        return options, args

    # build sym_count array
    def build_sym_count(self, options):
        sym_count = []
        total_syms = 0
        with open(options.filename, 'r') as file:
            temp_char = file.read(1)
            if temp_char == '':
                print('File provided is empty, exiting...')
                sys.exit(-1)                
            else:
                while(temp_char != ''):
                    total_syms = total_syms + 1
                    current_syms = [item[0] for item in sym_count]
                    if temp_char not in current_syms:
                        sym_count.append([temp_char, 1])
                    else:
                        for temp_list in sym_count:
                            if temp_list[0] == temp_char:
                                temp_list[1] = temp_list[1] + 1
                                break
                    temp_char = file.read(1)
        return sym_count, total_syms

    # calculate entropy
    def calc_entropy(self, sym_count, total_syms):
        x = lambda a : a / total_syms
        sym_counts = [item[1] for item in sym_count]
        sym_prob = list(map(x, sym_counts))

        max_entropy = math.log2(len(sym_count))

        logs_of_probs = []
        for prob in sym_prob:
            logs_of_probs.append(math.log2(1 / prob))
        
        entropy = 0
        for i in range(len(logs_of_probs)):
            entropy = entropy + (sym_prob[i] * logs_of_probs[i])
        
        return entropy, max_entropy

    # print report
    def print_report(self, options, sym_count, total_syms, entropy, max_entropy):
        print(f'Entropy Report for {options.filename}:')
        print(f'Number of Discrete Symbols:\t{len(sym_count)}')
        print('Symbol Occurences:')
        for i in range(len(sym_count)):
            print(f'Symbol: {sym_count[i][0]}\t\tOccurences: {sym_count[i][1]}')
        print(f'Total Number of Symbols:\t{total_syms}')
        print(f'Max Entropy:\t\t\t{max_entropy}')
        print(f'File Entropy:\t\t\t{entropy}')

    #driver method for entropy_calc class
    def Run(self):
        (options, args) = self.parse_args()
        sym_count, total_syms = self.build_sym_count(options)
        entropy, max_entropy = self.calc_entropy(sym_count, total_syms)
        self.print_report(options, sym_count, total_syms, entropy, max_entropy)

if __name__ == "__main__":
    ec = entropy_calc()
    ec.Run()
