/*
 * TreeManager.h
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#ifndef GARANA_TREEMANAGER_H_
#define GARANA TREEMANAGER_H_

//garana includes
#include "garana/Accessors/HeaderTree.h"

#include "garana/Accessors/StructuredGenTree.h"
#include "garana/Accessors/StructuredG4Tree.h"
#include "garana/Accessors/StructuredDetTree.h"
#include "garana/Accessors/StructuredRecoTree.h"
#include "garana/Accessors/StructuredDisplayTree.h"

#include "garana/Accessors/FlatGenTree.h"
#include "garana/Accessors/FlatG4Tree.h"
#include "garana/Accessors/FlatDetTree.h"
#include "garana/Accessors/FlatRecoTree.h"
#include "garana/Accessors/FlatDisplayTree.h"

using std::string;

namespace garana {

 /*const string GenTree::treename      = "genTree";
 const string G4Tree::treename       = "g4Tree";
 const string DetTree::treename      = "detTree";
 const string RecoTree::treename     = "recoTree";
 const string DisplayTree::treename  = "displayTree";*/



 class TreeManager {

  public :

    TreeManager(){}
    TreeManager(string infilename);

    HeaderTree*  GetHeaderTree()  const;
    GenTree*     GetGenTree()     const;
    G4Tree*      GetG4Tree()      const;
    DetTree*     GetDetTree()     const;
    RecoTree*    GetRecoTree()    const;
    DisplayTree* GetDisplayTree() const;

    const string genName = "genTree";   //GenTree::treename;
    const string g4Name  = "g4Tree" ;   //G4Tree::treename;

  private:

    void Init();

    string   fInFileName = "";
    TFile*   fInFile     = nullptr;

    HeaderTree*            fHeaderTree        = nullptr;

    StructuredGenTree*     fStructGenTree     = nullptr;
    StructuredG4Tree*      fStructG4Tree      = nullptr;
    StructuredDetTree*     fStructDetTree     = nullptr;
    StructuredRecoTree*    fStructRecoTree    = nullptr;
    StructuredDisplayTree* fStructDisplayTree = nullptr;

    FlatGenTree*           fFlatGenTree       = nullptr;
    FlatG4Tree*            fFlatG4Tree        = nullptr;
    FlatDetTree*           fFlatDetTree       = nullptr;
    FlatRecoTree*          fFlatRecoTree      = nullptr;
    FlatDisplayTree*       fFlatDisplayTree   = nullptr;

 };//class
}//namespace

#endif /* TREEMANAGER_H_ */
