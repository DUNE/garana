R__ADD_LIBRARY_PATH(/dune/app/users/birwin/garana_local_build/localProducts_garana_v00_00_13_e20_prof/garana/v00_00_13/slf7.x86_64.e20.prof/lib)
R__LOAD_LIBRARY(libGaranaAccessors.so)
R__LOAD_LIBRARY(libGaranaUtility.so)
R__ADD_INCLUDE_PATH(/dune/app/users/birwin/garana_local_build/localProducts_garana_v00_00_13_e20_prof/garana/v00_00_13/include)

/* Macro: FS Proton Reco Efficiency
 * Purpose 1: calculate the ratio of true final state protons that are matched with at least one track to
 * final state protons that are identified using Backtracker on tracks in the reconstruction tree (function of momentum)
 * Purpose 2: same calculation but as a function of angle (angle from drift direction, angle around drift direction)*/

#include "garana/Accessors/TreeManager.h"
#include "garana/Utility/Backtracker.h"
#include <TH1F.h>
#include <iostream>
#include <math.h>
#include <TStyle.h>
#include "functions.h"

using namespace garana;

void Eff()
{
//string infile = "/dune/data/users/chilgenb/for_burke/structuredtree_bigish.root";
string infile = "/dune/data/users/birwin/structuredtree_files/structuredtree_full.root";

TreeManager* treeman = new TreeManager(infile);
Backtracker* bt = new Backtracker(treeman);
GenTree* gen = treeman->GetGenTree();
G4Tree*  g4  = treeman->GetG4Tree();
RecoTree* reco = treeman->GetRecoTree();

vector<int> particle_types= {2212,13,211,321};


//Declare histograms for all particle types
//Proton
TH1F* ptp = new TH1F("ptp","True Proton Momentum",100,0.,3.);
TH2F* pta = new TH2F("pta","True Proton Drift Angle",10,0,M_PI,20,-M_PI,M_PI);
TH1F* prp = new TH1F("prp","True Momentum for Reconstructed Protons",100,0.,3.);
TH2F* pra = new TH2F("pra","Reconstructed Proton Drift Angles",10,0,M_PI,20,-M_PI,M_PI);

TH1F* ptazim = new TH1F("ptazim","True Proton Angle about Drift Direction",60,-M_PI,M_PI);
TH1F* ptpola = new TH1F("ptpola","True Proton Angle from Drift Direction",30,0,M_PI);
TH1F* prazim = new TH1F("prazim","True Angle about Drift Direction for Reco Protons",60,-M_PI,M_PI);
TH1F* prpola = new TH1F("prpola","True Angle from Drift Direction for Reco Protons",30,0,M_PI);

//Muons
TH1F* mtp = new TH1F("mtp","True Muon Momentum",100,0.,3.);
TH2F* mta = new TH2F("mta","True Muon Drift Angle",10,0,M_PI,20,-M_PI,M_PI);
TH1F* mrp = new TH1F("mrp","True Momentum for Reconstructed Muons",100,0.,3.);
TH2F* mra = new TH2F("mra","Reconstructed Muon Drift Angles",10,0,M_PI,20,-M_PI,M_PI);

TH1F* mtazim = new TH1F("mtazim","True Muon Angle about Drift Direction",60,-M_PI,M_PI);
TH1F* mtpola = new TH1F("mtpola","True Muon Angle from Drift Direction",30,0,M_PI);
TH1F* mrazim = new TH1F("mrazim","True Angle about Drift Direction for Reco Muons",60,-M_PI,M_PI);
TH1F* mrpola = new TH1F("mrpola","True Angle from Drift Direction for Reco Muons",30,0,M_PI);

//Charged Pions
TH1F* cptp = new TH1F("cptp","True Charged Pion Momentum",100,0.,3.);
TH2F* cpta = new TH2F("cpta","True Charged Pion Drift Angle",10,0,M_PI,20,-M_PI,M_PI);
TH1F* cprp = new TH1F("cprp","True Momentum for Reconstructed Charged Pions",100,0.,3.);
TH2F* cpra = new TH2F("cpra","Reconstructed Charged Pion Drift Angles",10,0,M_PI,20,-M_PI,M_PI);

TH1F* cptazim = new TH1F("cptazim","True Charged Pion Angle about Drift Direction",60,-M_PI,M_PI);
TH1F* cptpola = new TH1F("cptpola","True Charged Pion Angle from Drift Direction",30,0,M_PI);
TH1F* cprazim = new TH1F("cprazim","True Angle about Drift Direction for Reco Charged Pions",60,-M_PI,M_PI);
TH1F* cprpola = new TH1F("cprpola","True Angle from Drift Direction for Reco Charged Pions",30,0,M_PI);

//Charged Kaons
TH1F* ktp = new TH1F("ktp","True Charged Kaon Momentum",100,0.,3.);
TH2F* kta = new TH2F("kta","True Charged Kaon Drift Angles",10,0,M_PI,20,-M_PI,M_PI);
TH1F* krp = new TH1F("krp","True Momentum for Reconstructed Charged Kaons",100,0.,3.);
TH2F* kra = new TH2F("kra","Reconstructed Charged Kaon Drift Angles",10,0,M_PI,20,-M_PI,M_PI);

TH1F* ktazim = new TH1F("ktazim","True Charged Kaon Angle about Drift Direction",60,-M_PI,M_PI);
TH1F* ktpola = new TH1F("ktpola","True Charged Kaon Angle from Drift Direction",30,0,M_PI);
TH1F* krazim = new TH1F("krazim","True Angle about Drift Direction for Reco Charged Kaons",60,-M_PI,M_PI);
TH1F* krpola = new TH1F("krpola","True Angle from Drift Direction for Reco Charged Kaons",30,0,M_PI);

vector<TH1F*> oneD_histos = {ptp,prp,mtp,mrp,cptp,cprp,ktp,krp};
vector<TH2F*> twoD_histos = {pta,pra,mta,mra,cpta,cpra,kta,kra};
vector<TH1F*> azim_histos = {ptazim,prazim,mtazim,mrazim,cptazim,cprazim,ktazim,krazim};
vector<TH1F*> pola_histos = {ptpola,prpola,mtpola,mrpola,cptpola,cprpola,ktpola,krpola};



for(UInt_t ipdg = 0; ipdg<1; ipdg++)//particle_types.size(); ipdg++)
{
	for(UInt_t ientry=0; ientry<treeman->NEntries(); ientry++)		//Loop through all events
		{
		if(ientry%1000 == 0)
		{
			std::cout<<"Event: "<<ientry<<std::endl;
		}
		treeman->GetEntry(ientry);
		bt->FillMaps();

		for(UInt_t ig4p=0; ig4p<g4->NSim(); ig4p++)			//Loop through true particles
			{
			if(g4->IsPrimary(ig4p) && g4->PDG(ig4p) == particle_types.at(ipdg))
				{
					int association = 0;
					if(-220.<gen->NuVertex(bt->G4ParticleToGTruth(ig4p))->X()<220. && sqrt(pow(gen->NuVertex(bt->G4ParticleToGTruth(ig4p))->Y(),2)+pow(gen->NuVertex(bt->G4ParticleToGTruth(ig4p))->Z(),2))<210.)
					{
						auto truth_angles = Truth_Direction(g4,ig4p);
						pola_histos.at(2*ipdg)->Fill(truth_angles.first);
						azim_histos.at(2*ipdg)->Fill(truth_angles.second);
						oneD_histos.at(2*ipdg)->Fill(g4->SimMomEnter(ig4p,0)->P());
						twoD_histos.at(2*ipdg)->Fill(truth_angles.first,truth_angles.second);	
						for(UInt_t itrk=0; itrk<reco->NTrack(); itrk++)	//Loop through reconstructed tracks
						{
							auto PrimeParticle = bt->TrackToG4ParticleDeposit(itrk);
							if(ig4p==PrimeParticle.first)
							{
								association += 1;
							}	
						}
					}
				if(association != 0)
				{
					oneD_histos.at(2*ipdg+1)->Fill(g4->SimMomEnter(ig4p,0)->P());
					auto reco_angles = Truth_Direction(g4,ig4p);
					pola_histos.at(2*ipdg+1)->Fill(reco_angles.first);
					azim_histos.at(2*ipdg+1)->Fill(reco_angles.second);
                                        twoD_histos.at(2*ipdg+1)->Fill(reco_angles.first,reco_angles.second);
				}
				}
			}	
		}

	oneD_histos.at(2*ipdg)->Sumw2();
	oneD_histos.at(2*ipdg+1)->Sumw2();
}
//Efficiency Plots
//Protons

gStyle->SetOptStat(0);

TCanvas* cp1 = new TCanvas("Proton Efficiency vs. Momentum","Efficiency vs. Momentum",2000,1000);
cp1->Divide(2,1);

cp1->cd(1);
TH1D* epFull =(TH1D*) oneD_histos.at(1)->Clone("epFull");
epFull->Divide(oneD_histos.at(1),oneD_histos.at(0));
TH1D* ep400  =(TH1D*) epFull->Clone("ep400");
epFull->SetTitle("Proton Momentum Reconstruction Efficiency");
epFull->GetXaxis()->SetTitle("Momentum (GeV/c)");
epFull->GetXaxis()->SetRangeUser(0.,3.);
epFull->GetYaxis()->SetRangeUser(0.,1.0);
epFull->Draw("E");

cp1->cd(2);
ep400->SetTitle("Low Momentum Efficiency");
ep400->GetXaxis()->SetTitle("Momentum (GeV/c)");
ep400->GetXaxis()->SetRangeUser(0.,.4);
ep400->GetYaxis()->SetRangeUser(0.,1.0);
ep400->Draw("E");

cp1->Print("ProtonFigures/momeffpro.png");

TCanvas* cp2 = new TCanvas("Garana Proton Reco Efficiency vs. Drift Angle","Garana Reco Efficiency vs. Drift Angle",1000,1000);
cp2->Divide(2,2);
cp2->cd(2);
TH2D* epa =(TH2D*) twoD_histos.at(1)->Clone("epa");
epa->Divide(twoD_histos.at(1),twoD_histos.at(0));
epa->SetTitle("Proton Angular Reconstruction Efficiency");
epa->GetXaxis()->SetTitle("Angle from Drift Direction (radians)");
epa->GetYaxis()->SetTitle("Angle about Drift Direction (radians)");
epa->GetZaxis()->SetRangeUser(0.,1.);
epa->Draw("colz");

cp2->cd(1);
azim_histos.at(1)->Sumw2();
azim_histos.at(0)->Sumw2();
TH1D* epazim=(TH1D*) prazim->Clone("epazim");
epazim->Divide(azim_histos.at(1),azim_histos.at(0));
epazim->SetTitle("Angle about Drift Direction Efficiency");
epazim->Draw("E");

cp2->cd(4);
pola_histos.at(1)->Sumw2();
pola_histos.at(0)->Sumw2();
TH1D* eppola=(TH1D*) prpola->Clone("eppola");
eppola->Divide(pola_histos.at(1),pola_histos.at(0));
eppola->SetTitle("Angle from Drift Direction Efficiency");
eppola->Draw("E");

cp2->Print("ProtonFigures/angeffpro.png");

//Muons
TCanvas* cm1 = new TCanvas("Muon Efficiency vs. Momentum","Efficiency vs. Momentum",2000,1000);
cm1->Divide(2,1);

cm1->cd(1);
TH1D* emFull =(TH1D*) oneD_histos.at(3)->Clone("emFull");
emFull->Divide(oneD_histos.at(3),oneD_histos.at(2));
TH1D* em400  =(TH1D*) emFull->Clone("em400");
emFull->SetTitle("Muon Momentum Reconstruction Efficiency");
emFull->GetXaxis()->SetTitle("Momentum (GeV/c)");
emFull->GetXaxis()->SetRangeUser(0.,3.);
emFull->GetYaxis()->SetRangeUser(0.,1.);
emFull->Draw("E");

cm1->cd(2);
em400->SetTitle("Low Momentum Efficiency");
em400->GetXaxis()->SetTitle("Momentum (GeV/c)");
em400->GetXaxis()->SetRangeUser(0.,.4);
em400->GetYaxis()->SetRangeUser(0.,1.0);
em400->Draw("E");
cm1->Print("MuonFigures/momeffmu.png");

TCanvas* cm2 = new TCanvas("Garana Muon Reco Efficiency vs. Drift Angle","Garana Reco Efficiency vs. Drift Angle",1000,1000);
cm2->Divide(2,2);
cm2->cd(2);
TH2D* ema =(TH2D*) twoD_histos.at(3)->Clone("ema");
ema->Divide(twoD_histos.at(3),twoD_histos.at(2));
ema->SetTitle("Muon Angular Reconstruction Efficiency");
ema->GetXaxis()->SetTitle("Angle from Drift Direction (radians)");
ema->GetYaxis()->SetTitle("Angle about Drift Direction (radians)");
ema->GetZaxis()->SetRangeUser(0.,1.);
ema->Draw("col");

cm2->cd(1);
azim_histos.at(3)->Sumw2();
azim_histos.at(2)->Sumw2();
TH1D* emazim=(TH1D*) azim_histos.at(3)->Clone("emazim");
emazim->Divide(azim_histos.at(3),azim_histos.at(2));
emazim->SetTitle("Angle about Drift Direction Efficiency");
emazim->Draw("E");

cm2->cd(4);
pola_histos.at(3)->Sumw2();
pola_histos.at(2)->Sumw2();
TH1D* empola=(TH1D*) mrpola->Clone("empola");
empola->Divide(pola_histos.at(3),pola_histos.at(2));
empola->SetTitle("Angle from Drift Direction Efficiency");
empola->Draw("E");
cm2->Print("MuonFigures/angeffmu.png");


//Charged Pions
TCanvas* ccp1 = new TCanvas("Charged Pion Efficiency vs. Momentum","Efficiency vs. Momentum",2000,1000);
ccp1->Divide(2,1);

ccp1->cd(1);
TH1D* ecpFull =(TH1D*) oneD_histos.at(5)->Clone("ecpFull");
ecpFull->Divide(oneD_histos.at(5),oneD_histos.at(4));
TH1D* ecp400  =(TH1D*) ecpFull->Clone("ecp400");
ecpFull->SetTitle("Charged Pion Momentum Reconstruction Efficiency");
ecpFull->GetXaxis()->SetTitle("Momentum (GeV/c)");
ecpFull->GetXaxis()->SetRangeUser(0.,3.);
ecpFull->GetYaxis()->SetRangeUser(0.,1.);
ecpFull->Draw("E");

ccp1->cd(2);
ecp400->SetTitle("Low Momentum Efficiency");
ecp400->GetXaxis()->SetTitle("Momentum (GeV/c)");
ecp400->GetXaxis()->SetRangeUser(0.,.4);
ecp400->GetYaxis()->SetRangeUser(0.,1.0);
ecp400->Draw("E");
ccp1->Print("CPFigures/momeffcp.png");

TCanvas* ccp2 = new TCanvas("Garana Charged Pion Reco Efficiency vs. Drift Angle","Garana Reco Efficiency vs. Drift Angle",1000,1000);
ccp2->Divide(2,2);
ccp2->cd(2);
TH2D* ecpa =(TH2D*) twoD_histos.at(5)->Clone("ecpa");
ecpa->Divide(twoD_histos.at(5),twoD_histos.at(4));
ecpa->SetTitle("Charged Pion Angular Reconstruction Efficiency");
ecpa->GetXaxis()->SetTitle("Angle from Drift Direction");
ecpa->GetYaxis()->SetTitle("Angle about Drift Direction");
ecpa->GetZaxis()->SetRangeUser(0.,1.);
ecpa->Draw("col");

ccp2->cd(1);
azim_histos.at(5)->Sumw2();
azim_histos.at(4)->Sumw2();
TH1D* ecpazim=(TH1D*) azim_histos.at(5)->Clone("ecpazim");
ecpazim->Divide(azim_histos.at(5),azim_histos.at(4));
ecpazim->SetTitle("Angle about Drift Direction Efficiency");
ecpazim->Draw("E");

ccp2->cd(4);
pola_histos.at(4)->Sumw2();
pola_histos.at(5)->Sumw2();
TH1D* ecppola=(TH1D*) cprpola->Clone("ecppola");
ecppola->Divide(pola_histos.at(5),pola_histos.at(4));
ecppola->SetTitle("Angle from Drift Direction Efficiency");
ecppola->Draw("E");
ccp2->Print("CPFigures/angeffcp.png");

//Charged Kaons
TCanvas* ck1 = new TCanvas("Charged Kaon Efficiency vs. Momentum","Charged Kaon Efficiency vs. Momentum",2000,1000);
ck1->Divide(2,1);

ck1->cd(1);
TH1D* ekFull =(TH1D*) oneD_histos.at(7)->Clone("ekFull");
ekFull->Divide(oneD_histos.at(7),oneD_histos.at(6));
TH1D* ek400  =(TH1D*) ekFull->Clone("ek400");
ekFull->SetTitle("Charged Kaon Angular Reconstruction Efficiency");
ekFull->GetXaxis()->SetTitle("Momentum (GeV/c)");
ekFull->GetXaxis()->SetRangeUser(0.,3.);
ekFull->GetYaxis()->SetRangeUser(0.,1.);
ekFull->Draw("E");

ck1->cd(2);
ek400->SetTitle("Low Momentum Efficiency");
ek400->GetXaxis()->SetTitle("Momentum (GeV/c)");
ek400->GetXaxis()->SetRangeUser(0.,.4);
ek400->GetYaxis()->SetRangeUser(0.,1.0);
ek400->Draw("E");
ck1->Print("CKFigures/momeffk.png");

TCanvas* ck2 = new TCanvas("Garana Charged Kaon Reco Efficiency vs. Drift Angle","Garana Charged Kaon Reco Efficiency vs. Drift Angle",1000,1000);
ck2->Divide(2,2);
ck2->cd(2);
TH2D* eka =(TH2D*) twoD_histos.at(7)->Clone("eka");
eka->Divide(twoD_histos.at(7),twoD_histos.at(6));
eka->SetTitle("Charged Kaon Angular Reconstruction Efficiency");
eka->GetXaxis()->SetTitle("Angle from Drift Direction");
eka->GetYaxis()->SetTitle("Angle about Drift Direction");
eka->GetZaxis()->SetRangeUser(0.,1.);
eka->Draw("col");

ck2->cd(1);
azim_histos.at(7)->Sumw2();
azim_histos.at(6)->Sumw2();
TH1D* ekazim=(TH1D*) azim_histos.at(7)->Clone("ekazim");
ekazim->Divide(azim_histos.at(7),azim_histos.at(6));
ekazim->SetTitle("Angle about Drift Direction Efficiency");
ekazim->Draw("E");

ck2->cd(4);
pola_histos.at(7)->Sumw2();
pola_histos.at(6)->Sumw2();
TH1D* ekpola=(TH1D*) krpola->Clone("ekpola");
ekpola->Divide(pola_histos.at(7),pola_histos.at(6));
ekpola->SetTitle("Angle from Drift Direction Efficiency");
ekpola->Draw("E");
ck2->Print("CKFigures/angeffck.png");

}
