/*
 * G4Particle.h
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_G4PARTICLE_H_
#define GARANA_G4PARTICLE_H_

#include <TLorentzVector.h>
#include <climits>
#include <TROOT.h>

namespace garana {

  class G4Particle : public TObject {

    public:
	  G4Particle() :
	  fRi(TLorentzVector()),
	  fRf(TLorentzVector()),
	  fPi(TLorentzVector()),
	  fPf(TLorentzVector())
      {}

      G4Particle(int pdg, int parentPdg, int progenitorPdg, int trackId, int parentTrackId,
                 int progenitorTrackId, int processI, int processF, TLorentzVector ri,
                 TLorentzVector rf, TLorentzVector pi, TLorentzVector pf):
                  fPdg(pdg),
                  fParentPdg(parentPdg),
                  fProgenitorPdg(progenitorPdg),
                  fTrackId(trackId),
                  fParentTrackId(parentTrackId),
                  fProgenitorTrackId(progenitorTrackId),
                  fProcessI(processI),
                  fProcessF(processF),
                  fRi(ri),
                  fRf(rf),
                  fPi(pi),
                  fPf(pf)
                  {}


      int   PDG()                  const { return fPdg; }
      int   ParentPDG()            const { return fParentPdg; }
      int   ProgenitorPDG()        const { return fProgenitorPdg; }
      int   TrackID()              const { return fTrackId; }
      int   ParentTrackID()        const { return fParentTrackId; }
      int   ProgenitorTrackID()    const { return fProgenitorTrackId; }
      TLorentzVector* PosI() { return &fRi; }
      TLorentzVector* PosF() { return &fRf; }
      TLorentzVector* MomI() { return &fPi; }
      TLorentzVector* MomF() { return &fPf; }
      float XI()   const { return fRi.X();  }  ///< return init position x-coordinate [cm]
      float YI()   const { return fRi.Y();  }  ///< return init position y-coordinate [cm]
      float ZI()   const { return fRi.Z();  }  ///< return init position z-coordinate [cm]
      float XF()   const { return fRf.X();  }  ///< return end  position x-coordinate [cm]
      float YF()   const { return fRf.Y();  }  ///< return end  position y-coordinate [cm]
      float ZF()   const { return fRf.Z();  }  ///< return end  position z-coordinate [cm]
      float PxI()  const { return fPi.Px(); }  ///< return init momentum x-component [GeV/c]
      float PyI()  const { return fPi.Py(); }  ///< return init momentum y-component [GeV/c]
      float PzI()  const { return fPi.Pz(); }  ///< return init momentum z-component [GeV/c]
      float PxF()  const { return fPf.Px(); }  ///< return end  momentum x-component [GeV/c]
      float PyF()  const { return fPf.Py(); }  ///< return end  momentum y-component [GeV/c]
      float PzF()  const { return fPf.Pz(); }  ///< return end  momentum z-component [GeV/c]
      float PI()   const { return fPi.P();  }  ///< return magnitude of init particle momentum [GeV/c]
      float PF()   const { return fPf.P();  }  ///< return magnitude of end  particle momentum [GeV/c]
      float EI()   const { return fPi.E();  }  ///< return total init energy [GeV]
      float EF()   const { return fPf.E();  }  ///< return total end  energy [GeV]
      float KEI()  const { return EI()-sqrt(EI()*EI()-PI()*PI()); } ///< return init particle KE [GeV]
      float KEF()  const { return EF()-sqrt(EF()*EF()-PF()*PF()); } ///< return end particle KE [GeV]

    private:

      int fPdg               = INT_MAX;  ///< particle PDG code
      int fParentPdg         = INT_MAX;  ///< particle parent's PDG code
      int fProgenitorPdg     = INT_MAX;  ///< FS particle from gen stage that led to this one
      int fTrackId           = INT_MAX;  ///< particle trackID
      int fParentTrackId     = INT_MAX;  ///< particle's parent's trackID
      int fProgenitorTrackId = INT_MAX;  ///< FS particle from gen stage that led to this one
      int fProcessI          = INT_MAX;  ///< process that produced the particle
      int fProcessF          = INT_MAX;  ///< process that killed the particle
      TLorentzVector fRi;                ///< initial particle 4-position in lab frame [cm,ns]
      TLorentzVector fRf;                ///< final particle 4-position in lab frame [cm,ns]
      TLorentzVector fPi;                ///< initial particle 4-momentum in lab frame [GeV/c,GeV]
      TLorentzVector fPf;                ///< final particle 4-momentum in lab frame [GeV/c,GeV]


      ClassDef(G4Particle,2)

  };//class
}//namepsace
#endif /* GARANA_G4PARTICLE_H_ */
