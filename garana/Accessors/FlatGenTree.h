/*
 * FlatGenTree.h
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_FLATGENTREE_H_
#define GARANA_FLATGENTREE_H_

#include "garana/Base/GenTree.h"

#include <utility>


using std::vector;

namespace garana {

 class FlatGenTree : public GenTree {

  public:

	FlatGenTree() {}
	FlatGenTree(TTree* tree);
	FlatGenTree(TTree* tree, char opt);

    //accessors inherited from GenTree
    const UInt_t          NGen()                            const override;
    const UInt_t          NFSParticles(const UInt_t& igen ) const override;
    const Bool_t          IsGenie(const UInt_t& igen )      const override;

    const Bool_t          IsCC(const UInt_t& igen )         const override;
    const Int_t           NuPDG(const UInt_t& igen )        const override;
    const TLorentzVector* NuP(const UInt_t& igen)                 override;
    const TLorentzVector* NuVertex(const UInt_t& igen)            override;

    const int             ScatterCode(const UInt_t& igen)   const override;
    const int             InteractCode(const UInt_t& igen)  const override;

    const Int_t           TgtPDG(const UInt_t& igen )       const override;
    const TLorentzVector* TgtP4(const UInt_t& igen)         const override;
    const int             TgtZ(const UInt_t& igen )         const override;
    const int             TgtA(const UInt_t& igen )         const override;
    const int             HitNucPDG(const UInt_t& igen )    const override;
    const TLorentzVector* HitNucP4(const UInt_t& igen )     const override;

    const double          Q2(const UInt_t& igen )           const override;
    const double          q2(const UInt_t& igen )           const override;
    const double          W(const UInt_t& igen )            const override;
    const double          T(const UInt_t& igen )            const override;
    const double          X(const UInt_t& igen )            const override;
    const double          Y(const UInt_t& igen )            const override;
    const TLorentzVector* FSLeptonP4(const UInt_t& igen )   const override;
    const TLorentzVector* FSHadSystP4(const UInt_t& igen )  const override;

    const int             NumNuProton(const UInt_t& igen)   const override;
    const int             NumNuNeutron(const UInt_t& igen)  const override;
    const int             NumNuPi0(const UInt_t& igen)      const override;
    const int             NumNuPiPlus(const UInt_t& igen)   const override;
    const int             NumNuPiMinus(const UInt_t& igen)  const override;

    const Float_t         FSTotEnergy(const UInt_t& igen)      const override;
    const Float_t         FSEnergy(const UInt_t& igen, const UInt_t& ifsp)      const override;
    const Float_t         FSPDG(const UInt_t& igen, const UInt_t& ifsp)         const override;
    const Int_t           FSTrackId(const UInt_t& igen, const UInt_t& ifsp)     const override;

    void GetEntry(const UInt_t& ientry) override;

    //private:
  protected:

    bool SetBranchAddresses() override;
    void FindFSLimits();
    std::pair<UInt_t,UInt_t> FSParticlesFromGTruth(size_t igen) const;
    void SetVecs();
    void ClearVecs();

    typedef UInt_t fsLimit;
    typedef fsLimit fsBegin;
    typedef fsLimit fsEnd;
	vector< std::pair< fsBegin, fsEnd > > fGenToFSLimits;

    TLorentzVector   fNuP;
    TLorentzVector   fNuVertex;

    // leaves
    Int_t            fNGen        = -1;
    const vector<Int_t>*   fGIndex      = nullptr;

    //vector objects (used only if fOpt == 'w')
    vector<UInt_t>    fNFSObj;  ///< number of FSParticles for igen^th GTruth len=NGen
    vector<UInt_t>    fFSIndexObj;  ///<
    vector<UInt_t>    fFSPdgObj;  ///< particle PDG code
    vector<Float_t>  fFSPosXObj;  ///< x-coordinate [cm]
    vector<Float_t>  fFSPosYObj;  ///< y-coordinate [cm]
    vector<Float_t>  fFSPosZObj;  ///< z-coordinate [cm]
    vector<Float_t>  fFSTObj;  ///< time [ns]
    vector<Float_t>  fFSMomXObj;  ///< momentum, x-component [GeV/c]
    vector<Float_t>  fFSMomYObj;  ///< momentum, y-component [GeV/c]
    vector<Float_t>  fFSMomZObj;  ///< momentum, z-component [GeV/c]
    vector<Float_t>  fFSEObj;  ///< total energy [GeV]

	/// GTruth (one or more per genTree entry) //
    vector<double>   fNuXObj; ///<
    vector<double>   fNuYObj; ///<
    vector<double>   fNuZObj; ///<
    vector<double>   fNuTObj; ///<

    vector<double>   fWeightObj; ///<
    vector<double>   fProbabilityObj; ///<
    vector<double>   fXsecObj; ///<
    vector<double>   fDiffXsecObj; ///<
    vector<int>      fGPhaseSpaceObj; ///<
    vector<int>      fProbePDGObj; ///<

    vector<double>   fProbePxObj; ///<
    vector<double>   fProbePyObj; ///<
    vector<double>   fProbePzObj; ///<
    vector<double>   fProbeEObj; ///<

    vector<double>   fTgtPxObj; ///<
    vector<double>   fTgtPyObj; ///<
    vector<double>   fTgtPzObj; ///<
    vector<double>   fTgtEObj; ///<

    vector<int>      fTgtZObj;  ///<
    vector<int>      fTgtAObj;  ///<
    vector<int>      fTgtPDGObj;  ///<
    vector<int>      fHitNucPDGObj;  ///<
    vector<int>      fHitQrkPDGObj;  ///<
    vector<bool>     fIsSeaQuarkObj;  ///<

    vector<double>   fHitNucPxObj; ///<
    vector<double>   fHitNucPyObj; ///<
    vector<double>   fHitNucPzObj; ///<
    vector<double>   fHitNucEObj; ///<
    vector<double>   fHitNucPosObj; ///<

    vector<int>      fGscatterObj; ///<
    vector<int>      fGintObj;     ///<
    vector<double>   fGQ2Obj;      ///<
    vector<double>   fGq2Obj;      ///<
    vector<double>   fGWObj;       ///<
    vector<double>   fGTObj;       ///<
    vector<double>   fGXObj;       ///<
    vector<double>   fGYObj;       ///<

    vector<double>   fFSleptonPxObj; ///<
    vector<double>   fFSleptonPyObj; ///<
    vector<double>   fFSleptonPzObj; ///<
    vector<double>   fFSleptonEObj;  ///<

    vector<double>   fFShadSystPxObj; ///<
    vector<double>   fFShadSystPyObj; ///<
    vector<double>   fFShadSystPzObj; ///<
    vector<double>   fFShadSystEObj;  ///<

    vector<bool>     fIsCharmObj;          ///<
    vector<int>      fCharmHadronPDGObj;   ///<
    vector<bool>     fIsStrangeObj;        ///<
    vector<int>      fStrangeHadronPDGObj; ///<
    vector<int>      fNumProtonObj;        ///<
    vector<int>      fNumNeutronObj;       ///<
    vector<int>      fNumPi0Obj;           ///<
    vector<int>      fNumPiPlusObj;        ///<
    vector<int>      fNumPiMinusObj;       ///<
    vector<int>      fResNumObj;           ///<
    vector<int>      fDecayModeObj;        ///<

    //vector pointers
    //final state particles
    vector<UInt_t>*  fNFS              = nullptr;  ///< number of FSParticles for igen^th GTruth len=NGen
    vector<UInt_t>*  fFSIndex          = nullptr;  ///<
    vector<UInt_t>*  fFSTrackId        = nullptr;  ///< particle generator track ID
    vector<UInt_t>*  fFSPdg            = nullptr;  ///< particle PDG code
    vector<Float_t>* fFSPosX           = nullptr;  ///< x-coordinate [cm]
    vector<Float_t>* fFSPosY           = nullptr;  ///< y-coordinate [cm]
    vector<Float_t>* fFSPosZ           = nullptr;  ///< z-coordinate [cm]
    vector<Float_t>* fFST              = nullptr;  ///< time [ns]
    vector<Float_t>* fFSMomX           = nullptr;  ///< momentum, x-component [GeV/c]
    vector<Float_t>* fFSMomY           = nullptr;  ///< momentum, y-component [GeV/c]
    vector<Float_t>* fFSMomZ           = nullptr;  ///< momentum, z-component [GeV/c]
    vector<Float_t>* fFSE              = nullptr;  ///< total energy [GeV]

	/// GTruth (one or more per genTree entry) //
    vector<double>*  fNuX              = nullptr; ///<
    vector<double>*  fNuY              = nullptr; ///<
    vector<double>*  fNuZ              = nullptr; ///<
    vector<double>*  fNuT              = nullptr; ///<

    vector<double>*  fWeight           = nullptr; ///<
    vector<double>*  fProbability      = nullptr; ///<
    vector<double>*  fXsec             = nullptr; ///<
    vector<double>*  fDiffXsec         = nullptr; ///<
    vector<int>*     fGPhaseSpace      = nullptr; ///<
    vector<int>*     fProbePDG         = nullptr; ///<

    vector<double>*  fProbePx          = nullptr; ///<
    vector<double>*  fProbePy          = nullptr; ///<
    vector<double>*  fProbePz          = nullptr; ///<
    vector<double>*  fProbeE           = nullptr; ///<

    vector<double>*  fTgtPx            = nullptr; ///<
    vector<double>*  fTgtPy            = nullptr; ///<
    vector<double>*  fTgtPz            = nullptr; ///<
    vector<double>*  fTgtE             = nullptr; ///<

    vector<int>*     fTgtZ             = nullptr;  ///<
    vector<int>*     fTgtA             = nullptr;  ///<
    vector<int>*     fTgtPDG           = nullptr;  ///<
    vector<int>*     fHitNucPDG        = nullptr;  ///<
    vector<int>*     fHitQrkPDG        = nullptr;  ///<
    vector<bool>*    fIsSeaQuark       = nullptr;  ///<

    vector<double>*  fHitNucPx         = nullptr; ///<
    vector<double>*  fHitNucPy         = nullptr; ///<
    vector<double>*  fHitNucPz         = nullptr; ///<
    vector<double>*  fHitNucE          = nullptr; ///<
    vector<double>*  fHitNucPos        = nullptr; ///<

    vector<int>*     fGscatter         = nullptr; ///<
    vector<int>*     fGint             = nullptr;     ///<
    vector<double>*  fGQ2              = nullptr;      ///<
    vector<double>*  fGq2              = nullptr;      ///<
    vector<double>*  fGW               = nullptr;       ///<
    vector<double>*  fGT               = nullptr;       ///<
    vector<double>*  fGX               = nullptr;       ///<
    vector<double>*  fGY               = nullptr;       ///<

    vector<double>*  fFSleptonPx       = nullptr; ///<
    vector<double>*  fFSleptonPy       = nullptr; ///<
    vector<double>*  fFSleptonPz       = nullptr; ///<
    vector<double>*  fFSleptonE        = nullptr;  ///<

    vector<double>*  fFShadSystPx      = nullptr; ///<
    vector<double>*  fFShadSystPy      = nullptr; ///<
    vector<double>*  fFShadSystPz      = nullptr; ///<
    vector<double>*  fFShadSystE       = nullptr;  ///<

    vector<bool>*    fIsCharm          = nullptr;          ///<
    vector<int>*     fCharmHadronPDG   = nullptr;   ///<
    vector<bool>*    fIsStrange        = nullptr;        ///<
    vector<int>*     fStrangeHadronPDG = nullptr; ///<
    vector<int>*     fNumProton        = nullptr;        ///<
    vector<int>*     fNumNeutron       = nullptr;       ///<
    vector<int>*     fNumPi0           = nullptr;           ///<
    vector<int>*     fNumPiPlus        = nullptr;        ///<
    vector<int>*     fNumPiMinus       = nullptr;       ///<
    vector<int>*     fResNum           = nullptr;           ///<
    vector<int>*     fDecayMode        = nullptr;        ///<

    //branches
    TBranch*       b_NGen   = nullptr;
    TBranch*       b_GIndex       = nullptr;

    TBranch* b_NFS     = nullptr;
    TBranch* b_FSIndex = nullptr;
    TBranch* b_FSPdg   = nullptr;
    TBranch* b_FSPosX  = nullptr;
    TBranch* b_FSPosY  = nullptr;
    TBranch* b_FSPosZ  = nullptr;
    TBranch* b_FST     = nullptr;
    TBranch* b_FSMomX  = nullptr;
    TBranch* b_FSMomY  = nullptr;
    TBranch* b_FSMomZ  = nullptr;
    TBranch* b_FSE     = nullptr;

    TBranch*         b_NuX = nullptr; ///<
    TBranch*         b_NuY = nullptr; ///<
    TBranch*         b_NuZ = nullptr; ///<
    TBranch*         b_NuT = nullptr; ///<

    TBranch*         b_Weight      = nullptr; ///<
    TBranch*         b_Probability = nullptr; ///<
    TBranch*         b_Xsec        = nullptr; ///<
    TBranch*         b_DiffXsec    = nullptr; ///<
    TBranch*         b_GPhaseSpace = nullptr; ///<
    TBranch*         b_ProbePDG    = nullptr; ///<

    TBranch*         b_ProbePx = nullptr; ///<
    TBranch*         b_ProbePy = nullptr; ///<
    TBranch*         b_ProbePz = nullptr; ///<
    TBranch*         b_ProbeE  = nullptr; ///<

    TBranch*         b_TgtPx = nullptr; ///<
    TBranch*         b_TgtPy = nullptr; ///<
    TBranch*         b_TgtPz = nullptr; ///<
    TBranch*         b_TgtE  = nullptr; ///<

    TBranch*         b_TgtZ       = nullptr;  ///<
    TBranch*         b_TgtA       = nullptr;  ///<
    TBranch*         b_TgtPDG     = nullptr;  ///<
    TBranch*         b_HitNucPDG  = nullptr;  ///<
    TBranch*         b_HitQrkPDG  = nullptr;  ///<
    TBranch*         b_IsSeaQuark = nullptr;  ///<

    TBranch*         b_HitNucPx  = nullptr; ///<
    TBranch*         b_HitNucPy  = nullptr; ///<
    TBranch*         b_HitNucPz  = nullptr; ///<
    TBranch*         b_HitNucE   = nullptr; ///<
    TBranch*         b_HitNucPos = nullptr; ///<

    TBranch*         b_Gscatter = nullptr; ///<
    TBranch*         b_Gint = nullptr;     ///<
    TBranch*         b_GQ2 = nullptr;      ///<
    TBranch*         b_Gq2 = nullptr;      ///<
    TBranch*         b_GW = nullptr;       ///<
    TBranch*         b_GT = nullptr;       ///<
    TBranch*         b_GX = nullptr;       ///<
    TBranch*         b_GY = nullptr;       ///<

    TBranch*         b_FSleptonPx = nullptr; ///<
    TBranch*         b_FSleptonPy = nullptr; ///<
    TBranch*         b_FSleptonPz = nullptr; ///<
    TBranch*         b_FSleptonE = nullptr;  ///<

    TBranch*         b_FShadSystPx = nullptr; ///<
    TBranch*         b_FShadSystPy = nullptr; ///<
    TBranch*         b_FShadSystPz = nullptr; ///<
    TBranch*         b_FShadSystE = nullptr;  ///<

    TBranch*         b_IsCharm = nullptr;
    TBranch*         b_CharmHadronPDG = nullptr;
    TBranch*         b_IsStrange = nullptr;
    TBranch*         b_StrangeHadronPDG = nullptr;
    TBranch*         b_NumProton = nullptr;
    TBranch*         b_NumNeutron = nullptr;
    TBranch*         b_NumPi0 = nullptr;
    TBranch*         b_NumPiPlus = nullptr;
    TBranch*         b_NumPiMinus = nullptr;
    TBranch*         b_ResNum = nullptr;
    TBranch*         b_DecayMode = nullptr;
    // \GTruth


 };//class
}//namespace

#endif /* FLATGENTREE_H_ */
