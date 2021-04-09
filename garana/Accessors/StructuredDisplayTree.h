/*
 * StructuredDisplayTree.h
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_STRUCTUREDDISPLAYTREE_H_
#define GARANA_STRUCTUREDDISPLAYTREE_H_

#include "garana/Base/DisplayTree.h"

using std::vector;

namespace garana {

 class StructuredDisplayTree : public DisplayTree {

   public:

	 //StructuredDisplayTree() {}
	 StructuredDisplayTree(TTree* tree=0);

   private:

	 //pure virtual function from DisplayTree
	 bool SetBranchAddresses() override;

	 //leaves and branches
	 /*vector<DisplayParticle>* fDisplayParticles   = nullptr;  ///< 'condensed' nusimdata::MCParticles from Display
	 vector<UInt_t>      fDisplayTruthIndex  = nullptr;

     TBranch*            b_DisplayParticles  = nullptr;
     TBranch*            b_DisplayTruthIndex = nullptr;*/

 };//class
}//namespace
#endif /* GARANA_STRUCTUREDDISPLAYTREE_H_ */
