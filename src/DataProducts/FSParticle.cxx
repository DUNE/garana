/*
 * FSParticle.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "garana/DataProducts/FSParticle.h"
#include <climits>

using namespace garana;

 FSParticle::FSParticle() :
    fPdg(INT_MAX),
    fR(TLorentzVector()),
    fP(TLorentzVector()){}

 FSParticle::FSParticle(int pdg, float x, float y, float z, float t, float px, float py, float pz, float e):
     fPdg(pdg),
     fR(TLorentzVector(x,y,z,t)),
     fP(TLorentzVector(px,py,pz,e))
     {}

 FSParticle::FSParticle(int pdg, TLorentzVector r, TLorentzVector p):
     fPdg(pdg),
     fR(r),
     fP(p)
     {}


 int   FSParticle::PDG()                  const { return fPdg; }
 const TLorentzVector& FSParticle::Pos4() const { return fR; }
 const TLorentzVector& FSParticle::Mom4() const { return fP; }
 float FSParticle::X()                    const { return fR.X();  }
 float FSParticle::Y()                    const { return fR.Y();  }
 float FSParticle::Z()                    const { return fR.Z();  }
 float FSParticle::T()                    const { return fR.T();  }
 float FSParticle::Px()                   const { return fP.Px();  }
 float FSParticle::Py()                   const { return fP.Py();  }
 float FSParticle::Pz()                   const { return fP.Pz();  }
 float FSParticle::P()                    const { return fP.P();   }
 float FSParticle::E()                    const { return fP.E();   }
 float FSParticle::KE()                   const { return E()-sqrt(E()*E()-P()*P()); }


//ClassImp(FSParticle)
