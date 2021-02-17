/*
 * HeaderTree.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "include/garana/Accessors/HeaderTree.h"

using namespace garana;

HeaderTree::HeaderTree(){}
HeaderTree::HeaderTree(TTree* tree)
{
	SetupRead(tree);
}

HeaderTree::HeaderTree(TTree* tree, char opt)
{
	CheckOpt(opt);//sets TreeReader::fOpt

    if(fOpt=='r'){
    	SetupRead(tree);
    }
    else {
    	fTreeIn = tree;
    	SetBranchAddresses();
    }
}//


std::string* const HeaderTree::TreeType() const {

    fTreeIn->GetEntry(0);
    //std::cout << "trying tree type, " << fTreeType << std::endl;
	try{

		if(fTreeTypePtr->compare("structured")!=0 && fTreeTypePtr->compare("flat")!=0)
			throw fTreeTypePtr;

	}
	catch(std::string* type){
		std::cerr << "HeaderTree::TreeType: tree type is not set." << '\n';
	}

	return fTreeTypePtr;
}


Int_t HeaderTree::Run() const {
	fTreeIn->GetEntry(0);
	return fRun;
}
Int_t HeaderTree::SubRun() const {
	fTreeIn->GetEntry(0);
	return fSubRun;
}

bool HeaderTree::SetBranchAddresses(){

	if(fOpt=='r'){
		fTreeIn->SetBranchAddress("Run",      &fRun,      &b_Run);
		fTreeIn->SetBranchAddress("SubRun",   &fSubRun,   &b_SubRun);
		fTreeIn->SetBranchAddress("TreeType", &fTreeTypePtr, &b_TreeType);
	}

	if(fOpt=='w'){
		fTreeIn->Branch("Run",      &fRun,     "Run/I");
		fTreeIn->Branch("SubRun",   &fSubRun,  "SubRun/I");
		fTreeIn->Branch("TreeType", &fTreeType);
	}

	return true;
}

void HeaderTree::SetRun(const Int_t run) {
	std::cout << "SetRun called" << std::endl;
	if(BlockWrite())
		return;

	fRun = run;
	std::cout << "set run = " << fRun << std::endl;
}
void HeaderTree::SetSubRun(const Int_t subrun) {
	if(BlockWrite())
		return;
	fSubRun = subrun;
}
void HeaderTree::SetTreeType(std::string type) {
	if(BlockWrite())
		return;
	fTreeType = type;
	fTreeTypePtr = &fTreeType;
}

