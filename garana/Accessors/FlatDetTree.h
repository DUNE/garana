/*
 * FlatDetTree.h
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_FLATDETTREE_H_
#define GARANA_FLATDETTREE_H_

#include "garana/Base/DetTree.h"

using std::vector;

namespace garana {

 class FlatDetTree : public DetTree {

  public:

	FlatDetTree() {}
	FlatDetTree(TTree* tree);
	FlatDetTree(TTree* tree, char opt);

    //accessors inherited from DetTree

    //private:
  protected:

    bool SetBranchAddresses() override;
    void SetVecs();
    void ClearVecs();

 };//class
}//namespace

#endif /* FLATDETTREE_H_ */
