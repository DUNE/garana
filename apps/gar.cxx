
//garana includes
#include "garana/Accessors/TreeManager.h"

//ROOT includes
#include <TH2F.h>
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
    TH1F* hg4 = new TH1F("hg4",htitle.c_str(),10,0,3);

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

    RecoTree* reco = tm->GetRecoTree();

    TH2F* h_recovtx_xy =  new TH2F("h_recovtx_xy",";reco vertex x [cm]; reco vertex y [cm]", 20, -200, 200, 20, -100, 100);
    TH2F* h_recovtx_zy =  new TH2F("h_recovtx_zy",";reco vertex z [cm]; reco vertex y [cm]", 20, -100, 100, 20, -100, 100);
    TH2F* h_recovtx_xz =  new TH2F("h_recovtx_xz",";reco vertex x [cm]; reco vertex z [cm]", 20, -200, 200, 20, -100, 100);

    for(size_t ientry=0; ientry<reco->NEntries(); ientry++){

        reco->GetEntry(ientry);

        // tracks
        for(size_t itrk=0; itrk<reco->NTrack(); itrk++) {
        	auto vtx = reco->TrackVertex(itrk);
        	h_recovtx_xy->Fill(vtx.X(), vtx.Y());
        	h_recovtx_zy->Fill(vtx.Z(), vtx.Y());
        	h_recovtx_xz->Fill(vtx.X(), vtx.Z());

        }// for tracks
    }// for reco

    TCanvas* c_recovtx_xy = new TCanvas("c_recovtx_xy","reco track vertex: X-Y");
    h_recovtx_xy->Draw("colz");
    c_recovtx_xy->SaveAs("reco_trk_vtx_xy.png");

    TCanvas* c_recovtx_zy = new TCanvas("c_recovtx_zy","reco track vertex: Z-Y");
    h_recovtx_zy->Draw("colz");
    c_recovtx_zy->SaveAs("reco_trk_vtx_zy.png");

    TCanvas* c_recovtx_xz = new TCanvas("c_recovtx_xz","reco track vertex: X-Y");
    h_recovtx_xz->Draw("colz");
    c_recovtx_xz->SaveAs("reco_trk_vtx_xz.png");


    // clean up bare pointers
    delete tm;
    delete gen;
    delete g4;
    delete reco;

    delete hnue;
    delete hg4;
    delete c;
    delete cg4;

    delete h_recovtx_xy;
    delete h_recovtx_zy;
    delete h_recovtx_xz;
    delete c_recovtx_xy;
    delete c_recovtx_zy;
    delete c_recovtx_xz;

    return 0;
}
