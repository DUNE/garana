
//garana includes
#include "TreeManager.h"

//ROOT includes
#include <TH1F.h>
#include <TCanvas.h>

//c++ includes
#include <iostream>

using namespace garana;

int main(int argc, char *argv[]){


    std::cout << "welcome to garana!" << std::endl;
    if(argc==1) {
        std::cout << "you must specify a root file to analyze" << std::endl;
        return 1;
    }

    if(argc>2) {
        std::cout << "too many arguments! ignoring all file names except"
                  << argv[1] << std::endl;
    }

    TreeManager* tm = new TreeManager(argv[1]);


    TH1F* hnue = new TH1F("hnue",";E_{#nu};",10,0,10);

    GenTree* gen = tm->GetGenTree();
    static_cast<StructuredGenTree*>(gen);


    for(size_t ientry=0; ientry<gen->NEntries(); ientry++){

        gen->GetEntry(ientry);

        for(size_t i=0; gen->NGen(); i++){
            if(!gen->IsGenie(i)) continue;
            hnue->Fill(gen->NuP(i).E());
        }
    }

    auto c = new TCanvas();
    hnue->Draw();
    c->SaveAs("enu.png");
}
