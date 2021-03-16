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
    TreeManager(const string& infilename);//, bool onGen, bool onG4, bool onDet, bool onReco, bool onDis);

    HeaderTree*  GetHeaderTree()  const;
    GenTree*     GetGenTree()     const;
    G4Tree*      GetG4Tree()      const;
    DetTree*     GetDetTree()     const;
    RecoTree*    GetRecoTree()    const;
    DisplayTree* GetDisplayTree() const;
    void         GetEntry(UInt_t ientry);

    void         SetActiveGenTree(bool active=true) {fOnGen = active; }
    void         SetActiveG4Tree (bool active=true) {fOnG4  = active; }
    void         SetActiveDetTree(bool active=true) {fOnDet = active; }
    void         SetActiveRecTree(bool active=true) {fOnRec = active; }
    void         SetActiveDisTree(bool active=true) {fOnDis = active; }

    bool         IsActiveGenTree() const {return fOnGen; }
    bool         IsActiveG4Tree () const {return fOnG4 ; }
    bool         IsActiveDetTree() const {return fOnDet; }
    bool         IsActiveRecTree() const {return fOnRec; }
    bool         IsActiveDisTree() const {return fOnDis; }

    // tree names
    const string genName  = "genTree";   //GenTree::treename;
    const string g4Name   = "g4Tree" ;   //G4Tree::treename;
    const string detName  = "detTree";
    const string recoName = "recoTree";
    const string displayName = "displayTree";

  private:

    void Init();

    string   fInFileName = "";
    TFile*   fInFile     = nullptr;

    bool     fOnGen      = true;
    bool     fOnG4       = true;
    bool     fOnDet      = false;
    bool     fOnRec      = true;
    bool     fOnDis      = false;

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
