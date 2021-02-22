/*
 * G4Tree.h
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_G4TREE_H_
#define GARANA_G4TREE_H_

#include "garana/Base/TreeReader.h"

namespace garana {

  class G4Tree : public TreeReader {

    public:

	  virtual ~G4Tree() {};

	  virtual const UInt_t                        NSim()             const = 0;
	  virtual       std::vector<TLorentzVector>* SimMom(UInt_t iparticle) = 0;
	  virtual       std::vector<TLorentzVector>* SimPos(UInt_t iparticle) = 0;

	  //inline static const std::string treename = "g4Tree";

    protected:
		 std::vector<TLorentzVector>* fMom = nullptr;
		 std::vector<TLorentzVector>* fPos = nullptr;

  };//class
}//namespace

#endif /* GARANA_G4TREE_H_ */
