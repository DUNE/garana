/*
 * FSParticle.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "garana/DataProducts/FSParticle.h"
#include <climits>

using namespace garana;

 FSParticle::FSParticle(const int& trackid, const int& pdg, const float& x, const float& y, const float& z, const float& t,
         const float& px, const float& py, const float& pz, const float& e):
	 fTrackId(trackid),
     fPdg(pdg),
     fR(TLorentzVector(x,y,z,t)),
     fP(TLorentzVector(px,py,pz,e))
     {}

 FSParticle::FSParticle(const int& trackid, const int& pdg, const TLorentzVector& r, const TLorentzVector& p):
	 fTrackId(trackid),
     fPdg(pdg),
     fR(r),
     fP(p)
     {}


 int   const& FSParticle::TrackId()       const { return fTrackId; }
 int   const& FSParticle::PDG()           const { return fPdg; }
 const TLorentzVector& FSParticle::Pos4() const { return fR; }
 const TLorentzVector& FSParticle::Mom4() const { return fP; }
 float                 FSParticle::X()    const { return fR.X();  }
 float                 FSParticle::Y()    const { return fR.Y();  }
 float                 FSParticle::Z()    const { return fR.Z();  }
 float                 FSParticle::T()    const { return fR.T();  }
 float                 FSParticle::Px()   const { return fP.Px();  }
 float                 FSParticle::Py()   const { return fP.Py();  }
 float                 FSParticle::Pz()   const { return fP.Pz();  }
 float                 FSParticle::P()    const { return fP.P();   }
 float                 FSParticle::E()    const { return fP.E();   }
 float                 FSParticle::KE()   const { return E()-sqrt(E()*E()-P()*P()); }


//ClassImp(FSParticle)
