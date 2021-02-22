/*
 * test_derived_flat_tree.cxx
 *
 *  Created on: Feb 15, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/TreeManager.h"

#include <string>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

using namespace garana;

namespace{
	bool CheckHeader(HeaderTree* h1, HeaderTree* h2);
	bool CheckGen(GenTree* g1, GenTree* g2);
}

int main(int argc, char *argv[]) {

    //// check we got what we need from the command line ////
    if(argc<3) {
        cerr << "use error(test_derived_flat_tree): you must specify a root file to analyze ->" << '\n'
             << "  usage (input file order does not matter): test_derived_flat_tree "
             << "<my_structured_tree.root> <my_flat_tree.root>" << endl;
        return 1;
    }

    if(argc>3) {
        cerr << "use error(test_derived_flat_tree): too many arguments!" << endl;
        return 2;
    }

    // setup files
    std::cout << "open TreeManager for file, " << argv[1] << endl;
    TreeManager* tm1 = new TreeManager(argv[1]); //input file 1
    std::cout << "open TreeManager for file, " << argv[2] << endl;
    TreeManager* tm2 = new TreeManager(argv[2]); //input file 2
    std::cout << "done constructing TreeManagers." << std::endl;

    bool pass = true;

    //Check header trees. only difference should be branch, TreeType
    std::cout << "open headerTree 1" << std::endl;
    HeaderTree* header1 = tm1->GetHeaderTree();
    std::cout << "open headerTree 2" << std::endl;
    HeaderTree* header2 = tm2->GetHeaderTree();
    std::cout << "done constructing HeaderTrees." << std::endl;

    if(!CheckHeader(header1,header2)) {
    	cerr << "WARNING: header trees are incompatible" << endl;
    	pass = false;
    }
    else
    	std::cout << "Headers are compatible." << endl;

    GenTree* gen1 = tm1->GetGenTree();
    GenTree* gen2 = tm2->GetGenTree();

    if(!CheckGen(gen1,gen2)) {
    	cerr << "WARNING: gen trees are incompatible" << endl;
    	pass = false;
    }

    if(!pass){
    	cerr << "WARNING: test failed. something is amiss with your trees." << endl;
    	return 1;
    }
    else {
    	std::cout << "SUCESS!!!!!! =D" << std::endl;
    }

	return 0;
}

namespace{
	bool CheckHeader(HeaderTree* h1, HeaderTree* h2) {

		h1->GetEntry(0);
		h2->GetEntry(0);

	    //determine which tree is structured and which one is flat
	    // TO DO: add check to make sure flat tree came from specific provided structured tree
	    //        assume for now that user is careful (not a great assumption)"
	    try {
	    	if(h1->TreeType() == h2->TreeType())
	    		throw h1;
	    }
	    catch(HeaderTree* h){
	    	cerr << "ERROR (test_derived_flat_tree): provided trees are either both structured or both flat!"
	    		 << endl;
	    	return false;
	    }

		if(h1->NEntries() != h2->NEntries())
			return false;

		if(h1->Run() != h2->Run())
			return false;

		if(h1->SubRun() != h2->SubRun())
			return false;

		return true;
	}// CheckHeader()

	bool CheckGen(GenTree* g1, GenTree* g2) {

		if(g1->NEntries()!=g2->NEntries()){
			cerr << "Gen: trees different length" << endl;
			return false;
		}

		for(UInt_t ientry=0; ientry<g1->NEntries(); ientry++){

			g1->GetEntry(ientry);
			g2->GetEntry(ientry);

			if(g1->NGen()!=g2->NGen()){
				cerr << "Gen: different NGen per entry ("
					 << g1->NGen() << " vs. " << g2->NGen()
					 << ")" << std::endl;
				return false;
			}

			for(UInt_t igen=0; igen<g1->NGen(); igen++){

				if(g1->IsGenie(igen)!=g2->IsGenie(igen)){
					cerr << "Gen: disagreement on IsGenie" << endl;
					return false;
				}

				if(g1->NuPDG(igen)!=g2->NuPDG(igen))
					return false;

				if(*(g1->NuP(igen))!= *(g2->NuP(igen)))
					return false;

				if(g1->IsCC(igen)!=g2->IsCC(igen))
					return false;

				if(g1->NFSParticles(igen)!=g2->NFSParticles(igen))
					return false;

				if(g1->IsCC(igen)!=g2->IsCC(igen))
					return false;

				if(*(g1->NuVertex(igen)) !=  *(g2->NuVertex(igen)))
					return false;

				if(g1->FSEnergy(igen) != g2->FSEnergy(igen))
					return false;

			}//for gen subentries

		}//for gen entries

		return true;

	}//CheckGen()
}
