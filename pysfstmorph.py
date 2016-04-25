# ============================================================================
# Diplomarbeit - pysfstmorph.py
# Copyright (C) 2008 Hendrik Buschmeier
# ============================================================================
import os
import random
import string

import _pysfstmorph

class Transducer(object):
    '''An interface to the module _pysfstmorph, which is itself an interface
       to the Stuttgart Finite State Transducer (SFST).'''

    def __init__(self, transducer_file, temp_file='use_random_name'):
        '''Init the finite state transducer and load transducer file.'''
        self.transducer_file = transducer_file
        if temp_file == 'use_random_name':
            self.temp_file = 'z' + self._generate_random_string() + '.tmp'
        else:
            self.temp_file = temp_file
        _pysfstmorph.init_transducer(self.transducer_file, self.temp_file)

    def clean_up(self):
        '''Deletes the finite state transducer and the temp file.'''
        _pysfstmorph.delete_transducer()
        if os.path.isfile(self.temp_file):
            os.remove(self.temp_file)

    def analyse(self, input_str):
        '''Analyses the input word with the finite state transducer.'''
        result_str = _pysfstmorph.analyse(input_str)
        return self._split_up(result_str)

    def generate(self, input_str):
        '''Generates word forms of input with the finite state transducer.'''
        result_str = _pysfstmorph.generate(input_str)
        return self._split_up(result_str)

    def _split_up(self, result_str, delimitor='\n'):
        '''Splits up results of generation or analysis'''
        items = result_str.split(delimitor)
        if items[-1] == '':
            return items[:-1]
        else:
            return items

    def _generate_random_string(self, length=10):
        '''Generates a string of random characters.'''
        chars = string.letters + string.digits
        rand_str = ''.join([random.choice(chars) for i in range(length)])
        return rand_str

## Testcode
#if __name__ == '__main__':
#   tf = '/Users/hendrik/Desktop/SFST/data/SMOR/smor.a'
#   t = Transducer(tf)
#   print t.generate('Kardinal<+NN><Masc><Dat><Sg>')
#   print t.analyse('Kardinals')
#   t.clean_up()