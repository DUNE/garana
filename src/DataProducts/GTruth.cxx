//////////////////////////////////////////////////////////////////
/// \file  GTruth.h
/// \Class to hold the additional information needed to recreate a genie::EventRecord
/// \author  nathan.mayer@tufts.edu
////////////////////////////////////////////////////////////////////////

/// This class stores/retrieves the additional information needed (and not in MCTruth) to recreate a genie::EventRecord
/// for genie based event reweighting.

#include "garana/DataProducts/GTruth.h"

#include <vector>
#include <iostream>
#include <string>
#include <sstream> // for ostringstream
#include <iomanip>

using namespace garana;

  //---------------------------------------------------------------
  GTruth::GTruth()
    : fVertex(0, 0, 0, 0)
    , fweight(0)
    , fprobability(0)
    , fXsec(0)
    , fDiffXsec(0)
    , fGPhaseSpace(-1)

    , fProbePDG(-1)
    , fProbeP4(0, 0, 0, 0)
    , fTgtP4(0, 0, 0, 0)

    , ftgtZ(0)
    , ftgtA(0)
    , ftgtPDG(0)
    , fHitNucPDG(kUndefinedValue)
    , fHitQrkPDG(kUndefinedValue)
    , fIsSeaQuark(false)
    , fHitNucP4(0, 0, 0, 0)
    , fHitNucPos(0)

    , fGscatter(-1)
    , fGint(-1)

    , fgQ2(kUndefinedValue)
    , fgq2(kUndefinedValue)
    , fgW(kUndefinedValue)
    , fgT(kUndefinedValue)
    , fgX(kUndefinedValue)
    , fgY(kUndefinedValue)
    , fFSleptonP4(0, 0, 0, 0)
    , fFShadSystP4(0, 0, 0, 0)

    , fIsCharm(false)
    , fCharmHadronPdg(0)
    , fIsStrange(false)
    , fStrangeHadronPdg(0)
    , fNumProton(-1)
    , fNumNeutron(-1)
    , fNumPi0(-1)
    , fNumPiPlus(-1)
    , fNumPiMinus(-1)
    , fResNum(-1)
    , fDecayMode(-1)
  {}

  bool GTruth::IsFilled(){

	  //check if all data members still initialized from default constructor
	  // note some might retain initial values so check
	  // check if all have init values

      const TLorentzVector emptyVec(0,0,0,0); //initializes to (0,0,0,0)

	  if(
	         fVertex == emptyVec
	      && fweight == 0
	      && fprobability == 0
	      && fXsec == 0
	      && fDiffXsec == 0
	      && fGPhaseSpace == -1
	      && fProbePDG == -1
	      && fProbeP4 == emptyVec
	      && fTgtP4 == emptyVec

	      && ftgtZ == 0
	      && ftgtA == 0
	      && ftgtPDG == 0
	      && fHitNucPDG == kUndefinedValue
	      && fHitQrkPDG == kUndefinedValue
	      && !fIsSeaQuark
	      && fHitNucP4 == emptyVec
	      && fHitNucPos == 0

	      && fGscatter == -1
	      && fGint == -1

	      && fgQ2 == kUndefinedValue
	      && fgq2 == kUndefinedValue
	      && fgW == kUndefinedValue
	      && fgT == kUndefinedValue
	      && fgX == kUndefinedValue
	      && fgY == kUndefinedValue
	      && fFSleptonP4 == emptyVec
	      && fFShadSystP4 == emptyVec

	      && !fIsCharm
	      && fCharmHadronPdg == 0
	      && !fIsStrange
	      && fStrangeHadronPdg == 0
	      && fNumProton == -1
	      && fNumNeutron == -1
	      && fNumPi0 == -1
	      && fNumPiPlus == -1
	      && fNumPiMinus == -1
	      && fResNum == -1
	      && fDecayMode == -1
	  ) {
		  return false;
	  }

	  return true;
  }

  namespace gtruthaux {
    std::string stringifyTLorentzVector(const TLorentzVector& tv4) {
      std::ostringstream s;
      s << "[ "
        << std::setw(11) << tv4.X() << " "
        << std::setw(11) << tv4.Y() << " "
        << std::setw(11) << tv4.Z() << " "
        << std::setw(11) << tv4.T() << " ]";
      return s.str();
    }
  }
  //......................................................................
  std::ostream&  operator<< (std::ostream& output, const garana::GTruth &gtruth)
  {
    output
      << "GTruth:" << std::endl
      //  123456789012
      << " Vertex      " << gtruthaux::stringifyTLorentzVector(gtruth.fVertex)  << std::endl
      << " weight      " << std::setw(11) << gtruth.fweight       << " "
      << "  prob       " << std::setw(11) << gtruth.fprobability  << std::endl
      << " Xsec        " << std::setw(11) << gtruth.fXsec         << " "
      << "  DiffXsec   " << std::setw(11) << gtruth.fDiffXsec     << " "
      << "  GPhaseSpace " << std::setw(9) << gtruth.fGPhaseSpace << std::endl

      << " probe       " << std::setw(11) << gtruth.fProbePDG     << std::endl
      << " ProbeP4     " << gtruthaux::stringifyTLorentzVector(gtruth.fProbeP4) << std::endl
      << " TgtP4       " << gtruthaux::stringifyTLorentzVector(gtruth.fTgtP4) << std::endl

      << " Z A PDG (nuc,qrk) " << std::setw(4)  << gtruth.ftgtZ         << " "
                         << std::setw(4)  << gtruth.ftgtA         << " "
                         << std::setw(11) << gtruth.ftgtPDG       << " ("
                         << std::setw(11) << gtruth.fHitNucPDG    << " "
                         << std::setw(11) << gtruth.fHitQrkPDG    << ") "
      << " IsSeaQuark  " << std::setw(4)  << ((gtruth.fIsSeaQuark)?"yes":"no") << std::endl
      << " HitNucP4    " << gtruthaux::stringifyTLorentzVector(gtruth.fHitNucP4) << " "
      << " HitNucPos   " << std::setw(11) << gtruth.fHitNucPos    << std::endl

      << " Gscatter    " << std::setw(11) << gtruth.fGscatter     << " "
      << "  Gint       " << std::setw(11) << gtruth.fGint         << std::endl

      << "  Q2 q2      " << std::setw(11) << gtruth.fgQ2          << " "
                         << std::setw(11) << gtruth.fgq2          << std::endl
      << "  W  T       " << std::setw(11) << gtruth.fgW           << " "
                         << std::setw(11) << gtruth.fgT           << std::endl
      << "  X  Y       " << std::setw(11) << gtruth.fgX           << " "
                         << std::setw(11) << gtruth.fgY           << std::endl
      << " FSlepton    " << gtruthaux::stringifyTLorentzVector(gtruth.fFSleptonP4) << std::endl
      << " FShadSyst   " << gtruthaux::stringifyTLorentzVector(gtruth.fFShadSystP4) << std::endl

      << "  IsCharm    " << std::setw(4)  << ((gtruth.fIsCharm)?"yes":"no")   << " "
      << "  CharmPDG   " << std::setw(6)  << gtruth.fCharmHadronPdg         << " "
      << "  IsStrange  " << std::setw(4)  << ((gtruth.fIsStrange)?"yes":"no") << " "
      << "  StrangePDG " << std::setw(6)  << gtruth.fStrangeHadronPdg         << std::endl
      << "  Np Nn      " << std::setw(4)  << gtruth.fNumProton    << " "
                         << std::setw(4)  << gtruth.fNumNeutron   << " "
      << "  Npi(0,+,-) " << std::setw(4)  << gtruth.fNumPi0       << " "
                         << std::setw(4)  << gtruth.fNumPiPlus    << " "
                         << std::setw(4)  << gtruth.fNumPiMinus   << std::endl
      << "  ResNum     " << std::setw(4)  << gtruth.fResNum       << " "
      << "  DecayMode  " << std::setw(4)  << gtruth.fDecayMode    << std::endl

      << std::endl ;

    return output;
  }

  ClassImp(GTruth)
