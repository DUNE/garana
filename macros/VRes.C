R__ADD_LIBRARY_PATH(/dune/app/users/birwin/garana_local_build/localProducts_garana_v00_00_13_e20_prof/garana/v00_00_13/slf7.x86_64.e20.prof/lib)
R__LOAD_LIBRARY(libGaranaAccessors.so)
R__LOAD_LIBRARY(libGaranaUtility.so)
R__ADD_INCLUDE_PATH(/dune/app/users/birwin/garana_local_build/localProducts_garana_v00_00_13_e20_prof/garana/v00_00_13/include)

/* Macro: FS Proton Reco Efficiency
 *  * Purpose 1: calculate the ratio of true final state protons that are matched with at least one track to
 *   * final state protons that are identified using Backtracker on tracks in the reconstruction tree (function of momentum)
 *    * Purpose 2: same calculation but as a function of angle (angle from drift direction, angle around drift direction)*/

#include "garana/Accessors/TreeManager.h"
#include "garana/Utility/Backtracker.h"
#include <TH1F.h>
#include <iostream>
#include <math.h>
#include <TStyle.h>
#include "functions.h"

using namespace garana;

void VRes()
{
string infile = "/dune/data/users/chilgenb/for_burke/fixed_vertices/structuredtree.root";

TreeManager* treeman 	= new TreeManager(infile);
Backtracker* bt 	= new Backtracker(treeman);
GenTree* gen		= treeman->GetGenTree();
G4Tree*  g4    		= treeman->GetG4Tree();
RecoTree* reco 		= treeman->GetRecoTree();
HeaderTree* header	= treeman->GetHeaderTree();

vector<int> particle_types= {2212,13,211,321};

TH1F* pvres   = new TH1F("pvres","Proton Vertex Resolution",20,0,240);
TH1F* lpvres  = new TH1F("lpvres","Good Proton Vertex Resolution",20,0,20);
TH2F* pvresp  = new TH2F("pvresp","Proton Vertex Resolution vs True Momentum",20,0.,3.,20,0.,5.);
TH2F* pvresx  = new TH2F("pvresx","Proton Vertex Resolution vs True Vertex X Position",20,-220.,220.,20,0.,5.);
TH2F* pvresy  = new TH2F("pvresy","Proton Vertex Resolution vs True Vertex Y Position",20,-210.,210.,20,0.,5.);
TH2F* pvresz  = new TH2F("pvresz","Proton Vertex Resolution vs True Vertex Z Position",20,-210.,210.,20,0.,5.);
TH2F* pvresd  = new TH2F("pvresd","Proton Vertex Resolution vs True Vertex Displacement",20,0.,304.,20,0.,5.);

TH1F* mvres   = new TH1F("mvres","Muon Vertex Resolution",20,0,140);
TH1F* lmvres  = new TH1F("lmvres","Good Muon Vertex Resolution",20,0,20);
TH2F* mvresp  = new TH2F("mvresp","Muon Vertex Resolution vs True Momentum",20,0.,3.,20,0.,5.);
TH2F* mvresx  = new TH2F("mvresx","Muon Vertex Resolution vs True Vertex X Position",20,-220.,220.,20,0.,5.);
TH2F* mvresy  = new TH2F("mvresy","Muon Vertex Resolution vs True Vertex Y Position",20,-210.,210.,20,0.,5.);
TH2F* mvresz  = new TH2F("mvresz","Muon Vertex Resolution vs True Vertex Z Position",20,-210.,210.,20,0.,5.);
TH2F* mvresd  = new TH2F("mvresd","Muon Vertex Resolution vs True Vertex Displacement",20,0.,304.,20,0.,5.);

TH1F* cpvres  = new TH1F("cpvres","Charged Pion Vertex Resolution",20,0,420);
TH1F* lcpvres = new TH1F("lcpvres","Good Charged Pion Vertex Resolution",20,0,20);
TH2F* cpvresp = new TH2F("cpvresp","Charged Pion Vertex Resolution vs True Momentum",20,0.,3.,20,0.,5.);
TH2F* cpvresx = new TH2F("cpvresx","Charged Pion Vertex Resolution vs True Vertex X Position",20,-220.,220.,20,0.,5.);
TH2F* cpvresy = new TH2F("cpvresy","Charged Pion Vertex Resolution vs True Vertex Y Position",20,-210.,210.,20,0.,5.);
TH2F* cpvresz = new TH2F("cpvresz","Charged Pion Vertex Resolution vs True Vertex Z Position",20,-210.,210.,20,0.,5.);
TH2F* cpvresd = new TH2F("cpvresd","Charged Pion Vertex Resolution vs True Vertex Displacement",20,0.,304.,20,0.,5.);

TH1F* kvres   = new TH1F("kvres","Charged Kaon Vertex Resolution",20,0,100);
TH1F* lkvres  = new TH1F("lkvres","Good Charged Kaon Vertex Resolution",20,0,20);
TH2F* kvresp  = new TH2F("kvresp","Charged Kaon Vertex Resolution vs True Momentum",20,0.,3.,20,0.,5.);
TH2F* kvresx  = new TH2F("kvresx","Charged Kaon Vertex Resolution vs True Vertex X Position",20,-220.,220.,20,0.,5.);
TH2F* kvresy  = new TH2F("kvresy","Charged Kaon Vertex Resolution vs True Vertex Y Position",20,-210.,210.,20,0.,5.);
TH2F* kvresz  = new TH2F("kvresz","Charged Kaon Vertex Resolution vs True Vertex Z Position",20,-210.,210.,20,0.,5.);
TH2F* kvresd  = new TH2F("kvresd","Charged Kaon Vertex Resolution vs True Vertex Displacement",20,0.,304.,20,0.,5.);

vector<TH1F*> histos = {pvres,mvres,cpvres,kvres};
vector<TH1F*> lhistos = {lpvres,lmvres,lcpvres,lkvres};
vector<TH2F*> histos2D = {pvresp,mvresp,cpvresp,kvresp};
vector<TH2F*> position = {pvresx,pvresy,pvresz,pvresd,mvresx,mvresy,mvresz,mvresd,cpvresx,cpvresy,cpvresz,cpvresd,kvresx,kvresy,kvresz,kvresd};

const char *titles[4] = {"Proton Vertex Resolution","Muon Vertex Resolution","Charged Pion Vertex Resolution","Charged Kaon Vertex Resolution"};
const char *titles2D[4] = {"Proton Vertex Resolution vs True Momentum","Muon Vertex Resolution vs True Momentum","Charged Pion Vertex Resolution vs True Momentum","Charged Kaon Vertex Resolution vs True Momentum"};
const char *saves[4] = {"VResFigures/PVRes.png","VResFigures/MVRes.png","VResFigures/CPVRes.png","VResFigures/KVRes.png"};
const char *ltitles[4] = {"Good Proton Vertex Resolution","Good Muon Vertex Resolution","Good Charged Pion Vertex Resolution","Good Charged Kaon Vertex Resolution"};
const char *positionTitles[16] = {"Proton VRes vs X position","Proton VRes vs Y position","Proton VRes vs Z position","Proton VRes vs True Displacement","Muon VRes vs X position","Muon VRes vs Y position","Muon VRes vs Z position","Muon VRes vs True Displacement","Charged Pion VRes vs X position","Charged Pion VRes vs Y position","Charged Pion VRes vs Z position","Charged Pion VRes vs True Displacement","Charged Kaon VRes vs X position","Charged Kaon VRes vs Y position","Charged Kaon VRes vs Z position","Charged Kaon VRes vs True Displacement"};
const char *positionsaves[4] = {"VResFigures/PposVRes.png","VResFigures/MposVRes.png","VResFigures/CPposVRes.png","VResFigures/KposVRes.png"};
std::cout<<"=======================================\n"<<std::endl;
std::cout<<"Number of Entries: "<<treeman->NEntries()<<std::endl;
std::cout<<"======================================="<<std::endl;

for(UInt_t ipdg = 0; ipdg<particle_types.size(); ipdg++)
{
	pair<int,double> max_p; 
        for(UInt_t ientry=0; ientry<treeman->NEntries(); ientry++)              //Loop through all events
                {
                if(ientry%1000 == 0)
                {
                        std::cout<<"Event: "<<ientry<<std::endl;
                }
                treeman->GetEntry(ientry);
                bt->FillMaps();

                for(UInt_t ig4p=0; ig4p<g4->NSim(); ig4p++)                     //Loop through true particles
                        {
                        if(g4->IsPrimary(ig4p) && g4->PDG(ig4p) == particle_types.at(ipdg))
                                {
                                        int association = 0;
					pair<int,float> Responsible_track;
                                        if(-220.<gen->NuVertex(bt->G4ParticleToGTruth(ig4p))->X()<220. && sqrt(pow(gen->NuVertex(bt->G4ParticleToGTruth(ig4p))->Y(),2)+pow(gen->NuVertex(bt->G4ParticleToGTruth(ig4p))->Z(),2))<210.)
                                        {
						if(g4->SimMomEnter(ig4p,0)->P()>max_p.second)
						{
							max_p.first  = ig4p;
							max_p.second = g4->SimMomEnter(ig4p,0)->P();
						}
					}
				}
			}//G4 Particle Loop
                                        
				const vector<UInt_t>* list_of_vertices = bt->G4ParticleToVertices(max_p.first);
                                if(list_of_vertices->size()==1) //Fill Reco Histos
                                {
					double V_Res = sqrt(pow((reco->GetVertex(list_of_vertices->at(0))->X()-header->TpcCenter()->X())-gen->NuVertex(bt->G4ParticleToGTruth(max_p.first))->X(),2)+pow((reco->GetVertex(list_of_vertices->at(0))->Y()-header->TpcCenter()->Y())-gen->NuVertex(bt->G4ParticleToGTruth(max_p.first))->Y(),2)+pow((reco->GetVertex(list_of_vertices->at(0))->Z()-header->TpcCenter()->Z())-gen->NuVertex(bt->G4ParticleToGTruth(max_p.first))->Z(),2));
					histos.at(ipdg)->Fill(V_Res);
					lhistos.at(ipdg)->Fill(V_Res);
					histos2D.at(ipdg)->Fill(g4->SimMomEnter(max_p.first,0)->P(),V_Res);
					position.at(4*ipdg)->Fill(gen->NuVertex(bt->G4ParticleToGTruth(max_p.first))->X(),V_Res);
					position.at(4*ipdg+1)->Fill(gen->NuVertex(bt->G4ParticleToGTruth(max_p.first))->Y(),V_Res);
					position.at(4*ipdg+2)->Fill(gen->NuVertex(bt->G4ParticleToGTruth(max_p.first))->Z(),V_Res);
					position.at(4*ipdg+3)->Fill(sqrt(pow(gen->NuVertex(bt->G4ParticleToGTruth(max_p.first))->X(),2)+pow(gen->NuVertex(bt->G4ParticleToGTruth(max_p.first))->Y(),2)+pow(gen->NuVertex(bt->G4ParticleToGTruth(max_p.first))->Z(),2)),V_Res);
				}
		}//Event Loop
//pvres->Sumw2();
gStyle->SetOptStat(0);
TCanvas* p1 = new TCanvas("p1","p1",1000,1000);
p1->Divide(2,2);
p1->cd(1);
histos.at(ipdg)->SetTitle(titles[ipdg]);
histos.at(ipdg)->GetXaxis()->SetTitle("Distance between true and reco vertex");
histos.at(ipdg)->Draw("E");
p1->cd(2);
lhistos.at(ipdg)->SetTitle(ltitles[ipdg]);
lhistos.at(ipdg)->GetXaxis()->SetTitle("Distance between true and reco vertex");
lhistos.at(ipdg)->Draw("E");
p1->cd(3);
histos2D.at(ipdg)->SetTitle(titles2D[ipdg]);
histos2D.at(ipdg)->GetXaxis()->SetTitle("True Momentum");
histos2D.at(ipdg)->GetYaxis()->SetTitle("Distnace between true and reco vertex");
histos2D.at(ipdg)->Draw("colz");
p1->Print(saves[ipdg]);

TCanvas* a1 = new TCanvas("a1","a1",1000,1000);
a1->Divide(2,2);

//VRes vs True Vertex X displacement
a1->cd(1);
position.at(4*ipdg)->SetTitle(positionTitles[4*ipdg]);
position.at(4*ipdg)->GetXaxis()->SetTitle("X position");
position.at(4*ipdg)->GetYaxis()->SetTitle("Vertex Resolution");
position.at(4*ipdg)->Draw("colz");

//VRes vs True Vertex Y displacement
a1->cd(2);
position.at(4*ipdg+1)->SetTitle(positionTitles[4*ipdg+1]);
position.at(4*ipdg+1)->GetXaxis()->SetTitle("Y position");
position.at(4*ipdg+1)->GetYaxis()->SetTitle("Vertex Resolution");
position.at(4*ipdg+1)->Draw("colz");

//VRes vs True Vertex Z displacement
a1->cd(3);
position.at(4*ipdg+2)->SetTitle(positionTitles[4*ipdg+2]);
position.at(4*ipdg+2)->GetXaxis()->SetTitle("Z position");
position.at(4*ipdg+2)->GetYaxis()->SetTitle("Vertex Resolution");
position.at(4*ipdg+2)->Draw("colz");

//VRes vs True Vertex true displacement
a1->cd(4);
position.at(4*ipdg+3)->SetTitle(positionTitles[4*ipdg+3]);
position.at(4*ipdg+3)->GetXaxis()->SetTitle("True Displacement");
position.at(4*ipdg+3)->GetYaxis()->SetTitle("Vertex Resolution");
position.at(4*ipdg+3)->Draw("colz");

a1->Print(positionsaves[ipdg]);
}//FS Particle Loop

}










