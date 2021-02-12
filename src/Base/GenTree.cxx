#include "include/garana/Base/GenTree.h"

using namespace garana;

bool GenTree::SetBranchAddresses(){

    fTreeIn->SetBranchAddress("GIndex", &fGIndex, &b_GIndex);

    return true;

}
