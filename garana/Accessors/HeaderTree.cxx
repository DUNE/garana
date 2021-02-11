/*
 * HeaderTree.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "HeaderTree.h"

using namespace garana;

HeaderTree::HeaderTree() {}
HeaderTree::HeaderTree(TTree* tree) {

	SetupRead(tree);
}

std::string HeaderTree::TreeType() const {

	try{

		if(fTreeType!="structured" && fTreeType!="flat")
			throw fTreeType;
	}
	catch(std::string& type){
		std::cerr << "HeaderTree::TreeType: tree type is not set." << '\n';
	}

	return fTreeType;
}

bool HeaderTree::SetBranchAddresses(){

	fTreeIn->SetBranchAddress("TreeType", &fTreeType, &b_TreeType);

	return true;
}
