/*
 * StructuredRecoTree.h
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_STRUCTUREDRECOTREE_H_
#define GARANA_STRUCTUREDRECOTREE_H_

#include "garana/Base/RecoTree.h"

using std::vector;

namespace garana {

 class StructuredRecoTree : public RecoTree {

   public:

	 StructuredRecoTree() {}
	 StructuredRecoTree(TTree* tree);


   private:

	 //pure virtual function from RecoTree
	 bool SetBranchAddresses() override;

	 //leaves and branches
	 /*vector<RecoParticle>* fRecoParticles   = nullptr;  ///< 'condensed' nusimdata::MCParticles from Reco
	 vector<UInt_t>      fRecoTruthIndex  = nullptr;

     TBranch*            b_RecoParticles  = nullptr;
     TBranch*            b_RecoTruthIndex = nullptr;*/

 };//class
}//namespace
#endif /* GARANA_STRUCTUREDRECOTREE_H_ */
