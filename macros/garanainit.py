##########################################################################
# File: garanainit.py                                                    # 
# Author: Chris Hilgenberg (chilgenb@fnal.gov)                           #
# Description: Script for loading GArAna libraries in python macros      #
# Usage: Include script at top of your macro with 'import garanainit.py' #
#        and call from top of your script with 'garanainit.init()'.      #
#        For example, see garana/macros/demo.py                          #
##########################################################################

import ROOT

def init():

    ROOT.gInterpreter.ProcessLine('R__ADD_LIBRARY_PATH(/dune/app/users/birwin/garana_local_build/localProducts_garana_v00_00_13_e20_prof/garana/v00_00_13/slf7.x86_64.e20.prof/lib)') #change this to your library install area

    #shared garana libraries
    ROOT.gInterpreter.ProcessLine('R__LOAD_LIBRARY(libGaranaAccessors.so)')
#    ROOT.gInterpreter.ProcessLine('R__LOAD_LIBRARY(libGaranaProducts.so)')
#    ROOT.gInterpreter.ProcessLine('R__LOAD_LIBRARY(libGaranaDict.so)')
    ROOT.gInterpreter.ProcessLine('R__LOAD_LIBRARY(libGaranaUtility.so)')

    ROOT.gInterpreter.ProcessLine('R__ADD_INCLUDE_PATH(/dune/app/users/birwin/garana_local_build/localProducts_garana_v00_00_13_e20_prof/garana/v00_00_13/include)') #change this to your garana install area

    # add your headers here
    ROOT.gInterpreter.Declare('#include "garana/Accessors/TreeManager.h"')
    ROOT.gInterpreter.Declare('#include "garana/Utility/Backtracker.h"')

    ROOT.gInterpreter.ProcessLine('using namespace garana;')

#execute as a script
if __name__ == '__main__':
    init()
