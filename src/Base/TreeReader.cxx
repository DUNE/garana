
#include "TreeReader.h"

using namespace garana;

void TreeReader::SetupRead(TTree* tree=0){

	fTreeIn = tree;

	try{
       if(!fTreeIn)
    	   throw fTreeIn;

       if(!SetBranchAddresses())
    	   throw false;
	}
	catch(TTree* t){
		std::cerr << "TreeReader::SetupRead error: input tree not valid" << std::endl;
	}
	catch(bool set){
        std::cerr << "TreeReader::SetupRead error: failed to set branch addresses" << std::endl;
	}

    fTreeIn->SetBranchAddress("Event",       &fEvent,      &b_Event);
}

TTree* TreeReader::GetInputTree(){
    return fTreeIn;
}

Int_t TreeReader::Event() const {

	return fEvent;
}

size_t TreeReader::NEntries() const {
    return fTreeIn->GetEntries();
}

void TreeReader::GetEntry(Long64_t ientry=0) const {
    fTreeIn->GetEntry(ientry);
    return;
}
