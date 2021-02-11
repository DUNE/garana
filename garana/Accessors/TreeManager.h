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

 namespace{
     template<class T>
     struct item_return{ typedef T type; };
     
     template<class T>
     typename item_return<T>::type item();
 }

 class TreeManager {

  public :

    TreeManager();
    TreeManager(std::string infilename);

    GenTree* GetGenTree() const;


  private:

    void Init();
    //bool FindTree(std::string name) const;

    std::string   fInFileName = "";
    TFile*        fInFile = nullptr;

    bool fIsStructured = false;

    HeaderTree*        fHeaderTree = nullptr;
    StructuredGenTree* fStructGenTree = nullptr;
    FlatGenTree*       fFlatGenTree = nullptr;

 };//class
}//namespace

#endif /* TREEMANAGER_H_ */
