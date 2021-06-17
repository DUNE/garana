#ifndef GARANA_DATAPRODUCTS_FSPARTICLE_H
#define GARANA_DATAPRODUCTS_FSPARTICLE_H

#include <TLorentzVector.h>
#include <TObject.h>
#include <climits>
//#include <TROOT.h>

namespace garana {
 class FSParticle : public TObject {

  public:

    //constructors
    FSParticle() {}

	#ifndef __GCCXML__
    FSParticle(const int& trackid, const int& pdg, const float& x, const float& y, const float& z, const float& t,
                  const float& px, const float& py, const float& pz, const float& e);
    FSParticle(const int& trackid, const int& pdg, const TLorentzVector& r, const TLorentzVector& p);


    int   const&          TrackId() const;
    int   const&          PDG()     const;
    const TLorentzVector& Pos4()    const;
    const TLorentzVector& Mom4()    const;
    float                 X()       const;    ///< return position x-component [GeV/c]
    float                 Y()       const;    ///< return position y-component [GeV/c]
    float                 Z()       const;    ///< return position z-component [GeV/c]
    float                 T()       const;    ///< return time [ns]
    float                 Px()      const;    ///< return momentum x-component [GeV/c]
    float                 Py()      const;    ///< return momentum y-component [GeV/c]
    float                 Pz()      const;    ///< return momentum z-component [GeV/c]
    float                 P()       const;    ///< return magnitude of particle momentum [GeV/c]
    float                 E()       const;    ///< return total energy [GeV]
    float                 KE()      const;

	#endif

  protected:

    //member data
    int            fTrackId = INT_MAX; ///< generator track ID
    int            fPdg     = INT_MAX;  ///< particle PDG code
    TLorentzVector fR;    ///< final particle 4-position in lab frame [cm,ns]
    TLorentzVector fP;    ///< final particle 4-momentum in lab frame [GeV/c,GeV]


  ClassDef(FSParticle,11)

 };//class
}//namespace

#endif //GARANA_DATAPRODUCTS_FSPARTICLE_H
