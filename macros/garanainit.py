# garanainit.py 
# created: April 2021
# author: chilgenb@fnal.gov
# description: helper script to make loading garana libraries easier
# usage: 

import ROOT

def init():

    ROOT.gInterpreter.ProcessLine('R__ADD_LIBRARY_PATH(/usr/local/lib)')
    ROOT.gInterpreter.ProcessLine('R__LOAD_LIBRARY(libGaranaAccessors.so)')
    ROOT.gInterpreter.ProcessLine('R__ADD_INCLUDE_PATH(/home/chilgenb/garana/include)')
    ROOT.gInterpreter.Declare('#include "TreeManager.h"')
    ROOT.gInterpreter.ProcessLine('using namespace garana;')


#execute as a script
if __name__ == '__main__':
    init()
