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

#pragma once

#include <iostream>
#include <TLorentzVector.h>
#include <TROOT.h>

namespace garana {

  class GTruth: public TObject {

  public:
    GTruth();

    // genie::GHepRecord info
    // holds a genie::Interaction
    TLorentzVector fVertex;
    // skipping TBits data members  EventFlags and EventMask
    double         fweight;       ///< event interaction weight (genie internal)
    double         fprobability;  ///< interaction probability
    double         fXsec;         ///< cross section of interaction
    double         fDiffXsec;     ///< differential cross section of interaction
    int            fGPhaseSpace;  ///< phase space system of DiffXSec

    // genie::Interaction
    //   container for InitialState, ProcessInfo, XclsTag, Kinematics, KPhaseSpace)
    //   holds no fundamental type info

    // genie:::InitialState info (sub-object to genie::Interactions)
    int            fProbePDG;
    // holds a genie::Target
    TLorentzVector fProbeP4;
    TLorentzVector fTgtP4;                                      // added version 13

    // genie::Target info (sub-object to genie::InitialState)
    int            ftgtZ;
    int            ftgtA;
    int            ftgtPDG;       ///< PDG of Target Nucleus, nucleon only if free
    int            fHitNucPDG;    ///< hit nucleon PDG code     // added version 13
    int            fHitQrkPDG;    ///< hit quark PDG code       // added version 13
    bool           fIsSeaQuark;
    TLorentzVector fHitNucP4;
    double         fHitNucPos;                                  // added version 12

    // genie::ProcessInfo (sub-object to genie::Interactions)
    int            fGscatter;     ///< neutrino scattering code
    int            fGint;         ///< interaction code

    // genie::Kinematics info (sub-object to genie::Interactions)
    ///< these are for the internal (on shell) genie kinematics
    ///<   this list might be an incomplete transcription of map<KineVar_t,double>
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

    // Flag for values that might not have been set
    static constexpr double kUndefinedValue = -99999;

    friend std::ostream& operator<< (std::ostream& output, const garana::GTruth &gtruth);

    bool IsFilled();



   ClassDef(GTruth,2) //
  }; //class GTruth
} // end garana namespace

#endif // GARANA_GTRUTH_H
