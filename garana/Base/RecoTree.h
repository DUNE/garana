/*
 * G4Tree.h
 *
 *  Created on: Feb 18, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_RECOTREE_H_
#define GARANA_RECOTREE_H_

#include "garana/Base/TreeReader.h"
#include "garana/DataProducts/Track.h"
#include "garana/DataProducts/Vertex.h"
#include "garana/DataProducts/Vee.h"
#include "garana/DataProducts/CaloCluster.h"


namespace garana {

  class RecoTree : public TreeReader {

    public:

	  virtual ~RecoTree() {};

	  //inline static std::string const treename = "recoTree";

	  // pure virtual methods
	  // sizes
	  virtual size_t NTrack()      const = 0;
	  virtual size_t NVertex()     const = 0;
	  virtual size_t NVee()        const = 0;
	  virtual size_t NCalCluster() const = 0;

	  // track
      virtual TLorentzVector TrackVertex(size_t itrack) const = 0;
      virtual TLorentzVector TrackEnd(size_t itrack)    const = 0;
      virtual size_t         NTrackHit(size_t itrack)   const = 0;
      virtual TVector3       TrackMomBeg(size_t itrack) const = 0;
      virtual TVector3       TrackMomEnd(size_t itrack) const = 0;

	  //vertex
      virtual TLorentzVector GetVertex(size_t ivertex) const = 0;
      virtual void           VertexCovariance(size_t ivertex, float covar[][3]) const = 0;

      //vee

      //calo cluster

  };//class
}//namespace

#endif /* GARANA_RECOTREE_H_ */
