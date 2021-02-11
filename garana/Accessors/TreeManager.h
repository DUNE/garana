/*
 * TreeManager.h
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_TREEMANAGER_H_
#define GARANA TREEMANAGER_H_

//garana includes
#include "HeaderTree.h"
#include "StructuredGenTree.h"
#include "FlatGenTree.h"

//ROOT includes
#include "TTree.h"
#include "TFile.h"

//c++ includes
#include <string>
#include <iostream>

namespace garana {

 class TreeManager {

  public :
	TreeManager();
    TreeManager(std::string infilename);

    template<class gentype>
    gentype* GetGenTree();

  private:

    void Init();
    //bool FindTree(std::string name) const;

    std::string   fInFileName = "";
    TFile*        fInFile = nullptr;

    HeaderTree*        fHeaderTree = nullptr;
    StructuredGenTree* fStructGenTree = nullptr;
    FlatGenTree*       fFlatGenTree = nullptr;

 };//class
}//namespace

#endif /* TREEMANAGER_H_ */
