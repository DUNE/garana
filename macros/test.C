
R__ADD_LIBRARY_PATH(/usr/local/lib)
R__LOAD_LIBRARY(libGaranaAccessors.so)
R__ADD_INCLUDE_PATH(/home/chilgenb/garana/include)


#include "TreeManager.h"
#include <TH1F.h>
#include <iostream>

using namespace garana;


void test(){

  std::cout << "loaded libraries" << std::endl;

  string infile = "/home/chilgenb/test_garana/structuredtree.root";

  TreeManager tm(infile);

  GenTree* gen = tm.GetGenTree();

  TH1F* h = new TH1F("h","my c++ macro histogram;E_{#nu} [GeV]",10,0,10);

  for(size_t i=0; i<gen->NEntries(); i++){
    gen->GetEntry(i);
    for(size_t j=0; j<gen->NGen(); j++){
        h->Fill(gen->NuP(j)->E());
    }
  }

  std::cout << "found genTree with " << gen->NEntries() << " entries" << std::endl;

 auto c = new TCanvas();
 h->Draw();
 c->SaveAs("testhist_cppmacro.png");

}
