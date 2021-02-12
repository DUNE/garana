
//garana includes
#include "include/garana/Accessors/TreeManager.h"

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

    std::cout << "new TreeManager" << std::endl;

    TH1F* hnue = new TH1F("hnue",";E_{#nu};",10,0,10);

    std::cout << "get GenTree*" << std::endl;
    GenTree* gen = tm->GetGenTree();

    std::cout << "loop over entries" << std::endl;
    for(size_t ientry=0; ientry<gen->NEntries(); ientry++){

        gen->GetEntry(ientry);

        std::cout << "loop over " << gen->NGen() <<" igen" << std::endl;
        for(size_t i=0; i<gen->NGen(); i++){
            std::cout << "check if GENIE" << std::endl;
            if(!gen->IsGenie(i)) continue;
            std::cout << "found GENIE" << std::endl;
            hnue->Fill(gen->NuP(i).E());
            std::cout << "fill hist" << std::endl;
        }
    }

    std::cout << "draw" << std::endl;
    auto c = new TCanvas();
    hnue->Draw();
    c->SaveAs("enu.png");

    return 0;
}
