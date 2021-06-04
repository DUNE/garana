import ROOT

def init():

    ROOT.gInterpreter.ProcessLine('R__ADD_LIBRARY_PATH(/cvmfs/dune.opensciencegrid.org/products/dune/garana/v00_00_13/slf7.x86_64.e20.prof/lib)') #change this to your library install area

    #shared garana libraries
    ROOT.gInterpreter.ProcessLine('R__LOAD_LIBRARY(libGaranaAccessors.so)')
    #ROOT.gInterpreter.ProcessLine('R__LOAD_LIBRARY(libGaranaDict.so)')

    ROOT.gInterpreter.ProcessLine('R__LOAD_LIBRARY(libGaranaUtility.so)')

    ROOT.gInterpreter.ProcessLine('R__ADD_INCLUDE_PATH(/cvmfs/dune.opensciencegrid.org/products/dune/garana/v00_00_13)') #change this to your garana install area

    # add your headers here
    ROOT.gInterpreter.Declare('#include "garana/Accessors/TreeManager.h"')
    ROOT.gInterpreter.Declare('#include "garana/Utility/Backtracker.h"')

    ROOT.gInterpreter.ProcessLine('using namespace garana;')

#execute as a script
if __name__ == '__main__':
    init()

