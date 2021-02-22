/*
 * G4Tree.h
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_DETTREE_H_
#define GARANA_DETTREE_H_

#include "garana/Base/TreeReader.h"

//#include <TTree.h>

//#include <string>

namespace garana {

  class DetTree : public TreeReader {

    public:

      virtual ~DetTree() {};

	  //inline static const std::string treename = "detTree";

  };//class
}//namespace

#endif /* GARANA_DETTREE_H_ */
