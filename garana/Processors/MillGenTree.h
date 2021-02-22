#ifndef GARANA_MILL_GENTREE_H
#define GARANA_MILL_GENTREE_H

#include "garana/Accessors/FlatGenTree.h"
#include "garana/Accessors/StructuredGenTree.h"
//#include garana/DataProducts/FSParticle.h"
//#include garana/DataProducts/GTruth.h"
#include "garana/Processors/Mill.h"

#include <vector>
#include <string>
#include <climits>

using std::vector;

namespace garana {

	class MillGenTree : public Mill, public FlatGenTree {

	 public:

		MillGenTree(){};
		MillGenTree(TTree* treeIn, TTree* treeOut);

		void MillTrees() override;

	 private:

		bool VerifyBranches() override;
		void FillGTruth(const GTruth* truth);
		void FillEmptyGTruth();
		void FillFSParticle(const vector<FSParticle>* fsp);

		StructuredGenTree* fGenIn  = nullptr;
		//FlatGenTree*       fGenOut = nullptr;

		//known branches, need to update if tree structure changes
		//  in garsoft/Ana/StructuredTree_module.cc
		enum GenBranch {
			kEvent,
			kGIndex,
			kGTruth,
			kFSParticle
		};//

		std::map<std::string,GenBranch> nameToGenBranch =	{
			{"Event",      kEvent},
			{"GIndex",     kGIndex},
			{"GTruth",     kGTruth},
			{"FSParticles", kFSParticle}
		};//

		std::map<GenBranch,bool> branchToDrawOpt = {
		    {kEvent,      false},
			{kGIndex,     false},
			{kGTruth,     false},
			{kFSParticle, false}
		};

		// leaves for output tree (maybe there is a more sophisticated solution
		// using inheritance from GTruth.h / FSParticle.h)

		/*vector<Int_t> fGIndex; ///index of ith entry


		/// FSParticle (one per GTruth per genTree entry) //
		vector<Int_t>  fNFS;     ///< number of FS particles associated with ith entry
		vector<Int_t>  fFSIndex; ///< index of FS particle associated with ith entry
		vector<int>    fFSPdg;   ///< particle PDG code
		vector<double> fFSPosX;  ///< final particle x-position in lab frame [cm]
		vector<double> fFSPosY;  ///< final particle y-position in lab frame [cm]
		vector<double> fFSPosZ;  ///< final particle z-position in lab frame [cm]
		vector<double> fFST;     ///< final particle time in lab frame [ns]
		vector<double> fFSMomX;  ///< final particle 4-momentum in lab frame [GeV/c]
		vector<double> fFSMomY;  ///< final particle 4-momentum in lab frame [GeV/c]
		vector<double> fFSMomZ;  ///< final particle z-momentum in lab frame [GeV/c]
		vector<double> fFSE;     ///< final particle total energy in lab frame [GeV]

		/// GTruth (one or more per genTree entry) //
	    vector<double>         fNuX; ///<
	    vector<double>         fNuY; ///<
	    vector<double>         fNuZ; ///<
	    vector<double>         fNuT; ///<

	    vector<double>         fweight;      ///<
	    vector<double>         fprobability; ///<
	    vector<double>         fXsec;        ///<
	    vector<double>         fDiffXsec;    ///<
	    vector<int>            fGPhaseSpace; ///<
	    vector<int>            fProbePDG;    ///<

	    vector<double>         fProbePx; ///<
	    vector<double>         fProbePy; ///<
	    vector<double>         fProbePz; ///<
	    vector<double>         fProbeE;  ///<

	    vector<double>         fTgtPx; ///<
	    vector<double>         fTgtPy; ///<
	    vector<double>         fTgtPz; ///<
	    vector<double>         fTgtE;  ///<

	    vector<int>            ftgtZ;       ///<
	    vector<int>            ftgtA;       ///<
	    vector<int>            ftgtPDG;     ///<
	    vector<int>            fHitNucPDG;  ///<
	    vector<int>            fHitQrkPDG;  ///<
	    vector<bool>           fIsSeaQuark; ///<
                                            ///<
	    vector<double>         fHitNucPx;  ///<
	    vector<double>         fHitNucPy;  ///<
	    vector<double>         fHitNucPz;  ///<
	    vector<double>         fHitNucE;   ///<
	    vector<double>         fHitNucPos; ///<

	    vector<int>            fGscatter; ///<
	    vector<int>            fGint;     ///<
	    vector<double>         fgQ2;      ///<
	    vector<double>         fgq2;      ///<
	    vector<double>         fgW;       ///<
	    vector<double>         fgT;       ///<
	    vector<double>         fgX;       ///<
	    vector<double>         fgY;       ///<

	    vector<double>         fFSleptonPx; ///<
	    vector<double>         fFSleptonPy; ///<
	    vector<double>         fFSleptonPz; ///<
	    vector<double>         fFSleptonE;  ///<

	    vector<double>         fFShadSystPx; ///<
	    vector<double>         fFShadSystPy; ///<
	    vector<double>         fFShadSystPz; ///<
	    vector<double>         fFShadSystE;  ///<

	    vector<bool>           fIsCharm;          ///<
	    vector<int>            fCharmHadronPdg;   ///<
	    vector<bool>           fIsStrange;        ///<
	    vector<int>            fStrangeHadronPdg; ///<
	    vector<int>            fNumProton;        ///<
	    vector<int>            fNumNeutron;       ///<
	    vector<int>            fNumPi0;           ///<
	    vector<int>            fNumPiPlus;        ///<
	    vector<int>            fNumPiMinus;       ///<
	    vector<int>            fResNum;           ///<
	    vector<int>            fDecayMode;        ///<*/
        // \GTruth


	};//class

}//namespace

#endif /* GARANA_MILL_GENTREE_H */
