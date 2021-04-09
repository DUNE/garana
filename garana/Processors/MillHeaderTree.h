/*
 * MillHeaderTree.h
 *
 *  Created on: Feb 15, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_MILL_HEADERTREE_H_
#define GARANA_MILL_HEADERTREE_H_

#include "garana/Processors/Mill.h"
#include "garana/Accessors/HeaderTree.h"
#include <string>

namespace garana {

 class MillHeaderTree : public Mill {

  public:
	 MillHeaderTree() {}
	 MillHeaderTree(TTree* treeIn, TTree* treeOut);

	 //bool SetBranchAddresses();// override;

	 void MillTrees()      override;
	 bool VerifyBranches() override;

  private:
	 HeaderTree* fHeaderIn = nullptr;
	 HeaderTree* fHeaderOut = nullptr;

	 //Int_t       fRun      = -1;
	 //Int_t       fSubRun   = -1;
	 std::string fTreeType = "";

 };//class
}//namespace

#endif /* MILLHEADERTREE_H_ */
