
//garana includes
#include "garana/Accessors/TreeManager.h"

//ROOT includes
#include <TH1F.h>
#include <TCanvas.h>

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

    // headerTree
    HeaderTree* header = tm->GetHeaderTree();
    std::cout << "input tree type: " << *header->TreeType() << std::endl;

    // genTree
    std::string htitle = "my garana histogram ("+*header->TreeType()+");E_{#nu} [GeV];";
    TH1F* hnue = new TH1F("hnue",htitle.c_str(),10,0,10);

    GenTree* gen = tm->GetGenTree();

    for(size_t ientry=0; ientry<gen->NEntries(); ientry++){

        gen->GetEntry(ientry);

        for(size_t i=0; i<gen->NGen(); i++){
            if(!gen->IsGenie(i)) continue;
            hnue->Fill(gen->NuP(i)->E());
        }
    }

    auto c = new TCanvas();
    hnue->Draw();
    std::string outname = "testhist_"+*header->TreeType()+".png";
    c->SaveAs(outname.c_str());

    /// g4Tree
    std::string htitleg4 = "my garana histogram ("+*header->TreeType()+");E_{tot} [GeV];";
    TH1F* hg4 = new TH1F("hg4",htitle.c_str(),10,0,10);

    G4Tree* g4 = tm->GetG4Tree();

    for(size_t ientry=0; ientry<g4->NEntries(); ientry++){

        g4->GetEntry(ientry);

        for(size_t i=0; i<g4->NSim(); i++){

            hg4->Fill(g4->SimMom(i)->at(0).E());
        }
    }

    auto cg4 = new TCanvas();
    hg4->Draw();
    outname = "testg4hist_"+*header->TreeType()+".png";
    cg4->SaveAs(outname.c_str());

    // clean up raw pointers
    delete tm;
    delete hnue;
    delete hg4;
    delete c;
    delete cg4;

    return 0;
}
