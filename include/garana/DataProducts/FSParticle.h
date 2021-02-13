#ifndef GARANA_DATAPRODUCTS_FSPARTICLE_H
#define GARANA_DATAPRODUCTS_FSPARTICLE_H

#include <TLorentzVector.h>
#include <TROOT.h>

namespace garana {
 class FSParticle : public TObject {

  public:

    //constructors
    FSParticle();
    FSParticle(int pdg, float x, float y, float z, float t,
                  float px, float py, float pz, float e);
    FSParticle(int pdg, TLorentzVector r, TLorentzVector p);


    int   PDG()                  const;
    const TLorentzVector& Pos4() const;
    const TLorentzVector& Mom4() const;
    float X()                    const;    ///< return position x-component [GeV/c]
    float Y()                    const;    ///< return position y-component [GeV/c]
    float Z()                    const;    ///< return position z-component [GeV/c]
    float Px()                   const;    ///< return momentum x-component [GeV/c]
    float Py()                   const;    ///< return momentum y-component [GeV/c]
    float Pz()                   const;    ///< return momentum z-component [GeV/c]
    float P()                    const;    ///< return magnitude of particle momentum
    float E()                    const;    ///< return total energy [GeV]
    float KE()                   const;

  protected:

    //member data
    int            fPdg;  ///< particle PDG code
    TLorentzVector fR;    ///< final particle 4-position in lab frame [cm,ns]
    TLorentzVector fP;    ///< final particle 4-momentum in lab frame [GeV/c,GeV]


  ClassDef(FSParticle,2)

 };//class
}//namespace

#endif //GARANA_DATAPRODUCTS_FSPARTICLE_H
