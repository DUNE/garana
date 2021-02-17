/*
 * FlatGenTree.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "include/garana/Accessors/FlatGenTree.h"

using namespace garana;

FlatGenTree::FlatGenTree() {}

FlatGenTree::FlatGenTree(TTree* tree)
{
    SetupRead(tree);
    fNuP.SetPxPyPzE(0.,0.,0.,0.);
    fNuVertex.SetXYZT(0.,0.,0.,0.);
}

FlatGenTree::FlatGenTree(TTree* tree, char opt)
{
	CheckOpt(opt);//sets TreeReader::fOpt

    if(fOpt=='r'){
    	std::cout << "constructed FlatGenTree object in read-only mode" << std::endl;
    	SetupRead(tree);
		fNuP.SetPxPyPzE(0.,0.,0.,0.);
		fNuVertex.SetXYZT(0.,0.,0.,0.);
		FindFSLimits();
    }
    else {
    	std::cout << "constructed FlatGenTree object in write mode" << std::endl;
    	fTreeIn = tree;
    	SetVecs();
    	SetBranchAddresses();
    }

}

void FlatGenTree::GetEntry(UInt_t entry) {
	this->fGenToFSLimits.clear();
	fTreeIn->GetEntry(entry);
    this->FindFSLimits();
}

bool FlatGenTree::SetBranchAddresses(){

std::cout << "FlatGenTree SetBranchAddresses()" << std::endl;

	if(fOpt=='r'){
		fTreeIn->SetBranchAddress("Event",             &fEvent,            &b_Event           );
		fTreeIn->SetBranchAddress("NGen",              &fNGen,             &b_NGen            );
		fTreeIn->SetBranchAddress("GIndex",            &fGIndex,           &b_GIndex          );


		//FSParticles
		fTreeIn->SetBranchAddress("NFSParticle",       &fNFS,              &b_NFS             );
		fTreeIn->SetBranchAddress("FSParticleIndex",   &fFSIndex,          &b_FSIndex         );
		fTreeIn->SetBranchAddress("FSParticlePDG",     &fFSPdg,            &b_FSPdg           );
		fTreeIn->SetBranchAddress("FSParticleX",       &fFSPosX,           &b_FSPosX          );
		fTreeIn->SetBranchAddress("FSParticleY",       &fFSPosY,           &b_FSPosY          );
		fTreeIn->SetBranchAddress("FSParticleZ",       &fFSPosZ,           &b_FSPosZ          );
		fTreeIn->SetBranchAddress("FSParticleT",       &fFST,              &b_FST             );
		fTreeIn->SetBranchAddress("FSParticlePx",      &fFSMomX,           &b_FSMomX          );
		fTreeIn->SetBranchAddress("FSParticlePy",      &fFSMomY,           &b_FSMomY          );
		fTreeIn->SetBranchAddress("FSParticlePz",      &fFSMomZ,           &b_FSMomZ          );
		fTreeIn->SetBranchAddress("FSParticleE",       &fFSE ,             &b_FSE             );

		//GTruth
		fTreeIn->SetBranchAddress("GNuX",              &fNuX,              &b_NuX             );
		fTreeIn->SetBranchAddress("GNuY",              &fNuY,              &b_NuY             );
		fTreeIn->SetBranchAddress("GNuZ",              &fNuZ,              &b_NuZ             );
		fTreeIn->SetBranchAddress("GNuT",              &fNuT,              &b_NuT             );

		fTreeIn->SetBranchAddress("GWeight",           &fWeight,	       &b_Weight          );
		fTreeIn->SetBranchAddress("GProbability",      &fProbability,      &b_Probability     );
		fTreeIn->SetBranchAddress("GXsec",   	       &fXsec,   	       &b_Xsec            );
		fTreeIn->SetBranchAddress("GDiffXsec",         &fDiffXsec,         &b_DiffXsec        );
		fTreeIn->SetBranchAddress("GGPhaseSpace",      &fGPhaseSpace,      &b_GPhaseSpace     );
		fTreeIn->SetBranchAddress("GProbePDG",         &fProbePDG,	       &b_ProbePDG        );

		fTreeIn->SetBranchAddress("GProbePx",          &fProbePx,          &b_ProbePx         );
		fTreeIn->SetBranchAddress("GProbePy",          &fProbePy,          &b_ProbePy         );
		fTreeIn->SetBranchAddress("GProbePz",          &fProbePz,          &b_ProbePz         );
		fTreeIn->SetBranchAddress("GProbeE ",          &fProbeE ,          &b_ProbeE          );

		fTreeIn->SetBranchAddress("GTgtPx",            &fTgtPx,            &b_TgtPx           );
		fTreeIn->SetBranchAddress("GTgtPy",            &fTgtPy,            &b_TgtPy           );
		fTreeIn->SetBranchAddress("GTgtPz",            &fTgtPz,            &b_TgtPz           );
		fTreeIn->SetBranchAddress("GTgtE ",            &fTgtE ,            &b_TgtE            );

		fTreeIn->SetBranchAddress("GTgtZ",             &fTgtZ,             &b_TgtZ            );
		fTreeIn->SetBranchAddress("GTgtA",             &fTgtA,             &b_TgtA            );
		fTreeIn->SetBranchAddress("GTgtPDG",           &fTgtPDG,           &b_TgtPDG          );
		fTreeIn->SetBranchAddress("GHitNucPDG ",       &fHitNucPDG,        &b_HitNucPDG       );
		fTreeIn->SetBranchAddress("GHitQrkPDG ",       &fHitQrkPDG,        &b_HitQrkPDG       );
		fTreeIn->SetBranchAddress("GIsSeaQuark",       &fIsSeaQuark,       &b_IsSeaQuark      );

		fTreeIn->SetBranchAddress("GHitNucPx",         &fHitNucPx,         &b_HitNucPx        );
		fTreeIn->SetBranchAddress("GHitNucPy",         &fHitNucPy,         &b_HitNucPy        );
		fTreeIn->SetBranchAddress("GHitNucPz",         &fHitNucPz,         &b_HitNucPz        );
		fTreeIn->SetBranchAddress("GHitNucE",          &fHitNucE,          &b_HitNucE         );
		fTreeIn->SetBranchAddress("GHitNucPos",        &fHitNucPos,        &b_HitNucPos       );

		fTreeIn->SetBranchAddress("GGscatter",         &fGscatter,         &b_Gscatter        );
		fTreeIn->SetBranchAddress("GGint",             &fGint,             &b_Gint            );
		fTreeIn->SetBranchAddress("GGQ2",              &fGQ2,              &b_GQ2             );
		fTreeIn->SetBranchAddress("GGq2",              &fGq2,              &b_Gq2             );
		fTreeIn->SetBranchAddress("GGW",               &fGW,               &b_GW              );
		fTreeIn->SetBranchAddress("GGT",               &fGT,               &b_GT              );
		fTreeIn->SetBranchAddress("GGX",               &fGX,               &b_GX              );
		fTreeIn->SetBranchAddress("GGY",               &fGY,               &b_GY              );

		fTreeIn->SetBranchAddress("GFSleptonPx",       &fFSleptonPx,       &b_FSleptonPx      );
		fTreeIn->SetBranchAddress("GFSleptonPy",       &fFSleptonPy,       &b_FSleptonPy      );
		fTreeIn->SetBranchAddress("GFSleptonPz",       &fFSleptonPz,       &b_FSleptonPz      );
		fTreeIn->SetBranchAddress("GFSleptonE",        &fFSleptonE ,       &b_FSleptonE       );

		fTreeIn->SetBranchAddress("GFShadSystPx",      &fFShadSystPx,      &b_FShadSystPx     );
		fTreeIn->SetBranchAddress("GFShadSystPy",      &fFShadSystPy,      &b_FShadSystPy     );
		fTreeIn->SetBranchAddress("GFShadSystPz",      &fFShadSystPz,      &b_FShadSystPz     );
		fTreeIn->SetBranchAddress("GFShadSystE",       &fFShadSystE ,      &b_FShadSystE      );

		fTreeIn->SetBranchAddress("GIsCharm",          &fIsCharm,          &b_IsCharm         );
		fTreeIn->SetBranchAddress("GCharmHadronPDG",   &fCharmHadronPDG,   &b_CharmHadronPDG  );
		fTreeIn->SetBranchAddress("GIsStrange",        &fIsStrange,        &b_IsStrange       );
		fTreeIn->SetBranchAddress("GStrangeHadronPDG", &fStrangeHadronPDG, &b_StrangeHadronPDG);
		fTreeIn->SetBranchAddress("GNumProton",        &fNumProton,        &b_NumProton       );
		fTreeIn->SetBranchAddress("GNumNeutron",       &fNumNeutron,       &b_NumNeutron      );
		fTreeIn->SetBranchAddress("GNumPi0",           &fNumPi0,           &b_NumPi0          );
		fTreeIn->SetBranchAddress("GNumPiPlus",        &fNumPiPlus,        &b_NumPiPlus       );
		fTreeIn->SetBranchAddress("GNumPiMinus",       &fNumPiMinus,       &b_NumPiMinus      );
		fTreeIn->SetBranchAddress("GResNum",           &fResNum,           &b_ResNum          );
		fTreeIn->SetBranchAddress("GDecayMode",        &fDecayMode,        &b_DecayMode       );
	}


	if(fOpt=='w'){

		fTreeIn->Branch("Event",             &fEvent, "Event/I");
		fTreeIn->Branch("NGen",              &fNGen,   "NGen/I");
		fTreeIn->Branch("GIndex",            &fGIndex          );

		//FSParticlees
		fTreeIn->Branch("NFSParticle",       &fNFS             );
		fTreeIn->Branch("FSParticleIndex",   &fFSIndex         );
		fTreeIn->Branch("FSParticlePDG",     &fFSPdg           );
		fTreeIn->Branch("FSParticleX",       &fFSPosX          );
		fTreeIn->Branch("FSParticleY",       &fFSPosY          );
		fTreeIn->Branch("FSParticleZ",       &fFSPosZ          );
		fTreeIn->Branch("FSParticleT",       &fFST             );
		fTreeIn->Branch("FSParticlePx",      &fFSMomX          );
		fTreeIn->Branch("FSParticlePy",      &fFSMomY          );
		fTreeIn->Branch("FSParticlePz",      &fFSMomZ          );
		fTreeIn->Branch("FSParticleE",       &fFSE             );

		//GTruth
		fTreeIn->Branch("GNuX",              &fNuXObj             );
		fTreeIn->Branch("GNuY",              &fNuYObj             );
		fTreeIn->Branch("GNuZ",              &fNuZObj             );
		fTreeIn->Branch("GNuT",              &fNuTObj             );

		fTreeIn->Branch("GWeight",           &fWeightObj 	       );
		fTreeIn->Branch("GProbability",      &fProbabilityObj     );
		fTreeIn->Branch("GXsec",   	         &fXsecObj    	       );
		fTreeIn->Branch("GDiffXsec",         &fDiffXsecObj        );
		fTreeIn->Branch("GGPhaseSpace",      &fGPhaseSpaceObj     );
		fTreeIn->Branch("GProbePDG",         &fProbePDGObj 	   );

		fTreeIn->Branch("GProbePx",          &fProbePxObj         );
		fTreeIn->Branch("GProbePy",          &fProbePyObj         );
		fTreeIn->Branch("GProbePz",          &fProbePzObj         );
		fTreeIn->Branch("GProbeE ",          &fProbeEObj          );

		fTreeIn->Branch("GTgtPx",            &fTgtPxObj           );
		fTreeIn->Branch("GTgtPy",            &fTgtPyObj           );
		fTreeIn->Branch("GTgtPz",            &fTgtPzObj           );
		fTreeIn->Branch("GTgtE ",            &fTgtEObj            );

		fTreeIn->Branch("GTgtZ",             &fTgtZObj            );
		fTreeIn->Branch("GTgtA",             &fTgtAObj            );
		fTreeIn->Branch("GTgtPDG",           &fTgtPDGObj          );
		fTreeIn->Branch("GHitNucPDG ",       &fHitNucPDGObj       );
		fTreeIn->Branch("GHitQrkPDG ",       &fHitQrkPDGObj       );
		fTreeIn->Branch("GIsSeaQuark",       &fIsSeaQuarkObj      );

		fTreeIn->Branch("GHitNucPx",         &fHitNucPxObj        );
		fTreeIn->Branch("GHitNucPy",         &fHitNucPyObj        );
		fTreeIn->Branch("GHitNucPz",         &fHitNucPzObj        );
		fTreeIn->Branch("GHitNucE",          &fHitNucEObj         );
		fTreeIn->Branch("GHitNucPos",        &fHitNucPosObj       );

		fTreeIn->Branch("GGscatter",         &fGscatterObj        );
		fTreeIn->Branch("GGint",             &fGintObj            );
		fTreeIn->Branch("GGQ2",              &fGQ2Obj             );
		fTreeIn->Branch("GGq2",              &fGq2Obj             );
		fTreeIn->Branch("GGW",               &fGWObj              );
		fTreeIn->Branch("GGT",               &fGTObj              );
		fTreeIn->Branch("GGX",               &fGXObj              );
		fTreeIn->Branch("GGY",               &fGYObj              );

		fTreeIn->Branch("GFSleptonPx",       &fFSleptonPxObj      );
		fTreeIn->Branch("GFSleptonPy",       &fFSleptonPyObj      );
		fTreeIn->Branch("GFSleptonPz",       &fFSleptonPzObj      );
		fTreeIn->Branch("GFSleptonE",        &fFSleptonEObj       );

		fTreeIn->Branch("GFShadSystPx",      &fFShadSystPxObj     );
		fTreeIn->Branch("GFShadSystPy",      &fFShadSystPyObj     );
		fTreeIn->Branch("GFShadSystPz",      &fFShadSystPzObj     );
		fTreeIn->Branch("GFShadSystE",       &fFShadSystEObj      );

		fTreeIn->Branch("GIsCharm",          &fIsCharmObj         );
		fTreeIn->Branch("GCharmHadronPDG",   &fCharmHadronPDGObj  );
		fTreeIn->Branch("GIsStrange",        &fIsStrangeObj       );
		fTreeIn->Branch("GStrangeHadronPDG", &fStrangeHadronPDGObj);
		fTreeIn->Branch("GNumProton",        &fNumProtonObj       );
		fTreeIn->Branch("GNumNeutron",       &fNumNeutronObj      );
		fTreeIn->Branch("GNumPi0",           &fNumPi0Obj          );
		fTreeIn->Branch("GNumPiPlus",        &fNumPiPlusObj       );
		fTreeIn->Branch("GNumPiMinus",       &fNumPiMinusObj      );
		fTreeIn->Branch("GResNum",           &fResNumObj          );
		fTreeIn->Branch("GDecayMode",        &fDecayModeObj       );
	}

	return true;
}

//implement accessors inherited from GenTree
const UInt_t FlatGenTree::NGen() const {
	return fNGen;
}

const UInt_t FlatGenTree::NFSParticles( UInt_t igen ) const {
    return fNFS->at(igen);
}

const Bool_t FlatGenTree::IsGenie( UInt_t igen ) const {

    if (fGIndex->at(igen) >-1)
    	return kTRUE;
    else
    	return kFALSE;
}

const Bool_t FlatGenTree::IsCC( UInt_t igen ) const {

    if(IsGenie(igen))
        return fGint->at(igen) == 2;

    return kFALSE;
}

const Int_t FlatGenTree::NuPDG( UInt_t igen ) const {
    return fProbePDG->at(igen);
}

TLorentzVector* FlatGenTree::NuP(const UInt_t igen) {

	if(!IsGenie(igen))
		return nullptr;

	fNuP.SetPxPyPzE(fProbePx->at(igen), fProbePy->at(igen),
					fProbePz->at(igen), fProbeE->at(igen));
	return &fNuP;
}

TLorentzVector* FlatGenTree::NuVertex(const UInt_t igen) {

	if(!IsGenie(igen))
	    return nullptr;

	fNuVertex.SetXYZT(fNuX->at(igen), fNuY->at(igen),
			          fNuZ->at(igen), fNuT->at(igen));

	return &fNuVertex;
}

const Float_t FlatGenTree::FSEnergy(const UInt_t igen) const {

    Float_t e = 0.;
    for(UInt_t i = fGenToFSLimits[igen].first; i < fGenToFSLimits[igen].second + 1; i++){
        e += fFSE->at(i);
    }
    return e;
}

 void FlatGenTree::FSParticlesFromGTruth(size_t igen, vector<UInt_t>& fsindex){}

 void FlatGenTree::FindFSLimits() {

	 if(fOpt!='r')
		 return;
	 std::cout << "FindFSLimits called" << std::endl;

	 if(fGenToFSLimits.size()!=0){
		 std::cerr << "FlatGenTree::FindFSLimits: fGenToFSLimits has already been filled"
				   << std::endl;
		 return;
	 }

     //it should be the case that FSParticle vecs are filled consecutively for each igen
	 fsBegin beg = 0;
	 fsEnd end =0;
	 if(fNGen>0){
		 std::cout << "In FindFSLimits, about to loop over " << fNGen << " igen" << std::endl;
	 }
	 else {
		 std::cerr << "FlatGenTree::FindFSLimits: bad NGen ("
				   << fNGen << ")" << std::endl;
		 return;
	 }

	 for(UInt_t igen=1; igen<fNGen+1; igen++){

		 end = fNFS->at(igen-1) - 1 + beg;
		 std::cout << "igen = " << igen << ", beg = " << beg
				   << ", end = " << end << ", NFS = "
				   << fNFS->back() << std::endl;;
		 std::pair<fsBegin,fsEnd> limits = {beg,end};
		 fGenToFSLimits.push_back(limits);

		 if(igen<fNGen)
			 beg = fNFS->at(igen);
	 }

	 std::cout << "done with FSLimits." << std::endl;
 }

 void FlatGenTree::SetVecs() {

	 fNFS               = /*new vector<UInt_t>();*/ &(fNFSObj);
	 fFSIndex           = /*new vector<UInt_t>();*/ &(fFSIndexObj);
	 fFSPdg             = /*new vector<UInt_t>();*/ &(fFSPdgObj);
	 fFSPosX            = /*new vector<Float_t>();*/ &(fFSPosXObj);
	 fFSPosY            = /*new vector<Float_t>();*/ &(fFSPosYObj);
	 fFSPosZ            = /*new vector<Float_t>();*/ &(fFSPosZObj);
	 fFST               = /*new vector<Float_t>();*/ &(fFSTObj);
	 fFSMomX            = /*new vector<Float_t>();*/ &(fFSMomXObj);
	 fFSMomY            = /*new vector<Float_t>();*/ &(fFSMomYObj);
	 fFSMomZ            = /*new vector<Float_t>();*/ &(fFSMomZObj);
	 fFSE               = /*new vector<Float_t>();*/ &(fFSEObj);

	 fNuX               = /*new vector<double>();*/ &(fNuXObj);
	 fNuY               = /*new vector<double>();*/ &(fNuYObj);
	 fNuZ               = /*new vector<double>();*/ &(fNuZObj);
	 fNuT               = /*new vector<double>();*/ &(fNuTObj);

	 fWeight            = /*new vector<double>();*/ &(fWeightObj);
	 fProbability       = /*new vector<double>();*/ &(fProbabilityObj);
	 fXsec              = /*new vector<double>();*/ &(fXsecObj);
	 fDiffXsec          = /*new vector<double>();*/ &(fDiffXsecObj);
	 fGPhaseSpace       = /*new vector<int>();*/ &(fGPhaseSpaceObj);
	 fProbePDG          = /*new vector<int>();*/ &(fProbePDGObj);

	 fProbePx           = /*new vector<double>();*/ &(fProbePxObj);
	 fProbePy           = /*new vector<double>();*/ &(fProbePyObj);
	 fProbePz           = /*new vector<double>();*/ &(fProbePzObj);
	 fProbeE            = /*new vector<double>();*/ &(fProbeEObj);

	 fTgtPx             = /*new vector<double>();*/ &(fTgtPxObj);
	 fTgtPy             = /*new vector<double>();*/ &(fTgtPyObj);
	 fTgtPz             = /*new vector<double>();*/ &(fTgtPzObj);
	 fTgtE              = /*new vector<double>();*/ &(fTgtEObj);

	 fTgtZ              = /*new vector<int>();*/ &(fTgtZObj);
	 fTgtA              = /*new vector<int>();*/ &(fTgtAObj);
	 fTgtPDG            = /*new vector<int>();*/ &(fTgtPDGObj);
	 fHitNucPDG         = /*new vector<int>();*/ &(fHitNucPDGObj);
	 fHitQrkPDG         = /*new vector<int>();*/ &(fHitQrkPDGObj);
	 fIsSeaQuark        = /*new vector<bool>();*/ &(fIsSeaQuarkObj);

	 fHitNucPx          = /*new vector<double>();*/ &(fHitNucPxObj);
	 fHitNucPy          = /*new vector<double>();*/ &(fHitNucPyObj);
	 fHitNucPz          = /*new vector<double>();*/ &(fHitNucPzObj);
	 fHitNucE           = /*new vector<double>();*/ &(fHitNucEObj);
	 fHitNucPos         = /*new vector<double>();*/ &(fHitNucPosObj);

	 fGscatter          = /*new vector<int>();*/ &(fGscatterObj);
	 fGint              = /*new vector<int>();*/ &(fGintObj);
	 fGQ2               = /*new vector<double>();*/ &(fGQ2Obj);
	 fGq2               = /*new vector<double>();*/ &(fGq2Obj);
	 fGW                = /*new vector<double>();*/ &(fGWObj);
	 fGT                = /*new vector<double>();*/ &(fGTObj);
	 fGX                = /*new vector<double>();*/ &(fGXObj);
	 fGY                = /*new vector<double>();*/ &(fGYObj);

	 fFSleptonPx        = /*new vector<double>();*/ &(fFSleptonPxObj);
	 fFSleptonPy        = /*new vector<double>();*/ &(fFSleptonPyObj);
	 fFSleptonPz        = /*new vector<double>();*/ &(fFSleptonPzObj);
	 fFSleptonE         = /*new vector<double>();*/ &(fFSleptonEObj);

	 fFShadSystPx       = /*new vector<double>();*/ &(fFShadSystPxObj);
	 fFShadSystPy       = /*new vector<double>();*/ &(fFShadSystPyObj);
	 fFShadSystPz       = /*new vector<double>();*/ &(fFShadSystPzObj);
	 fFShadSystE        = /*new vector<double>();*/ &(fFShadSystEObj);

	 fIsCharm           = /*new vector<bool>();*/ &(fIsCharmObj);
	 fCharmHadronPDG    = /*new vector<int>();*/ &(fCharmHadronPDGObj);
	 fIsStrange         = /*new vector<bool>();*/ &(fIsStrangeObj);
	 fStrangeHadronPDG  = /*new vector<int>();*/ &(fStrangeHadronPDGObj);
	 fNumProton         = /*new vector<int>();*/ &(fNumProtonObj);
	 fNumNeutron        = /*new vector<int>();*/ &(fNumNeutronObj);
	 fNumPi0            = /*new vector<int>();*/ &(fNumPi0Obj);
	 fNumPiPlus         = /*new vector<int>();*/ &(fNumPiPlusObj);
	 fNumPiMinus        = /*new vector<int>();*/ &(fNumPiMinusObj);
	 fResNum            = /*new vector<int>();*/ &(fResNumObj);
	 fDecayMode         = /*new vector<int>();*/ &(fDecayModeObj);

 }

 void FlatGenTree::ClearVecs() {

	 fNFS->clear();
	 fFSIndex->clear();
	 fFSPdg->clear();
	 fFSPosX->clear();
	 fFSPosY->clear();
	 fFSPosZ->clear();
	 fFST->clear();
	 fFSMomX->clear();
	 fFSMomY->clear();
	 fFSMomZ->clear();
	 fFSE->clear();

	 fNuX->clear();
	 fNuY->clear();
	 fNuZ->clear();
	 fNuT->clear();

	 fWeight->clear();
	 fProbability->clear();
	 fXsec->clear();
	 fDiffXsec->clear();
	 fGPhaseSpace->clear();
	 fProbePDG->clear();

	 fProbePx->clear();
	 fProbePy->clear();
	 fProbePz->clear();
	 fProbeE->clear();

	 fTgtPx->clear();
	 fTgtPy->clear();
	 fTgtPz->clear();
	 fTgtE->clear();

	 fTgtZ->clear();
	 fTgtA->clear();
	 fTgtPDG->clear();
	 fHitNucPDG->clear();
	 fHitQrkPDG->clear();
	 fIsSeaQuark->clear();

	 fHitNucPx->clear();
	 fHitNucPy->clear();
	 fHitNucPz->clear();
	 fHitNucE->clear();
	 fHitNucPos->clear();

	 fGscatter->clear();
	 fGint->clear();
	 fGQ2->clear();
	 fGq2->clear();
	 fGW->clear();
	 fGT->clear();
	 fGX->clear();
	 fGY->clear();

	 fFSleptonPx->clear();
	 fFSleptonPy->clear();
	 fFSleptonPz->clear();
	 fFSleptonE ->clear();

	 fFShadSystPx->clear();
	 fFShadSystPy->clear();
	 fFShadSystPz->clear();
	 fFShadSystE->clear();

	 fIsCharm->clear();
	 fCharmHadronPDG->clear();
	 fIsStrange->clear();
	 fStrangeHadronPDG->clear();
	 fNumProton->clear();
	 fNumNeutron->clear();
	 fNumPi0->clear();
	 fNumPiPlus->clear();
	 fNumPiMinus->clear();
	 fResNum->clear();
	 fDecayMode->clear();

 }
