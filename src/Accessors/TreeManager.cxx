/*
 * TreeManager.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/TreeManager.h"
#include <iostream>

using namespace garana;
using std::cerr;
using std::endl;

TreeManager::TreeManager(std::string infilename) {

	fInFileName = infilename;
	Init();

}

void TreeManager::Init() {

	//open file for reading
    try {
        fInFile = new TFile(fInFileName.c_str(),"READ");
        if(!fInFile)
        	throw fInFileName;
    }
    catch(std::string& fname){
    	std::cerr << "TreeManager::Init: unable to find the file, "
    			  << fInFileName << '\n';
    }

    // headerTree
    TTree* header = (TTree*)fInFile->FindObjectAny("headerTree");
    try {
	    if(!header)
		    throw header;
    }
    catch(TTree* t){
    	std::cerr << "TreeManager::Init: "
    			  << "No HeaderTree found in input file, " << fInFile
    	          << '\n';
    }

    fHeaderTree = new HeaderTree(header);
    std::string treeType = *(fHeaderTree->TreeType());
    
    /// genTree
    TTree* gen = nullptr;
    try{
    	gen = (TTree*)fInFile->FindObjectAny(genName.c_str());
    	if(!gen)
    		throw gen;
    }
    catch(TTree* t){
    std::cerr << "TreeManager::Init: "
    		  << "No GenTree found in input file, " << fInFile
    		  << '\n';
    }

    if(treeType == "structured"){ //structured tree
        fStructGenTree = new StructuredGenTree(gen);
    }
    else { //flat tree
        fFlatGenTree = new FlatGenTree(gen);
    }

    /// g4Tree ///
     TTree* g4 = nullptr;
     try{
     	g4 = (TTree*)fInFile->FindObjectAny(g4Name.c_str());
     	if(!g4)
     		throw g4;
     }
     catch(TTree* t){
     std::cerr << "TreeManager::Init: "
     		  << "No G4Tree found in input file, " << fInFile
     		  << '\n';
     }

     if(treeType == "structured"){ //structured tree
         fStructG4Tree = new StructuredG4Tree(g4);
     }
     else { //flat tree
         fFlatG4Tree = new FlatG4Tree(g4);
     }

     /// recoTree ///
     TTree* reco = nullptr;
     try{
     	reco = (TTree*)fInFile->FindObjectAny(recoName.c_str());
     	if(!reco)
     		throw reco;
     }
     catch(TTree* t){
     std::cerr << "TreeManager::Init: "
     		  << "No RecoTree found in input file, " << fInFile
     		  << '\n';
     }

     if(treeType == "structured"){ //structured tree
         fStructRecoTree = new StructuredRecoTree(reco);
     }
     else { //flat tree
         fFlatRecoTree = new FlatRecoTree(reco);
     }

}// Init()

HeaderTree* TreeManager::GetHeaderTree() const{

	return fHeaderTree;

}

GenTree* TreeManager::GetGenTree() const{

    try{
    	if(!fStructGenTree && !fFlatGenTree)
    		throw fStructGenTree;
    	if(!fStructGenTree){
                return fFlatGenTree;
        }
    	else{
                return fStructGenTree;
        }
    }
    catch(StructuredGenTree* e){
    	std::cerr << "TreeManager::GenTree: no structured genTree or flat genTree found!" << std::endl;
    }

    return nullptr;

}//GetGenTree()

G4Tree* TreeManager::GetG4Tree() const{

    try{
    	if(!fStructG4Tree && !fFlatG4Tree)
    		throw fStructG4Tree;
    	if(!fStructG4Tree){
                return fFlatG4Tree;
        }
    	else{
                return fStructG4Tree;
        }
    }
    catch(StructuredGenTree* e){
    	std::cerr << "TreeManager::G4Tree: no structured g4Tree or flat g4Tree found!" << std::endl;
    }

    return nullptr;

}//GetGenTree()

DetTree* TreeManager::GetDetTree() const{

    try{
    	if(!fStructDetTree && !fFlatDetTree)
    		throw fStructDetTree;
    	if(!fStructDetTree){
                return fFlatDetTree;
        }
    	else{
                return fStructDetTree;
        }
    }
    catch(StructuredDetTree* e){
    	std::cerr << "TreeManager::DetTree: no structured detTree or flat detTree found!" << std::endl;
    }

    return nullptr;

}//GetGenTree()

RecoTree* TreeManager::GetRecoTree() const{

    try{
    	if(!fStructRecoTree && !fFlatRecoTree)
    		throw fStructRecoTree;
    	if(!fStructRecoTree){
                return fFlatRecoTree;
        }
    	else{
                return fStructRecoTree;
        }
    }
    catch(StructuredRecoTree* e){
    	cerr << "TreeManager::RecoTree: no structured recoTree or flat recoTree found!" << endl;
    }

    return nullptr;

}//GetGenTree()

DisplayTree* TreeManager::GetDisplayTree() const{

    try{
    	if(!fStructDisplayTree && !fFlatDisplayTree)
    		throw fStructDisplayTree;
    	if(!fStructDisplayTree){
                return fFlatDisplayTree;
        }
    	else{
                return fStructDisplayTree;
        }
    }
    catch(StructuredDisplayTree* e){
    	cerr << "TreeManager::DisplayTree: no structured displayTree or flat displayTree found!" << endl;
    }

    return nullptr;

}//GetGenTree()
