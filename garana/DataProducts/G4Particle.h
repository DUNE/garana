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

namespace garana {

  class G4Particle {

    public:
	  G4Particle() {}
      G4Particle(const int& npts, const int& pdg, const int& parentPdg, const int& progenitorPdg, const int& trackId,
    		     const int& parentTrackId, const int& progenitorTrackId, const int& processI,
    		     const int& processF, const TLorentzVector& ri,
                 const TLorentzVector& rf, const TLorentzVector& pi, const TLorentzVector& pf):
                  fNpts(npts),
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
      //default dest'or

      int const&            NPoints()           const { return fNpts;              }
      int const&            PDG()               const { return fPdg;               }
      int const&            ParentPDG()         const { return fParentPdg;         }
      int const&            ProgenitorPDG()     const { return fProgenitorPdg;     }
      int const&            TrackID()           const { return fTrackId;           }
      int const&            ParentTrackID()     const { return fParentTrackId;     }
      int const&            ProgenitorTrackID() const { return fProgenitorTrackId; }
      int const&            ProcessI()          const { return fProcessI;          }
      int const&            ProcessF()          const { return fProcessF;          }
      const TLorentzVector* PosI()              const { return &fRi;               }
      const TLorentzVector* PosF()              const { return &fRf;               }
      const TLorentzVector* MomI()              const { return &fPi;               }
      const TLorentzVector* MomF()              const { return &fPf;               }
      const float           XI()                const { return fRi.X();            }  ///< return init position x-coordinate [cm]
      const float           YI()                const { return fRi.Y();            }  ///< return init position y-coordinate [cm]
      const float           ZI()                const { return fRi.Z();            }  ///< return init position z-coordinate [cm]
      const float           XF()                const { return fRf.X();            }  ///< return end  position x-coordinate [cm]
      const float           YF()                const { return fRf.Y();            }  ///< return end  position y-coordinate [cm]
      const float           ZF()                const { return fRf.Z();            }  ///< return end  position z-coordinate [cm]
      const float           PxI()               const { return fPi.Px();           }  ///< return init momentum x-component [GeV/c]
      const float           PyI()               const { return fPi.Py();           }  ///< return init momentum y-component [GeV/c]
      const float           PzI()               const { return fPi.Pz();           }  ///< return init momentum z-component [GeV/c]
      const float           PxF()               const { return fPf.Px();           }  ///< return end  momentum x-component [GeV/c]
      const float           PyF()               const { return fPf.Py();           }  ///< return end  momentum y-component [GeV/c]
      const float           PzF()               const { return fPf.Pz();           }  ///< return end  momentum z-component [GeV/c]
      const float           PI()                const { return fPi.P();            }  ///< return magnitude of init particle momentum [GeV/c]
      const float           PF()                const { return fPf.P();            }  ///< return magnitude of end  particle momentum [GeV/c]
      const float           EI()                const { return fPi.E();            }  ///< return total init energy [GeV]
      const float           EF()                const { return fPf.E();            }  ///< return total end  energy [GeV]
      const float           KEI()               const { return EI()-sqrt(EI()*EI()-PI()*PI()); } ///< return init particle KE [GeV]
      const float           KEF()               const { return EF()-sqrt(EF()*EF()-PF()*PF()); } ///< return end particle KE [GeV]

    private:

      int            fNpts              = INT_MAX;  ///< number of G4 steps (i.e. trajectory points)
      int            fPdg               = INT_MAX;  ///< particle PDG code
      int            fParentPdg         = INT_MAX;  ///< particle parent's PDG code
      int            fProgenitorPdg     = INT_MAX;  ///< FS particle from gen stage that led to this one
      int            fTrackId           = INT_MAX;  ///< particle trackID
      int            fParentTrackId     = INT_MAX;  ///< particle's parent's trackID
      int            fProgenitorTrackId = INT_MAX;  ///< FS particle from gen stage that led to this one
      int            fProcessI          = INT_MAX;  ///< process that produced the particle
      int            fProcessF          = INT_MAX;  ///< process that killed the particle
      TLorentzVector fRi;                           ///< initial particle 4-position in lab frame [cm,ns]
      TLorentzVector fRf;                           ///< final particle 4-position in lab frame [cm,ns]
      TLorentzVector fPi;                           ///< initial particle 4-momentum in lab frame [GeV/c,GeV]
      TLorentzVector fPf;                           ///< final particle 4-momentum in lab frame [GeV/c,GeV]

  };//class
}//namepsace
#endif /* GARANA_G4PARTICLE_H_ */
