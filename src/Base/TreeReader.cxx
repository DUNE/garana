
#include "include/garana/Base/TreeReader.h"

using namespace garana;

void TreeReader::SetupRead(TTree* tree=0){

	fTreeIn = tree;
	fOpt = 'r';

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

void TreeReader::GetEntry(UInt_t ientry=0) {
    fTreeIn->GetEntry(ientry);
    return;
}

const TObjArray* TreeReader::GetBranchList() const {
	return fTreeIn->GetListOfBranches();
}

void TreeReader::Fill() {
	if(BlockWrite())
		return;

	fTreeIn->Fill();
}

void TreeReader::Write(){
	if(BlockWrite())
		return;

	//fTreeIn->GetCurrentFile()->Write();
	fTreeIn->Write();
}

//checks read/write option and sets usable value
void TreeReader::CheckOpt(char opt) {
	switch(opt) {
	case('W') :
		fOpt = 'w';
		return;

	case('R') :
		fOpt = 'r';
		return;

	case('w') :
		fOpt = 'w';
		return;
	case('r') :
		fOpt = 'r';
		return;

	default :
		std::cerr << "WARNING(TreeReader): Unknown option specified '"
				  << opt << "'. Option should be 'R'/'r' (read-only)"
				  << " or 'W'/'w' (write). Setting option to read-only."
				  << std::endl;
		fOpt = 'r';
	}
}

bool TreeReader::BlockWrite() const{
	if(fOpt!='w') {
		std::cerr  << "WARNING(TreeReader): Write method invoked for read-only accessor - "
				   << " ignoring method call..." << std::endl;
		return true;
	}
	return false;
}
