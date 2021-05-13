////////////////////////////////////////////////////////////////////////
/// \file  GTruth.h
/// \Class to hold the additional information needed to recreate a genie::EventRecord
/// \author  nathan.mayer@tufts.edu
/// \importer chilgenb@umn.edu
////////////////////////////////////////////////////////////////////////

/// This class stores/retrieves the additional information needed
/// (and not in MCTruth) to recreate a genie::EventRecord
/// for genie based event reweighting.
/// Imported from LArSoft on 2021 Feb 09

#ifndef GARANA_GTRUTH_H
#define GARANA_GTRUTH_H

#include <iostream>
#include <TLorentzVector.h>

namespace garana {

  class GTruth {

  public:
    GTruth();

    int            fVertexRegion; ///< region code where vertex is located

    // genie::GHepRecord info
    // holds a genie::Interaction

    TLorentzVector fVertex;
    double         fweight;       ///< event interaction weight (genie internal)
    double         fprobability;  ///< interaction probability
    double         fXsec;         ///< cross section of interaction
    double         fDiffXsec;     ///< differential cross section of interaction
    int            fGPhaseSpace;  ///< phase space system of DiffXSec

    // genie:::InitialState info (sub-object to genie::Interactions)
    int            fProbePDG;
    TLorentzVector fProbeP4;
    TLorentzVector fTgtP4;

    // genie::Target info (sub-object to genie::InitialState)
    int            ftgtZ;
    int            ftgtA;
    int            ftgtPDG;       ///< PDG of Target Nucleus, nucleon only if free
    int            fHitNucPDG;    ///< hit nucleon PDG code
    int            fHitQrkPDG;    ///< hit quark PDG code
    bool           fIsSeaQuark;
    TLorentzVector fHitNucP4;
    double         fHitNucPos;

    // genie::ProcessInfo (sub-object to genie::Interactions)
    int            fGscatter;     ///< neutrino scattering code
    int            fGint;         ///< interaction code

    // genie::Kinematics info (sub-object to genie::Interactions)
    ///< these are for the internal (on shell) genie kinematics
    double         fgQ2;
    double         fgq2;
    double         fgW;
    double         fgT;
    double         fgX;
    double         fgY;
    TLorentzVector fFSleptonP4;   ///< generated final state primary lepton (LAB frame) // added version 13
    TLorentzVector fFShadSystP4;  ///< generated final state hadronic system (LAB frame)

    // genie::XclsTag info (sub-object to genie::Interactions)
    bool           fIsCharm;      ///< did the interaction produce a charmed hadron?
    int            fCharmHadronPdg;                             // added version 13
    bool           fIsStrange;    ///< strange production       // added version 13
    int            fStrangeHadronPdg;                           // added version 13
    int            fNumProton;    ///< number of protons after reaction, before FSI
    int            fNumNeutron;   ///< number of neutrons after reaction, before FSI
    int            fNumPi0;       ///< number of pi0 after reaction, before FSI
    int            fNumPiPlus;    ///< number of pi pluses after reaction, before FSI
    int            fNumPiMinus;   ///< number of pi minuses after reaction, before FSI
    int            fResNum;       ///< resonance number
    int            fDecayMode;                                  // added version 13

	#ifndef __GCCXML__
    // Flag for values that might not have been set
    static constexpr double kUndefinedValue = -99999;

    friend std::ostream& operator<< (std::ostream& output, const garana::GTruth &gtruth);

    bool IsFilled();

	#endif
  }; //class GTruth
} // end garana namespace

#endif // GARANA_GTRUTH_H
