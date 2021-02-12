/*
 * TreeManager.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "TreeManager.h"
#include <iostream>

using namespace garana;

TreeManager::TreeManager() {}

TreeManager::TreeManager(std::string infilename) {

	fInFileName = infilename;
	Init();

}

void TreeManager::Init() {

    try {
        fInFile = new TFile(fInFileName.c_str(),"READ");
        if(!fInFile)
        	throw fInFileName;
    }
    catch(std::string& fname){
    	std::cerr << "TreeManager::Init: unable to find the file, "
    			  << fInFileName << '\n';
    }

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
    
    TTree* gen = nullptr;
    try{
    	gen = (TTree*)fInFile->FindObjectAny("genTree");
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
}//Init()

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
    	std::cerr << "TreeManager::GenTree: no StructGenTree or FlatGenTree found!" << std::endl;
    }

    return nullptr;

}//GetGenTree()


