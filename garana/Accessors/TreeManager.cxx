/*
 * TreeManager.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/TreeManager.h"
#include <iostream>

using namespace garana;
using namespace std;

TreeManager::TreeManager(const string& infilename) : //, bool onGen=1, bool onG4=1, bool onDet=0, bool onReco=1, bool onDis=0) :
	fInFileName(infilename),
	fOnGen(true),
	fOnG4(true),
	fOnDet(false),
	fOnRec(true),
	fOnDis(false)
	{

	//fInFileName = infilename;
	Init();
	CheckEntries();

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

    cout << "found header Tree" << endl;

    fHeaderTree = new HeaderTree(header);
    fTreeType = *(fHeaderTree->TreeType());
    
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

    if(fTreeType == "structured"){ //structured tree
        fStructGenTree = new StructuredGenTree(gen);
    }
    else { //flat tree
        fFlatGenTree = new FlatGenTree(gen);
    }

    cout << "found genTree" << endl;

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

     if(fTreeType == "structured"){ //structured tree
         fStructG4Tree = new StructuredG4Tree(g4);
     }
     else { //flat tree
         fFlatG4Tree = new FlatG4Tree(g4);
     }
     cout << "found g4Tree" << endl;

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

     if(fTreeType == "structured"){ //structured tree
         fStructRecoTree = new StructuredRecoTree(reco);
     }
     else { //flat tree
         fFlatRecoTree = new FlatRecoTree(reco);
     }

     cout << "found recoTree" << endl;

     cout << "at end of Init()" << endl;

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


void TreeManager::GetEntry(const UInt_t& ientry){

	if(fOnGen) {
		if(fStructGenTree)    fStructGenTree->GetEntry(ientry);
		else if(fFlatGenTree) fFlatGenTree->GetEntry(ientry);
	}
	if(fOnG4) {
		if(fStructG4Tree)    fStructG4Tree->GetEntry(ientry);
		else if(fFlatG4Tree) fFlatG4Tree->GetEntry(ientry);
	}
	if(fOnDet) {
		if(fStructDetTree)    fStructDetTree->GetEntry(ientry);
		else if(fFlatDetTree) fFlatDetTree->GetEntry(ientry);
	}
	if(fOnRec) {
		if(fStructRecoTree)    fStructRecoTree->GetEntry(ientry);
		else if(fFlatRecoTree) fFlatRecoTree->GetEntry(ientry);
	}

	// probably don't want to include display tree
}

bool TreeManager::CheckEntries() {

	vector<UInt_t> ns;
	if(fOnGen) {
		if(fStructGenTree)    ns.push_back(fStructGenTree->NEntries());
		else if(fFlatGenTree) ns.push_back(fFlatGenTree->NEntries());
	}
	if(fOnG4) {
		if(fStructG4Tree)    ns.push_back(fStructG4Tree->NEntries());
		else if(fFlatG4Tree) ns.push_back(fFlatG4Tree->NEntries());
	}
	if(fOnDet) {
		if(fStructDetTree)    ns.push_back(fStructDetTree->NEntries());
		else if(fFlatDetTree) ns.push_back(fFlatDetTree->NEntries());
	}
	if(fOnRec) {
		if(fStructRecoTree)    ns.push_back(fStructRecoTree->NEntries());
		else if(fFlatRecoTree) ns.push_back(fFlatRecoTree->NEntries());
	}

	try {
		for(size_t i=1; i<ns.size(); i++){
			if(ns[0]!=ns[i])
				throw ns[0];
		}
	}
	catch(Int_t n){
		cerr << "number of entries differs between trees!" << endl;
		return false;
	}

	fNEntries = ns[0];
	return true;
}
