/*
 * FlatDetTree.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/FlatDetTree.h"

using namespace garana;

FlatDetTree::FlatDetTree(TTree* tree)
{
    SetupRead(tree);
}

FlatDetTree::FlatDetTree(TTree* tree, char opt)
{
	CheckOpt(opt);//sets TreeReader::fOpt

    if(fOpt=='r'){
    	std::cout << "constructed FlatDetTree object in read-only mode" << std::endl;
    	SetupRead(tree);
    }
    else {
    	std::cout << "constructed FlatDetTree object in write mode" << std::endl;
    	fTreeIn = tree;
    	SetBranchAddresses();
    }

}

/*void FlatDetTree::GetEntry(UInt_t entry) {
	this->fDetToFSLimits.clear();
	fTreeIn->GetEntry(entry);
    this->FindFSLimits();
}*/

bool FlatDetTree::SetBranchAddresses(){

std::cout << "FlatDetTree SetBranchAddresses()" << std::endl;

	if(fOpt=='r'){
		fTreeIn->SetBranchAddress("Event",             &fEvent,            &b_Event           );

	}


	if(fOpt=='w'){

		fTreeIn->Branch("Event",             &fEvent, "Event/I");

	}

	return true;
}

//implement accessors inherited from DetTree
 void FlatDetTree::SetVecs() {


 }

 void FlatDetTree::ClearVecs() {



 }
