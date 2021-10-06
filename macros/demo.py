####################################################################################
# File: demo.py                                                                    #
# Created: April 2021                                                              #
# Author: Chris Hilenberg (chilgenb@fnal.gov)                                      #
# Description: macro for demonstrating how to use garana                           #
# Usage: in your terminal, enter the command 'python demo.py'                      #
#        and that's all there is to it :)                                          #
#        you can build off the example below to access other trees/variables.      #
#        documentation is a work in progress. for now see documentation in         #
#        accessor base classes (garana/Base/*.h).                                  #
####################################################################################

import garanainit # script for loading garana libs
import ROOT # loads all ROOT libs

garanainit.init() # FIXME (if neccessary) loads the garana libs, may need to update library include paths

# central garana tree manager
# it links to all of the individual tree accessors given a file
# with garana trees produced in the default garana format
tm = ROOT.TreeManager("../../test_garana/structuredtree.root") #FIXME update with path to your .root file

# get accessor to genTree
gen = tm.GetGenTree()

print("found GenTree with "+str(gen.NEntries())+" entries")

# make a histogram of the true neutrino energy
h = ROOT.TH1F("h","my PyROOT histogram;E_{#nu} [GeV]",10,0,10);

# loop over events
for ientry in range(0,gen.NEntries()):

	gen.GetEntry(ientry) # fill data members with data for current event

        # loop over all interactions in this event
	for igen in range(0,gen.NGen()):
		h.Fill(gen.NuP(igen).E());

# draw our histogram and save it to file
c = ROOT.TCanvas()
h.Draw()	
c.SaveAs('testhist_pyroot.png')


# ask for user input as a way to keep the program from ending so we can
# see the histogram.
# python doesn't like empty input strings so I abuse exception handling
try:
	null = input("press <Enter> to close canvas and exit program.") 

except:
	null = 'null'

