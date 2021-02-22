/*
 * FlatRecoTree.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/FlatRecoTree.h"

using namespace garana;

FlatRecoTree::FlatRecoTree(TTree* tree)
{
    SetupRead(tree);
}

FlatRecoTree::FlatRecoTree(TTree* tree, char opt)
{
	CheckOpt(opt);//sets TreeReader::fOpt

    if(fOpt=='r'){
    	std::cout << "constructed FlatRecoTree object in read-only mode" << std::endl;
    	SetupRead(tree);
    }
    else {
    	std::cout << "constructed FlatRecoTree object in write mode" << std::endl;
    	fTreeIn = tree;
    	SetBranchAddresses();
    }

}

/*void FlatRecoTree::GetEntry(UInt_t entry) {
	this->fRecoToFSLimits.clear();
	fTreeIn->GetEntry(entry);
    this->FindFSLimits();
}*/

bool FlatRecoTree::SetBranchAddresses(){

std::cout << "FlatRecoTree SetBranchAddresses()" << std::endl;

	if(fOpt=='r'){
		fTreeIn->SetBranchAddress("Event",             &fEvent,            &b_Event           );

	}


	if(fOpt=='w'){

		fTreeIn->Branch("Event",             &fEvent, "Event/I");

	}

	return true;
}

//implement accessors inherited from RecoTree

 void FlatRecoTree::SetVecs() {


 }

 void FlatRecoTree::ClearVecs() {



 }
