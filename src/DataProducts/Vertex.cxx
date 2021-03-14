/*
 * Vertex.cxx
 *
 *  Created on: Feb 23, 2021
 *      Author: chilgenb
 */

#include "garana/DataProducts/Vertex.h"

using namespace garana;

Vertex::Vertex() {

	  fPosition.SetXYZT(FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX);
	  for(size_t i=0; i<3; i++){
		  //fCovar = new float*[3];
		  for(size_t j=0; j<3; j++){
			  //fCovar[i] = new float[3];
			  fCovar[i][j] = FLT_MAX;
		  }
	  }
} //

Vertex::Vertex(const TLorentzVector& position, const float* covar) {

	  fPosition = position;
	  for(size_t i=0; i<3; i++){
		  //fCovar = new float*[3];
		  for(size_t j=0; j<3; j++){
			  //fCovar[i] = new float[3];
			  fCovar[i][j] = covar[i]; //TODO check input array dimensions
		  }
	  }
} //

TLorentzVector* Vertex::GetVertex() {
	return &fPosition;
}

void Vertex::GetCovar(float covar[][3])  {
	for(size_t i=0; i<3; i++){
		for(size_t j=0; j<3; j++){
            covar[i][j] = fCovar[i][j];
		}
	}
}

//ClassImp(Vertex)
