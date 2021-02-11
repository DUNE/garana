/*
 * HeaderTree.h
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_HEADERTREE_H_
#define GARANA_HEADERTREE_H_

#include "TreeReader.h"
#include <string>

namespace garana{

  class HeaderTree : public TreeReader  {

   public:

	  HeaderTree();
	  HeaderTree(TTree* tree);

	  std::string TreeType() const;

   private:

	  bool SetBranchAddresses() override;

	  //leaf types
	  std::string fTreeType="";

	  //branches
	  TBranch* b_TreeType=0;


  };//class
}//namespace
#endif /* HEADERTREE_H_ */
