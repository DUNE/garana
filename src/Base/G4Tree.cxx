/*
 * G4Tree.cxx
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#include "garana/Base/G4Tree.h"

using namespace garana;

const UInt_t G4Tree::GetTruthIndex(UInt_t iparticle) const {
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

const UInt_t G4Tree::NPrimary() const {

	UInt_t nprimary=0;
	while(nprimary<this->NSim() && this->IsPrimary(nprimary))
		nprimary++;

	return nprimary;
}

bool G4Tree::HasPassedTPC(const UInt_t& iparticle) const {

	for(size_t ireg=0; ireg<this->NRegions(iparticle); ireg++) {
		if(this->Region(iparticle,ireg)==0 || this->Region(iparticle,ireg)==1) {
			return true;
		}
	}

	return false;
}

bool G4Tree::HasPassedCalo(const UInt_t& iparticle) const {

	for(size_t ireg=0; ireg<this->NRegions(iparticle); ireg++) {
		if(this->Region(iparticle,ireg)==3 || this->Region(iparticle,ireg)==4) {
			return true;
		}
	}

	return false;
}

bool G4Tree::IsStoppedTPC(const UInt_t& iparticle)    const {
	UInt_t ireg = this->NRegions(iparticle)-1;
	if(this->Region(iparticle,ireg)==0 || this->Region(iparticle,ireg)==1)
		return true;
	else
		return false;
}

bool G4Tree::IsStoppedCalo(const UInt_t& iparticle)   const {
	UInt_t ireg = this->NRegions(iparticle)-1;
	if(this->Region(iparticle,ireg)==3 || this->Region(iparticle,ireg)==4)
		return true;
	else
		return false;
}

bool G4Tree::IsContainedTPC(const UInt_t& iparticle)  const {

	bool isAV = false;
	for(size_t ireg=0; ireg<this->NRegions(iparticle); ireg++) {
		if(this->Region(iparticle,ireg)!=0 && this->Region(iparticle,ireg)!=1)
			return false;
		else
			isAV = true;
	}

	if(isAV)
		return true;
	else
		return false;
}

bool G4Tree::IsContainedCalo(const UInt_t& iparticle) const {

	bool isCalo = false;
	for(size_t ireg=0; ireg<this->NRegions(iparticle); ireg++) {
		if(this->Region(iparticle,ireg)!=3 && this->Region(iparticle,ireg)!=4)
			return false;
		else
			isCalo = true;
	}

	if(isCalo)
		return true;
	else
		return false;

}

bool G4Tree::IsCathodeCrosser(const UInt_t& iparticle) const {

	if(this->NRegions(iparticle)<2)
		return false;

	for(size_t ireg=0; ireg<this->NRegions(iparticle)-1; ireg++) {

		if( (this->Region(iparticle,ireg)==0 && this->Region(iparticle,ireg+1)==1) ||
		      (this->Region(iparticle,ireg)==1 && this->Region(iparticle,ireg+1)==0) )
			return true;
	}

	return false;
}

bool G4Tree::IsContainedTPCEvent() const {

	for(size_t isim=0; isim<this->NSim(); isim++){
		if(this->HasPassedTPC(isim))
			if(!this->IsContainedTPC(isim))
				return false;
	}

	return true;
}

bool G4Tree::IsContainedTPCPrimaries() const {

	for(size_t isim=0; isim<this->NSim(); isim++){
		if(this->HasPassedTPC(isim))
			if(this->IsPrimary(isim))
				if(!this->IsContainedTPC(isim))
					return false;
	}

	return true;
}

bool G4Tree::IsContainedCaloEvent() const {

	for(size_t isim=0; isim<this->NSim(); isim++){
		if(this->HasPassedCalo(isim))
			if(!this->IsContainedCalo(isim))
				return false;
	}

	return true;
}

bool G4Tree::IsContainedCaloPrimaries() const {

	for(size_t isim=0; isim<this->NSim(); isim++){
		if(this->HasPassedCalo(isim))
			if(this->IsPrimary(isim))
				if(!this->IsContainedCalo(isim))
					return false;
	}

	return true;

}

const TLorentzVector* G4Tree::SimMomBegin(const UInt_t& iparticle) const {
	return this->SimMomEnter(iparticle,0);
}

const TLorentzVector* G4Tree::SimMomEnd(const UInt_t& iparticle) const {
	return this->SimMomExit(iparticle,this->NRegions(iparticle)-1);
}

const TLorentzVector* G4Tree::SimPosBegin(const UInt_t& iparticle) const {
	return this->SimPosEnter(iparticle,0);
}

const TLorentzVector* G4Tree::SimPosEnd(const UInt_t& iparticle) const {
	return this->SimPosExit(iparticle,this->NRegions(iparticle)-1);
}
