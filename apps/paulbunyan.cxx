#include <TFile.h>
#include <TTree.h>

#include <iostream>
#include <string>

#include "garana/Processors/MillGenTree.h"
#include "garana/Processors/MillHeaderTree.h"
//#include "include/garana/DataProducts/FSParticle.h"
//#include "include/garana/DataProducts/GTruth.h"

using namespace garana;

using std::cout;
using std::cerr;
using std::endl;
using std::string;

class FSParticle;
class GTruth;
class TTree;
class TFile;
class TBranch;
class TLeaf;

std::string GetOutfileName(const char* inName);

int main(int argc, char *argv[]) {

    //// check we got what we need from the command line ////
    if(argc==1) {
        cerr << "ERROR(paulbunyan): you must specify a root file to analyze ->" << '\n'
             << "  usage: paulbunyan <my_structured_tree.root>" << endl;
        return 1;
    }

    if(argc>2) {
        cerr << "ERROR(paulbunyan): too many arguments! using file name, "
             << argv[1] << endl;
    }

    // setup files
    TFile* inFile  = new TFile(argv[1],"READ"); //input file
    try{
        if(!inFile || !inFile->IsOpen())
            throw(inFile);
    } 
    catch(TFile* inFile){
        cerr << "ERROR(paulbunyan): could not open file , '" << string(argv[1]) << "'" << endl;
        return 2;
    }

    // get trees produced by garsoft/Ana/StructuredTree_module.cc and flatten them
    // headerTree
    TTree* header = (TTree*)inFile->Get("structuredtree/headerTree"); //required;
    try{
        if(!header)
            throw header;
        std::cout << "INFO(paulbunyan): found (required) input headerTree" << std::endl;
    }
    catch(TTree* ptr){
        cerr << "ERROR(paulbunyan): paulbunyan is not happy with your file. he does not want to chop your trees!" << '\n'
             << "   required 'headerTree' not found. fix your file and try again." << endl;
        return 1;
    }

    // following input (structured) trees may or may not be present
    TTree* gen     = (TTree*)inFile->Get("structuredtree/genTree");
    TTree* g4      = (TTree*)inFile->Get("structuredtree/g4Tree");
    TTree* det     = (TTree*)inFile->Get("structuredtree/detTree");
    TTree* reco    = (TTree*)inFile->Get("structuredtree/recoTree");
    TTree* display = (TTree*)inFile->Get("structuredtree/displayTree");

    //now write our flat trees to the output file
    std::string outname = GetOutfileName(argv[1]);
    TFile* outFile = new TFile(outname.c_str(),"RECREATE"); //output file with chopped trees

    TTree* header_out = new TTree("headerTree", "sample provenance information");
    outFile->cd();
    header_out->SetDirectory(outFile);

    MillHeaderTree hmill(header,header_out);

    //// done with prerequisites. on to the optional trees.
    // output (flat) trees
    TTree* gen_out     = new TTree("genTree", "generator level info"); //does this overwrite gen above?
    //TTree* g4_out      = nullptr;
    //TTree* det_out     = nullptr;
    //TTree* reco_out    = nullptr;
    //TTree* display_out = nullptr;

    //chop genTree
    if(gen){
    	std::cout << "INFO(paulbunyan): found input genTree" << std::endl;

    	//gen_out = new TTree("genTree", "generator level info"); //does this overwrite gen above?
    	outFile->cd();
    	gen_out->SetDirectory(outFile);

    	MillGenTree mill(gen,gen_out);
    }//gen*/

    if(g4){
    	std::cout << "INFO(paulbunyan): found input g4Tree" << std::endl;
    }
    if(det){
    	std::cout << "INFO(paulbunyan): found input detTree" << std::endl;
    }
    if(reco){
    	std::cout << "INFO(paulbunyan): found input recoTree" << std::endl;
    }

    if(display) {
    	std::cout << "INFO(paulbunyan): found input displayTree" << std::endl;
    }

    //close input/output files and free memory from TTrees
    inFile->Close();
    outFile->Close();

    //free memory from TFiles
    delete inFile;
    delete outFile;

    return 0;

}//main()

// helper functions  //
std::string GetOutfileName(const char* inName){

    string path(inName);
    std::cout << "parsing file '" << path << "'" << std::endl;
    string base = path;
    while(base.find("/")!=string::npos){
        base = base.substr(base.find("/")+1,base.size());
    }

    base = base.substr(0,base.find("."));
    path = path.substr(0,path.find(base));
    string outstr = path+base+"_chopped.root";
    std::cout << "generated output file path '" << outstr << "'" << std::endl;

    return outstr;
}//GetOutfileName
