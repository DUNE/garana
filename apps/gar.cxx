
//garana includes
#include "garana/Accessors/TreeManager.h"
#include "garana/Utility/Backtracker.h"

//ROOT includes
#include <TH2F.h>
#include <TCanvas.h>
#include <TEfficiency.h>
#include <TGraphAsymmErrors.h>

//c++ includes
#include <iostream>
using std::cout;
using std::endl;

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

    ///////// histograms /////////////////
    // headerTree
    HeaderTree* header = tm->GetHeaderTree();
    std::cout << "input tree type: " << *header->TreeType() << std::endl;

    // genTree
    std::string htitle = "my garana histogram ("+*header->TreeType()+");E_{#nu} [GeV];";
    TH1F* hnue = new TH1F("hnue",htitle.c_str(),10,0,10);

    /// g4Tree
    std::string htitleg4 = "my garana histogram ("+*header->TreeType()+");E_{tot} [GeV];";
    TH1F* hg4 = new TH1F("hg4",htitle.c_str(),10,0,3);
    TH1F* hg4_efrac = new TH1F("hg4_efrac","Fraction of Incident #nu Energy; E_{G4particle}/E_{#nu};",50,0,1);
    TH1F* hg4_eprot = new TH1F("hg4_eprot","primary protons;KE [MeV];",20,0,10);
    TH1F* hg4_nprot = new TH1F("hg4_nprot",";proton multiplicity;",20,0,20); //Ar has 18 protons

    // recoTree
    TH2F* h_recotrk_vtx_xy =  new TH2F("h_recotrk_vtx_xy",";reco vertex x [cm]; reco vertex y [cm]", 20, -250, 250, 20, -400, 100);
    TH2F* h_recotrk_vtx_zy =  new TH2F("h_recotrk_vtx_zy",";reco vertex z [cm]; reco vertex y [cm]", 20, 1200, 1800, 20, -400, 100);
    TH2F* h_recotrk_vtx_xz =  new TH2F("h_recotrk_vtx_xz",";reco vertex x [cm]; reco vertex z [cm]", 20, -250, 250, 20, 1200, 1800);

    TH2F* h_recovtx_vtx_xy =  new TH2F("h_recovtx_vtx_xy",";reco vertex x [cm]; reco vertex y [cm]", 20, -250, 250, 20, -400, 100);
    TH2F* h_recovtx_vtx_zy =  new TH2F("h_recovtx_vtx_zy",";reco vertex z [cm]; reco vertex y [cm]", 20, 1200, 1800, 20, -400, 100);
    TH2F* h_recovtx_vtx_xz =  new TH2F("h_recovtx_vtx_xz",";reco vertex x [cm]; reco vertex z [cm]", 20, -250, 250, 20, 1200, 1800);

    TEfficiency* eff_reco_prot_integ = new TEfficiency("eff_reco_prot_integ","",1,0,1); //integrated proton reco eff
    TEfficiency* eff_reco_prot_tprot = new TEfficiency("eff_reco_prot_tprot","proton reconstruction efficiency; proton KE [MeV]; "
    		                                    "#epsilon_{reco}",40,0,2); //proton reco eff vs. proton KE [MeV]

    //////// tree accessors //////////
    GenTree*  gen = tm->GetGenTree();
    G4Tree*   g4 = tm->GetG4Tree();
    RecoTree* reco = tm->GetRecoTree();

    // truth matching utility
    Backtracker bt(tm);

    /////// main event loop ////////// (e.g. over single genie interactions)
    for(size_t ientry=0; ientry<tm->NEntries(); ientry++){

        tm->GetEntry(ientry); //gets entry for all trees
        bt.FillMaps(); //load associations for this entry

        cout << "gen stuff" << endl;
        // genTree
        for(size_t i=0; i<gen->NGen(); i++){
            if(!gen->IsGenie(i)) continue;
            hnue->Fill(gen->NuP(i)->E());

            /*for(size_t ifsp=0; ifsp<gen->NFSParticles(i); ifsp++){
            	std::cout << "FSParticle " << ifsp << " with trackID " << gen->FSTrackId(i,ifsp) << std::endl;
            }*/
        }

        cout << "g4 stuff" << endl;
        // g4Tree
        size_t nprot = 0;
        for(size_t i=0; i<g4->NSim(); i++){

            hg4->Fill(g4->SimMomEnter(i)->at(0)->E());
            hg4_efrac->Fill(g4->SimMomEnter(i)->at(0)->E()/gen->NuP(bt.G4ParticleToGTruth(i))->E());

            if(g4->PDG(i) == 2212 && g4->IsPrimary(i)) { //is it a primary proton?
            	nprot++;
            	hg4_eprot->Fill(1.e3*(g4->SimMomEnter(i)->at(0)->E()-0.938272)); //KE in [MeV]

                const vector<UInt_t>* matchedtracks = bt.G4ParticleToTracks(i);
                eff_reco_prot_integ->Fill(matchedtracks->size()>0, 0.5);
                eff_reco_prot_tprot->Fill(matchedtracks->size()>0, 1e3*(g4->SimMomEnter(i)->at(0)->E()-0.938272));

            }
        }

    	hg4_nprot->Fill(nprot);

        cout << "reco stuff" << endl;
        // recoTree
        // tracks
        for(size_t itrk=0; itrk<reco->NTrack(); itrk++) {
        	auto trkvtx = reco->TrackVertex(itrk);
        	h_recotrk_vtx_xy->Fill(trkvtx->X(), trkvtx->Y());
        	h_recotrk_vtx_zy->Fill(trkvtx->Z(), trkvtx->Y());
        	h_recotrk_vtx_xz->Fill(trkvtx->X(), trkvtx->Z());

        }// end for tracks

        // vertices
        for(size_t ivtx=0; ivtx<reco->NVertex(); ivtx++) {
        	auto vtx = reco->GetVertex(ivtx);
        	h_recovtx_vtx_xy->Fill(vtx->X(), vtx->Y());
        	h_recovtx_vtx_zy->Fill(vtx->Z(), vtx->Y());
        	h_recovtx_vtx_xz->Fill(vtx->X(), vtx->Z());

        }// end for vertices

    }//end main event loop

    //hg4_nprot->SetBinContent(hg4_nprot->GetXaxis()->GetNbins(),hg4_nprot->GetBinContent(hg4_nprot->GetXaxis()->GetNbins()+1));
    cout << "proton reconstruction efficiency: " << eff_reco_prot_integ->GetEfficiency(1) << endl;

    auto c = new TCanvas();
    hnue->Draw();
    std::string outname = "testhist_"+*header->TreeType()+".png";
    c->SaveAs(outname.c_str());

    auto cg4 = new TCanvas();
    hg4->Draw();
    outname = "testg4hist_"+*header->TreeType()+".png";
    cg4->SaveAs(outname.c_str());

    outname = "g4_efrac_of_nu_"+*header->TreeType()+".png";
    auto cg4_efrac = new TCanvas();
    hg4_efrac->Draw();
    cg4_efrac->SaveAs(outname.c_str());

    outname = "g4_nproton_"+*header->TreeType()+".png";
    auto cg4_nprot = new TCanvas();
    hg4_nprot->Draw();
    cg4_nprot->SaveAs(outname.c_str());

    outname = "g4_eproton_"+*header->TreeType()+".png";
    auto cg4_eprot = new TCanvas();
    hg4_eprot->Draw("e0hist");
    cg4_eprot->SaveAs(outname.c_str());

    TCanvas* c_recotrk_vtx_xy = new TCanvas("c_recotrk_vtx_xy","reco track vertex: X-Y");
    h_recotrk_vtx_xy->Draw("colz");
    h_recovtx_vtx_xy->Draw("same");
    c_recotrk_vtx_xy->SaveAs("reco_trk_vtx_xy.png");

    TCanvas* c_recotrk_vtx_zy = new TCanvas("c_recotrk_vtx_zy","reco track vertex: Z-Y");
    h_recotrk_vtx_zy->Draw("colz");
    h_recovtx_vtx_zy->Draw("same*");
    c_recotrk_vtx_zy->SaveAs("reco_trk_vtx_zy.png");

    TCanvas* c_recotrk_vtx_xz = new TCanvas("c_recotrk_vtx_xz","reco track vertex: X-Y");
    h_recotrk_vtx_xz->Draw("colz");
    h_recovtx_vtx_xz->Draw("same*");
    c_recotrk_vtx_xz->SaveAs("reco_trk_vtx_xz.png");

    TCanvas* c_recovtx_vtx_xy = new TCanvas("c_recovtx_vtx_xy","reco vertex: X-Y");
    h_recovtx_vtx_xy->Draw("colz");
    c_recovtx_vtx_xy->SaveAs("reco_vtx_vtx_xy.png");

    TCanvas* c_recovtx_vtx_zy = new TCanvas("c_recovtx_vtx_zy","reco vertex: Z-Y");
    h_recovtx_vtx_zy->Draw("colz");
    c_recovtx_vtx_zy->SaveAs("reco_vtx_vtx_zy.png");

    TCanvas* c_recovtx_vtx_xz = new TCanvas("c_recovtx_vtx_xz","reco vertex: X-Y");
    h_recovtx_vtx_xz->Draw("colz");
    c_recovtx_vtx_xz->SaveAs("reco_vtx_vtx_xz.png");

    TCanvas* c_reco_peff_tp = new TCanvas();
    eff_reco_prot_tprot->Draw();
    c_reco_peff_tp->Update();
    auto g = eff_reco_prot_tprot->GetPaintedGraph();
    g->GetYaxis()->SetRangeUser(0,1);
    g->SetMarkerStyle(8);
    g->SetMarkerColor(kBlue);
    g->SetLineWidth(2);
    g->Draw("pl");

    c_reco_peff_tp->SaveAs("reco_proton_eff_tproton.png");

    // clean up bare pointers
    delete tm;
    delete gen;
    delete g4;
    delete reco;

    delete hnue;
    delete hg4;
    delete c;
    delete cg4;

    delete h_recotrk_vtx_xy;
    delete h_recotrk_vtx_zy;
    delete h_recotrk_vtx_xz;
    delete h_recovtx_vtx_xy;
    delete h_recovtx_vtx_zy;
    delete h_recovtx_vtx_xz;
    delete c_recotrk_vtx_xy;
    delete c_recotrk_vtx_zy;
    delete c_recotrk_vtx_xz;
    delete c_recovtx_vtx_xy;
    delete c_recovtx_vtx_zy;
    delete c_recovtx_vtx_xz;

    return 0;
}
