/*
 * Mill.h
 *
 *  Created on: Feb 14, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_MILL_H_
#define GARANA_MILL_H_

#include "include/garana/Base/TreeReader.h"
#include <TLorentzVector.h>
#include <string>

namespace garana {

 class Mill {// : public TreeReader {

  public:

	virtual ~Mill(){};

	//SetBranchAddrs passed from TreeReader

	virtual void MillTrees() = 0; //Fill out tree for given entry
	virtual bool VerifyBranches() = 0; //check our expectations vs. input tree for genTree branches

	inline bool IsVerified() const { return fIsVerified; }
	std::string CharStarToString(const char* cstr);

  protected:

    bool fIsVerified = false;

	TTree* fTreeOut = nullptr;
	TFile* fOutfile = nullptr;

 };//class Mill

} /* namespace garana */

#endif /* GARANA_MILL_H_ */
