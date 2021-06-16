////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                            //
//  File: demo.C                                                                              //  
//  Author: Chris Hilgenberg (chilgenb@fnal.gov)                                              //
//  Description: Short ROOT macro to demonstrate how to interact with GArAna.                 //
//               The user MUST UPDATE PATHS below to GArAna libraries and the input file path //
//               (search for comments prefaced with 'FIXME').                                 //
//  Usage: This macro can be executed via ROOT's interpreter (CINT) with the command          //
//         'root demo.C'                                                                      //
////////////////////////////////////////////////////////////////////////////////////////////////

// load GArAna libraries
R__ADD_LIBRARY_PATH(/usr/local/lib) // may need to be changed for your system
R__ADD_INCLUDE_PATH(/home/chilgenb/garana) // FIXME update path to your garana source area
R__LOAD_LIBRARY(libGaranaAccessors.so)
R__LOAD_LIBRARY(libGaranaDict.so)


// GArAna includes
#include "garana/Accessors/TreeManager.h"

// ROOT includes
#include <TH1F.h>

// c++ includes
#include <iostream>
#include <string>

using namespace garana;
using namespace std;

void test(){

  cout << "loaded libraries" << endl;

  string infile = "/home/chilgenb/test_garana/structuredtree.root"; // FIXME update this with your file path

  TreeManager tm(infile); // central tree manager

  GenTree* gen = tm.GetGenTree(); // pointer to generator tree
  cout << "found genTree with " << gen->NEntries() << " entries" << endl;

  TH1F* h = new TH1F("h","my c++ macro histogram;E_{#nu} [GeV]",10,0,10);

  // loop over genTree entries (events)
  for(size_t i=0; i<gen->NEntries(); i++){

    gen->GetEntry(i); // load data for this event

    // loop over generator particles (only one if single genie interactions)
    for(size_t j=0; j<gen->NGen(); j++){

        h->Fill(gen->NuP(j)->E()); // fill hist with neutrino energy
    }
  }

  cout << "found genTree with " << gen->NEntries() << " entries" << endl;

 auto c = new TCanvas();
 h->Draw();
 c->SaveAs("testhist_cppmacro.png");

}
