/*
 * StructuredDetTree.h
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_STRUCTUREDDETTREE_H_
#define GARANA_STRUCTUREDDETTREE_H_

#include "garana/Base/DetTree.h"

#include <TTree.h>

#include <vector>

using std::vector;

namespace garana {

 class StructuredDetTree : public DetTree {

   public:

	 //StructuredDetTree() {}
	 StructuredDetTree(TTree* tree=0);

   private:

	 //pure virtual function from DetTree
	 bool SetBranchAddresses() override;

	 //leaves and branches
	 /*vector<DetParticle>* fDetParticles   = nullptr;  ///< 'condensed' nusimdata::MCParticles from Det
	 vector<UInt_t>      fDetTruthIndex  = nullptr;

     TBranch*            b_DetParticles  = nullptr;
     TBranch*            b_DetTruthIndex = nullptr;*/

 };//class
}//namespace
#endif /* GARANA_STRUCTUREDDetTREE_H_ */
