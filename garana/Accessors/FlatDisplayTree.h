/*
 * FlatDisplayTree.h
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_FLATDISPLAYTREE_H_
#define GARANA_FLATDISPLAYTREE_H_

#include "garana/Base/DisplayTree.h"

using std::vector;

namespace garana {

 class FlatDisplayTree : public DisplayTree {

  public:

	FlatDisplayTree();
	FlatDisplayTree(TTree* tree);
	FlatDisplayTree(TTree* tree, char opt);

    //virtual void GetEntry(UInt_t entry) override;

    //private:
  protected:

    bool SetBranchAddresses() override;
    void SetVecs();
    void ClearVecs();





 };//class
}//namespace

#endif /* FLATDISPLAYTREE_H_ */
