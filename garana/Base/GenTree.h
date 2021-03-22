#ifndef GARANA_GENTREE_H
#define GARANA_GENTREE_H

#include "garana/Base/TreeReader.h"

namespace garana{

 class GenTree : public TreeReader {

  public: // TODO: make everything protected?

   virtual ~GenTree() {};

   // generator agnostic
   virtual const UInt_t          NGen()                                            const = 0;
   virtual const UInt_t          NFSParticles(const UInt_t& igen )                 const = 0;
   virtual const Bool_t          IsGenie(const UInt_t& igen )                      const = 0;
   virtual const Float_t         FSTotEnergy(const UInt_t& igen)                   const = 0;
   virtual const Float_t         FSEnergy(const UInt_t& igen, const UInt_t& ifsp)  const = 0;
   virtual const Float_t         FSPDG(const UInt_t& igen, const UInt_t& ifsp)     const = 0;
   virtual const Int_t           FSTrackId(const UInt_t& igen, const UInt_t& ifsp) const = 0;

   ///< GENIE specific
   ///< neutrino info
   virtual const Int_t           NuPDG(const UInt_t& igen )      const = 0; ///< neutrino PDG code
   virtual const TLorentzVector* NuP(const UInt_t& igen)               = 0; ///< initial neutrino 4-momentum
   virtual const TLorentzVector* NuVertex(const UInt_t& igen)          = 0; ///< 4-position of neutrino vertex
   virtual const Bool_t          IsCC(const UInt_t& igen )       const = 0; ///< whether interaction is CC or not
   virtual const int             ScatterCode(const UInt_t& igen) const = 0; ///< GENIE neutrino scattering code
   virtual const int             InteractCode(const UInt_t& igen)const = 0; ///< GENIE interaction code

   ///< target info
   virtual const Int_t           TgtPDG(const UInt_t& igen )    const = 0; ///< PDG of Target Nucleus, nucleon only if free
   virtual const TLorentzVector* TgtP4(const UInt_t& igen)      const = 0; ///< target 4-momentum
   virtual const int             TgtZ(const UInt_t& igen )      const = 0; ///< target Z
   virtual const int             TgtA(const UInt_t& igen )      const = 0; ///< target A
   virtual const int             HitNucPDG(const UInt_t& igen ) const = 0; ///< hit nucleon PDG code
   virtual const TLorentzVector* HitNucP4(const UInt_t& igen )  const = 0; ///< hit nucleon (initial) 4-momentum

   ///< kinematics
   virtual const double          Q2(const UInt_t& igen )          const = 0;
   virtual const double          q2(const UInt_t& igen )          const = 0;
   virtual const double          W(const UInt_t& igen )           const = 0;
   virtual const double          T(const UInt_t& igen )           const = 0;
   virtual const double          X(const UInt_t& igen )           const = 0;
   virtual const double          Y(const UInt_t& igen )           const = 0;
   virtual const TLorentzVector* FSLeptonP4(const UInt_t& igen )  const = 0; ///< final state primary lepton 4-momentum (LAB frame)
   virtual const TLorentzVector* FSHadSystP4(const UInt_t& igen ) const = 0; ///< final state hadronic system 4-momentum(LAB frame)

   ///< particle multiplicities (before FSI)
   virtual const int             NumNuProton(const UInt_t& igen)  const = 0;   ///< number of protons after reaction, before FSI
   virtual const int             NumNuNeutron(const UInt_t& igen) const = 0;   ///< number of neutrons after reaction, before FSI
   virtual const int             NumNuPi0(const UInt_t& igen)     const = 0;   ///< number of pi0 after reaction, before FSI
   virtual const int             NumNuPiPlus(const UInt_t& igen)  const = 0;   ///< number of pi pluses after reaction, before FSI
   virtual const int             NumNuPiMinus(const UInt_t& igen) const = 0;   ///< number of pi minuses after reaction, before FSI

   const std::vector<Int_t>* GetGIndex() const; ///< whether or not subentry is GENIE interaction, index of GENIE interaction

  protected:

   const std::vector<Int_t>* fGIndex  = nullptr;
   TBranch*                  b_GIndex = nullptr;

 }; //class
} //namespace

#endif //GenTree
