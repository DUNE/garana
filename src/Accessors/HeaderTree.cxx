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

std::string* const HeaderTree::TreeType() const {

        fTreeIn->GetEntry(0);
        std::cout << "trying tree type, " << *fTreeType << std::endl;
	try{

		if(fTreeType->compare("structured")!=0 && fTreeType->compare("flat")!=0)
			throw fTreeType;
	}
	catch(std::string* type){
		std::cerr << "HeaderTree::TreeType: tree type is not set." << '\n';
	}

	return fTreeType;
}

bool HeaderTree::SetBranchAddresses(){

	fTreeIn->SetBranchAddress("TreeType", &fTreeType, &b_TreeType);

	return true;
}
