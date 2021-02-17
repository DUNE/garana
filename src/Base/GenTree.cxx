#include "include/garana/Base/GenTree.h"

using namespace garana;

bool GenTree::SetBranchAddresses(){

    fTreeIn->SetBranchAddress("GIndex", &fGIndex, &b_GIndex);

    return true;

}

const std::vector<Int_t>* GenTree::GetGIndex() const {
	return fGIndex;
}
