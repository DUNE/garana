/*
 * G4Tree.h
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_G4TREE_H_
#define GARANA_G4TREE_H_

#include "garana/Base/TreeReader.h"

using std::vector;

namespace garana {

  class G4Tree : public TreeReader {

    public:

	  virtual ~G4Tree() {};

	  virtual const UInt_t                  NSim()             const = 0;
	  virtual       vector<TLorentzVector>* SimMom(UInt_t iparticle) = 0;
	  virtual       vector<TLorentzVector>* SimPos(UInt_t iparticle) = 0;

	  UInt_t const& GetTruthIndex(UInt_t iparticle) const;


	  //inline static const std::string treename = "g4Tree";

    protected:
	     vector<TLorentzVector>* fPos           = nullptr;
	     vector<TLorentzVector>* fMom           = nullptr;
		 vector<UInt_t>*         fG4TruthIndex  = nullptr;
		 vector<UInt_t>*         fG4FSIndex     = nullptr;
		 TBranch*                b_G4TruthIndex = nullptr;
		 TBranch*                b_G4FSIndex    = nullptr;
  };//class
}//namespace

#endif /* GARANA_G4TREE_H_ */
