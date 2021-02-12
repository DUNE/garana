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

	  std::string* const TreeType() const;

   private:

	  bool SetBranchAddresses() override;

	  //leaf types
	  std::string* fTreeType = nullptr;

	  //branches
	  TBranch* b_TreeType = nullptr;


  };//class
}//namespace
#endif /* HEADERTREE_H_ */
