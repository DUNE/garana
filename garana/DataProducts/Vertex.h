/*
 * Vertex.h
 *
 *  Created on: Feb 23, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_VERTEX_H_
#define GARANA_VERTEX_H_

#include <TLorentzVector.h>
//#include <TROOT.h>
#include <climits>

namespace garana {

  class Vertex { //: public TObject {

    public:

	  Vertex();
	  Vertex(const TLorentzVector& position, const float** covar);

	  TLorentzVector* GetVertex();
	  float**         GetCovar();

    protected:

	  TLorentzVector fPosition;    ///< 4-position of vertex [cm,ns]
	  float        fCovar[3][3]; ///< vertex 3-position fit uncertainties [cm]
	  //TODO extend covar matrix to time?

	//ClassDef(Vertex,2)

  }; //class
}//namespace

#endif /* GARANA_VERTEX_H_ */
