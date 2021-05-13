/*
 * FlatDisplayTree.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/FlatDisplayTree.h"

using namespace garana;

FlatDisplayTree::FlatDisplayTree(TTree* tree)
{
    SetupRead(tree);
}

FlatDisplayTree::FlatDisplayTree(TTree* tree, char opt)
{
	CheckOpt(opt);//sets TreeReader::fOpt

    if(fOpt=='r'){
    	std::cout << "constructed FlatDisplayTree object in read-only mode" << std::endl;
    	SetupRead(tree);
    }
    else {
    	std::cout << "constructed FlatDisplayTree object in write mode" << std::endl;
    	fTreeIn = tree;
    	SetBranchAddresses();
    }

}

/*void FlatDisplayTree::GetEntry(UInt_t entry) {
	this->fDisplayToFSLimits.clear();
	fTreeIn->GetEntry(entry);
    this->FindFSLimits();
}*/

bool FlatDisplayTree::SetBranchAddresses(){

std::cout << "FlatDisplayTree SetBranchAddresses()" << std::endl;

	if(fOpt=='r'){
		fTreeIn->SetBranchAddress("Event",             &fEvent,            &b_Event           );

	}


	if(fOpt=='w'){

		fTreeIn->Branch("Event",             &fEvent, "Event/I");

	}

	return true;
}

//implement accessors inherited from DisplayTree

 void FlatDisplayTree::SetVecs() {


 }

 void FlatDisplayTree::ClearVecs() {



 }
