/*
 * MillHeaderTree.cxx
 *
 *  Created on: Feb 15, 2021
 *      Author: chilgenb
 */

#include "include/garana/Processors/MillHeaderTree.h"

using namespace garana;

MillHeaderTree::MillHeaderTree(TTree* treeIn, TTree* treeOut)
{
	fHeaderIn = new HeaderTree(treeIn,'r');
	fHeaderOut = new HeaderTree(treeOut,'w');
	VerifyBranches();
	MillTrees();

}


void MillHeaderTree::MillTrees() {

	//only a single entry to process
	fHeaderOut->SetRun(fHeaderIn->Run());
	fHeaderOut->SetSubRun(fHeaderIn->SubRun());
	fHeaderOut->SetTreeType("flat");
	fHeaderOut->Fill();
	fHeaderOut->Write();

	delete fHeaderIn;
	delete fHeaderOut;
}
bool MillHeaderTree::VerifyBranches() {

	fIsVerified = true;
	return true;
}
