/*
 * G4Tree.h
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_RECOTREE_H_
#define GARANA_RECOTREE_H_

#include "garana/Base/TreeReader.h"

namespace garana {

  class RecoTree : public TreeReader {

    public:

	  virtual ~RecoTree() {};

	  //inline static std::string const treename = "recoTree";

  };//class
}//namespace

#endif /* GARANA_RECOTREE_H_ */
