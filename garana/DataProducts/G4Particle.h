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
#include <vector>
#include <utility>
#include <string>

using std::vector;
using std::pair;
using std::string;

namespace garana {

  class G4Particle {

    public:
	  G4Particle() {}

	  #ifndef __GCCXML__

      G4Particle(const int& npts, const int& pdg, const int& parentPdg, const int& progenitorPdg, const int& trackId,
    		     const int& parentTrackId, const int& progenitorTrackId, const int& processI,
    		     const int& processF, const vector<pair<TLorentzVector,TLorentzVector>>& positions,
    		     const vector<pair<TLorentzVector,TLorentzVector>>& momenta, const vector<int>& regions, const vector<size_t>& nptsPerRegion ):
                  fNpts(npts),
                  fPdg(pdg),
                  fParentPdg(parentPdg),
                  fProgenitorPdg(progenitorPdg),
                  fTrackId(trackId),
                  fParentTrackId(parentTrackId),
                  fProgenitorTrackId(progenitorTrackId),
                  fProcessI(processI),
                  fProcessF(processF),
                  fR(positions),
                  fP(momenta),
                  fRegions(regions),
                  fNptsPerRegion(nptsPerRegion)
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
      const TLorentzVector* PositionEnter(const size_t& iregion)    const { return &fR.at(iregion).first ; }
      const TLorentzVector* PositionExit(const size_t& iregion)     const { return &fR.at(iregion).second ; }
      const TLorentzVector* MomentumEnter(const size_t& iregion)    const { return &fP.at(iregion).first ; }
      const TLorentzVector* MomentumExit(const size_t& iregion)     const { return &fP.at(iregion).second ; }
      int                   Region(const size_t& iregion)           const { return fRegions.at(iregion); }
      size_t                NPointsPerRegion(const size_t& iregion) const { return fNptsPerRegion.at(iregion); }
      size_t                NRegions()                              const { return fRegions.size(); }

	  #endif

    private:

      int                                         fNpts              = INT_MAX;  ///< number of G4 steps (i.e. trajectory points)
      int                                         fPdg               = INT_MAX;  ///< particle PDG code
      int                                         fParentPdg         = INT_MAX;  ///< particle parent's PDG code
      int                                         fProgenitorPdg     = INT_MAX;  ///< FS particle from gen stage that led to this one
      int                                         fTrackId           = INT_MAX;  ///< particle trackID
      int                                         fParentTrackId     = INT_MAX;  ///< particle's parent's trackID
      int                                         fProgenitorTrackId = INT_MAX;  ///< FS particle from gen stage that led to this one
      int                                         fProcessI          = INT_MAX;  ///< process that produced the particle
      int                                         fProcessF          = INT_MAX;  ///< process that killed the particle
      vector<pair<TLorentzVector,TLorentzVector>> fR;                            ///< particle 4-position at entry (first) and exit (second) points for selected geometric regions
      vector<pair<TLorentzVector,TLorentzVector>> fP;                            ///< particle 4-momentum at entry (first) and exit (second) points for selected geometric regions
      vector<int>                                 fRegions;                      ///< region numbers (e.g. tpc inactive (2), tpc active (1), tpcFiducial(0), eCal (3))
      vector<size_t>                              fNptsPerRegion;                ///< number of trajectory points (G4 steps) per region of interest

  };//class
}//namepsace
#endif /* GARANA_G4PARTICLE_H_ */
