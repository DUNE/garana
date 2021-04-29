

#include "garana/Base/GenTree.h"

using namespace garana;

const std::vector<Int_t>* GenTree::GetGIndex() const {
       return fGIndex;
}

bool GenTree::NuInAV(const UInt_t& igen) const {
	if(this->NuRegion(igen)==0 || this->NuRegion(igen)==1)
		return true;
	else
		return false;
}
bool GenTree::NuInIV(const UInt_t& igen) const {
	if(this->NuRegion(igen)==2)
		return true;
	else
		return false;
}
bool GenTree::NuInCalo(const UInt_t& igen) const {
	if(this->NuRegion(igen)==3 || this->NuRegion(igen)==4)
		return true;
	else
		return false;
}
