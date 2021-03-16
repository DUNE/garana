/*
 * G4Tree.cxx
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#include "garana/Base/G4Tree.h"

using namespace garana;

UInt_t const& G4Tree::GetTruthIndex(UInt_t iparticle) const {
	try {
		if(iparticle < fG4TruthIndex->size())
	        return fG4TruthIndex->at(iparticle);

		throw(iparticle);
	}
	catch(UInt_t index){
		std::cerr << "G4TruthIndex out of range ("
				  << iparticle << " vs. " << fG4TruthIndex->size()
				  << std::endl;
		return UINT_MAX;
	}
}
