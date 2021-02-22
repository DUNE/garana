/*
 * FlatRecoTree.h
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_FLATRECOTREE_H_
#define GARANA_FLATRECOTREE_H_

#include "garana/Base/RecoTree.h"

using std::vector;

namespace garana {

 class FlatRecoTree : public RecoTree {

  public:

	FlatRecoTree();
	FlatRecoTree(TTree* tree);
	FlatRecoTree(TTree* tree, char opt);

    //accessors inherited from RecoTree
    //virtual void GetEntry(UInt_t entry) override;

    //private:
  protected:

    bool SetBranchAddresses() override;
    void SetVecs();
    void ClearVecs();


 };//class
}//namespace

#endif /* FLATRECOTREE_H_ */
