R__ADD_LIBRARY_PATH(/dune/app/users/birwin/garana_local_build/localProducts_garana_v00_00_13_e20_prof/garana/v00_00_13/slf7.x86_64.e20.prof/lib)
R__LOAD_LIBRARY(libGaranaAccessors.so)
R__LOAD_LIBRARY(libGaranaUtility.so)
R__ADD_INCLUDE_PATH(/dune/app/users/birwin/garana_local_build/localProducts_garana_v00_00_13_e20_prof/garana/v00_00_13/include)

/* Macro: FS Proton Reco Resolution
 * Purpose 1: Compare the true momentum spectrum of FS particles to the reconstructed momentum spectrum
 * Purpose 2:*/

#include "garana/Accessors/TreeManager.h"
#include "garana/Utility/Backtracker.h"
#include <TH1F.h>
#include <iostream>
#include <math.h>
#include <TStyle.h>
#include "functions.h"

using namespace garana;

void Res()
{

gROOT->SetBatch(kTRUE);

string infile = "/dune/data/users/birwin/structuredtree_files/structuredtree_full.root";

TreeManager* treeman = new TreeManager(infile);
Backtracker* bt = new Backtracker(treeman);
GenTree* gen = treeman->GetGenTree();
G4Tree*  g4  = treeman->GetG4Tree();
RecoTree* reco = treeman->GetRecoTree();

vector<int> particle_types= {2212,13,211,321};


//Declare histograms for all particle types
//Proton
TH1F* ptp 	= new TH1F("ptp","True Proton Momentum",50,0.,3.);
TH1F* prp 	= new TH1F("prp","Reconstructed Momentum for Reconstructed Protons",50,0.,3.);

TH1F* ptpolar 	= new TH1F("ptpolar","True Angle wrt Drift Direction",10,0,M_PI);
TH1F* ptazim 	= new TH1F("ptazim","True Angle about Drift Direction",20,-M_PI,M_PI);
TH2F* pta 	= new TH2F("pta","True Proton Drift Angle",5,0,M_PI,10,-M_PI,M_PI);
TH1F* prpolar   = new TH1F("prpolar","Reco Angle wrt Drift Direction",10,0,M_PI);
TH1F* prazim    = new TH1F("prazim","Reco Angle about Drift Direction",20,-M_PI,M_PI);
TH2F* pra 	= new TH2F("pra","Reconstructed Proton Drift Angles",5,0,M_PI,10,-M_PI,M_PI);

TH2F* ppres 	= new TH2F("ppres","Momentum Resolution",30,0.,3.,30,0.,3.);
TH2F* ppreslow  = new TH2F("ppreslow","Low Momentum Resolution",30,0.,1.,30,0.,1.);

TH1F* pfpres	= new TH1F("pfpres","Fractional Momentum Resolution",110,-12.,2.);
TH1F* pfpreslow	= new TH1F("pfpreslow","Fractional Momentum Resolution for Low True P Protons",110,1.5,1.);
TH1F* pfpresmid = new TH1F("pfpresmid","Fractional Momentum Resolution for Mid True P Protons",20,1.5,1.);
TH1F* pfpreshigh= new TH1F("pfpreshigh","Fractional Momentum Resolution for High True P Protons",20,1.5,1.);

TH1F* papres	= new TH1F("papres","Absolute Difference Momentum Resolution",60,-3.,3.);
TH1F* papreslow = new TH1F("papreslow","Absolute Difference Momentum Resolution for Low True P Protons",60,-3.,3.);
TH1F* papresmid = new TH1F("papresmid","Absolute Difference Momentum Resolution for Mid True P Protons",60,-3.,3.);
TH1F* papreshigh= new TH1F("papreshigh","Absolute Difference Momentum Resolution for High True P Protons",60,-3.,3.);

TH1F* ppolarres	= new TH1F("ppolarres","Polar Resolution",40,-M_PI,M_PI);
TH1F* pazimres	= new TH1F("pazimres","Azimuthal Resolution",40,-2.*M_PI,2.*M_PI);
TH2F* pares	= new TH2F("pares","Angular Resolution",20,-M_PI,M_PI,20,-2.*M_PI,2.*M_PI);
TH2F* pres_tp	= new TH2F("pres_tp","Fractional Resolution vs True Momentum",20,0.3,3.,42,-20.,1.);
TH1F* pt_r_dot	= new TH1F("pt_r_dot","Dot Product between True and Reco Momentum",50,-1.,1.);
TH2F* pdotvf	= new TH2F("pdotvf","Dot Product vs Fractional Difference",20,1.5,1.,20,-1.,1.);
TH2F* pdotva    = new TH2F("pdotva","Dot Product vs Absolute Difference",20,-3.,3.,20,-1.,1.);

//Muons
TH1F* mtp       = new TH1F("mtp","True Muon Momentum",50,0.,3.);
TH1F* mrp       = new TH1F("mrp","Reconstructed Momentum for Reconstructed Muons",50,0.,3.);

TH1F* mtpolar   = new TH1F("mtpolar","True Angle wrt Drift Direction",10,0,M_PI);
TH1F* mtazim    = new TH1F("mtazim","True Angle about Drift Direction",20,-M_PI,M_PI);
TH2F* mta       = new TH2F("mta","True Muon Drift Angle",5,0,M_PI,10,-M_PI,M_PI);
TH1F* mrpolar   = new TH1F("mrpolar","Reco Angle wrt Drift Direction",10,0,M_PI);
TH1F* mrazim    = new TH1F("mrazim","Reco Angle about Drift Direction",20,-M_PI,M_PI);
TH2F* mra       = new TH2F("mra","Reconstructed Muon Drift Angles",5,0,M_PI,10,-M_PI,M_PI);

TH2F* mpres     = new TH2F("mpres","Momentum Resolution",30,0.,3.,30,0.,3.);
TH2F* mpreslow  = new TH2F("mpreslow","Low Momentum Resolution",30,0.,1.,30,0.,1.);

TH1F* mfpres    = new TH1F("mfpres","Fractional Momentum Resolution",110,-12.,2.);
TH1F* mfpreslow = new TH1F("mfpreslow","Fractional Momentum Resolution for Low True P Muons",110,1.5,1.);
TH1F* mfpresmid = new TH1F("mfpresmid","Fractional Momentum Resolution for Mid True P Muons",20,1.5,1.);
TH1F* mfpreshigh= new TH1F("mfpreshigh","Fractional Momentum Resolution for High True P Muons",20,1.5,1.);

TH1F* mapres    = new TH1F("mapres","Absolute Difference Momentum Resolution",60,-3.,3.);
TH1F* mapreslow = new TH1F("mapreslow","Absolute Difference Momentum Resolution for Low True P Muons",60,-3.,3.);
TH1F* mapresmid = new TH1F("mapresmid","Absolute Difference Momentum Resolution for Mid True P Muons",60,-3.,3.);
TH1F* mapreshigh= new TH1F("mapreshigh","Absolute Difference Momentum Resolution for High True P Muons",60,-3.,3.);

TH1F* mpolarres = new TH1F("mpolarres","Polar Resolution",40,-M_PI,M_PI);
TH1F* mazimres  = new TH1F("mazimres","Azimuthal Resolution",40,-2.*M_PI,2.*M_PI);
TH2F* mares     = new TH2F("mares","Angular Resolution",20,-M_PI,M_PI,20,-2.*M_PI,2.*M_PI);
TH2F* mres_tp   = new TH2F("mres_tp","Fractional Resolution vs True Momentum",20,0.3,3.,42,-20.,1.);
TH1F* mt_r_dot  = new TH1F("mt_r_dot","Dot Product between True and Reco Momentum",50,-1.,1.);
TH2F* mdotvf    = new TH2F("mdotvf","Dot Product vs Fractional Difference",20,1.5,1.,20,-1.,1.);
TH2F* mdotva    = new TH2F("mdotva","Dot Product vs Absolute Difference",20,-3.,3.,20,-1.,1.);

//Charged Pions
TH1F* cptp       = new TH1F("cptp","True Charged Pion Momentum",50,0.,3.);
TH1F* cprp       = new TH1F("cprp","Reconstructed Momentum for Reconstructed Charged Pions",50,0.,3.);

TH1F* cptpolar   = new TH1F("cptpolar","True Angle wrt Drift Direction",10,0,M_PI);
TH1F* cptazim    = new TH1F("cptazim","True Angle about Drift Direction",20,-M_PI,M_PI);
TH2F* cpta       = new TH2F("cpta","True Charged Pion Drift Angle",5,0,M_PI,10,-M_PI,M_PI);
TH1F* cprpolar   = new TH1F("cprpolar","Reco Angle wrt Drift Direction",10,0,M_PI);
TH1F* cprazim    = new TH1F("cprazim","Reco Angle about Drift Direction",20,-M_PI,M_PI);
TH2F* cpra       = new TH2F("cpra","Reconstructed Charged Pion Drift Angles",5,0,M_PI,10,-M_PI,M_PI);

TH2F* cppres     = new TH2F("cppres","Momentum Resolution",30,0.,3.,30,0.,3.);
TH2F* cppreslow  = new TH2F("cppreslow","Low Momentum Resolution",30,0.,1.,30,0.,1.);

TH1F* cpfpres    = new TH1F("cpfpres","Fractional Momentum Resolution",110,-12.,2.);
TH1F* cpfpreslow = new TH1F("cpfpreslow","Fractional Momentum Resolution for Low True Charged Pions",110,1.5,1.);
TH1F* cpfpresmid = new TH1F("cpfpresmid","Fractional Momentum Resolution for Mid True P Charged Pions",20,1.5,1.);
TH1F* cpfpreshigh= new TH1F("cpfpreshigh","Fractional Momentum Resolution for High True P Charged Pions",20,1.5,1.);

TH1F* cpapres    = new TH1F("cpapres","Absolute Difference Momentum Resolution",60,-3.,3.);
TH1F* cpapreslow = new TH1F("cpapreslow","Absolute Difference Momentum Resolution for Low True P Charged Pions",60,-3.,3.);
TH1F* cpapresmid = new TH1F("cpapresmid","Absolute Difference Momentum Resolution for Mid True P Charged Pions",60,-3.,3.);
TH1F* cpapreshigh= new TH1F("cpapreshigh","Absolute Difference Momentum Resolution for High True P Charged Pions",60,-3.,3.);

TH1F* cppolarres = new TH1F("cppolarres","Polar Resolution",40,-M_PI,M_PI);
TH1F* cpazimres  = new TH1F("cpazimres","Azimuthal Resolution",40,-2.*M_PI,2.*M_PI);
TH2F* cpares     = new TH2F("cpares","Angular Resolution",20,-M_PI,M_PI,20,-2.*M_PI,2.*M_PI);
TH2F* cpres_tp   = new TH2F("cpres_tp","Fractional Resolution vs True Momentum",20,0.3,3.,42,-20.,1.);
TH1F* cpt_r_dot  = new TH1F("cpt_r_dot","Dot Product between True and Reco Momentum",50,-1.,1.);
TH2F* cpdotvf    = new TH2F("cpdotvf","Dot Product vs Fractional Difference",20,1.5,1.,20,-1.,1.);
TH2F* cpdotva    = new TH2F("cpdotva","Dot Product vs Absolute Difference",20,-3.,3.,20,-1.,1.);

//Charged Kaons
TH1F* ktp       = new TH1F("ktp","True Charged Kaon Momentum",50,0.,3.);
TH1F* krp       = new TH1F("krp","Reconstructed Momentum for Reconstructed Charged Kaons",50,0.,3.);

TH1F* ktpolar   = new TH1F("ktpolar","True Angle wrt Drift Direction",10,0,M_PI);
TH1F* ktazim    = new TH1F("ktazim","True Angle about Drift Direction",20,-M_PI,M_PI);
TH2F* kta       = new TH2F("kta","True Charged Kaon Drift Angle",5,0,M_PI,10,-M_PI,M_PI);
TH1F* krpolar   = new TH1F("krpolar","Reco Angle wrt Drift Direction",10,0,M_PI);
TH1F* krazim    = new TH1F("krazim","Reco Angle about Drift Direction",20,-M_PI,M_PI);
TH2F* kra       = new TH2F("kra","Reconstructed Charged Kaon Drift Angles",5,0,M_PI,10,-M_PI,M_PI);

TH2F* kpres     = new TH2F("kpres","Momentum Resolution",30,0.,3.,30,0.,3.);
TH2F* kpreslow  = new TH2F("kpreslow","Low Momentum Resolution",30,0.,1.,30,0.,1.);

TH1F* kfpres    = new TH1F("kfpres","Fractional Momentum Resolution",110,-12.,2.);
TH1F* kfpreslow = new TH1F("kfpreslow","Fractional Momentum Resolution for Low True P Charged Kaons",110,1.5,1.);
TH1F* kfpresmid = new TH1F("kfpresmid","Fractional Momentum Resolution for Mid True P Charged Kaons",20,1.5,1.);
TH1F* kfpreshigh= new TH1F("kfpreshigh","Fractional Momentum Resolution for High True P Charged Kaons",20,1.5,1.);

TH1F* kapres    = new TH1F("kapres","Absolute Difference Momentum Resolution",60,-3.,3.);
TH1F* kapreslow = new TH1F("kapreslow","Absolute Difference Momentum Resolution for Low True P Charged Kaons",60,-3.,3.);
TH1F* kapresmid = new TH1F("kapresmid","Absolute Difference Momentum Resolution for Mid True P Charged Kaons",60,-3.,3.);
TH1F* kapreshigh= new TH1F("kapreshigh","Absolute Difference Momentum Resolution for High True P Charged Kaons",60,-3.,3.);

TH1F* kpolarres = new TH1F("kpolarres","Polar Resolution",40,-M_PI,M_PI);
TH1F* kazimres  = new TH1F("kazimres","Azimuthal Resolution",40,-2.*M_PI,2.*M_PI);
TH2F* kares     = new TH2F("kares","Angular Resolution",20,-M_PI,M_PI,20,-2.*M_PI,2.*M_PI);
TH1F* kt_r_dot  = new TH1F("kt_r_dot","Dot Product between True and Reco Momentum",50,-1.,1.);
TH2F* kdotvf    = new TH2F("kdotvf","Dot Product vs Fractional Difference",20,1.5,1.,20,-1.,1.);
TH2F* kdotva    = new TH2F("kdotva","Dot Product vs Absolute Difference",20,-3.,3.,20,-1.,1.);

vector<TH1F*> pola_histos = {ptpolar,prpolar,mtpolar,mrpolar,cptpolar,cprpolar,ktpolar,krpolar};
vector<TH1F*> azim_histos = {ptazim,prazim,mtazim,mrazim,cptazim,cprazim,ktazim,krazim};
vector<TH2F*> drifthistos = {pta,pra,mta,mra,cpta,cpra,kta,kra};

vector<TH1F*> oneD_histos = {ptp,prp,ppolarres,pazimres,mtp,mrp,mpolarres,mazimres,cptp,cprp,cppolarres,cpazimres,ktp,krp,kpolarres,kazimres};

vector<TH1F*> abs_histos  = {papres,papreslow,papresmid,papreshigh,mapres,mapreslow,mapresmid,mapreshigh,cpapres,cpapreslow,cpapresmid,cpapreshigh,kapres,kapreslow,kapresmid,kapreshigh};
vector<TH1F*> frac_histos = {pfpres,pfpreslow,pfpresmid,pfpreshigh,mfpres,mfpreslow,mfpresmid,mfpreshigh,cpfpres,cpfpreslow,cpfpresmid,cpfpreshigh,kfpres,kfpreslow,kfpresmid,kfpreshigh};

vector<TH2F*> res_2Dhistos= {ppres,ppreslow,pares,mpres,mpreslow,mares,cppres,cppreslow,cpares,kpres,kpreslow,kares};

vector<TH1F*> dot_1Dhistos= {pt_r_dot,mt_r_dot,cpt_r_dot,kt_r_dot};
vector<TH2F*> dot_2Dhistos= {pdotvf,pdotva,mdotvf,mdotva,cpdotvf,cpdotva,kdotvf,kdotva};

int protoncount = 0;
int muoncount = 0;
int chargedpioncount = 0;
int chargedkaoncount = 0;
vector<int> counts = {protoncount,muoncount,chargedpioncount,chargedkaoncount};
for(UInt_t ipdg = 0; ipdg<particle_types.size(); ipdg++)
{
	for(UInt_t ientry=0; ientry<100000; ientry++)//treeman->NEntries(); ientry++)		//Loop through all events
		{
		if(ientry%1000==0)
		{
			std::cout<<"Event: "<<ientry<<std::endl;
		}
		treeman->GetEntry(ientry);
		bt->FillMaps();
		for(UInt_t ig4p=0; ig4p<g4->NSim(); ig4p++)			//Loop through true particles
			{
			if(g4->IsPrimary(ig4p) && g4->PDG(ig4p) == particle_types.at(ipdg))
				{
					auto truth_angles = Truth_Direction(g4,ig4p);
					int association = 0;
					pair<int,float> Responsible_track;
					if(-220.<gen->NuVertex(bt->G4ParticleToGTruth(ig4p))->X()<220. && sqrt(pow(gen->NuVertex(bt->G4ParticleToGTruth(ig4p))->Y(),2)+pow(gen->NuVertex(bt->G4ParticleToGTruth(ig4p))->Z(),2))<210.) //Fiducial Volume Cut
					{
						counts.at(ipdg)++;
						oneD_histos.at(4*ipdg)->Fill(g4->SimMomEnter(ig4p,0)->P());
						pola_histos.at(2*ipdg)->Fill(truth_angles.first);
						azim_histos.at(2*ipdg)->Fill(truth_angles.second);
						drifthistos.at(2*ipdg)->Fill(truth_angles.first,truth_angles.second);	
						for(UInt_t itrk=0; itrk<reco->NTrack(); itrk++)	//Loop through reconstructed tracks
						{
							auto PrimeParticle = bt->TrackToG4ParticleDeposit(itrk);
							if(ig4p==PrimeParticle.first)
							{
								association += 1;
								if(PrimeParticle.second>Responsible_track.second) //Find the track that the proton gave the most energy to
                                                                {
                                                                        Responsible_track = make_pair(itrk,PrimeParticle.second);
                                                                }
							}	
						}
					}
				const vector<UInt_t>* list_of_vertices = bt->TrackToVertices(Responsible_track.first);
				if(association != 0 && list_of_vertices->size()>0) //Fill Reco Histos
				{
					double true_p = g4->SimMomEnter(ig4p,0)->P();
					double fromBeg = sqrt(pow(reco->TrackMomBeg(Responsible_track.first)->X()-gen->NuVertex(bt->TrackToGTruth(Responsible_track.first))->X(),2) + pow(reco->TrackMomBeg(Responsible_track.first)->Y()-gen->NuVertex(bt->TrackToGTruth(Responsible_track.first))->Y(),2) + pow(reco->TrackMomBeg(Responsible_track.first)->X()-gen->NuVertex(bt->TrackToGTruth(Responsible_track.first))->X(),2));
					double fromEnd = sqrt(pow(reco->TrackMomEnd(Responsible_track.first)->X()-gen->NuVertex(bt->TrackToGTruth(Responsible_track.first))->X(),2) + pow(reco->TrackMomEnd(Responsible_track.first)->Y()-gen->NuVertex(bt->TrackToGTruth(Responsible_track.first))->Y(),2) + pow(reco->TrackMomEnd(Responsible_track.first)->X()-gen->NuVertex(bt->TrackToGTruth(Responsible_track.first))->X(),2));
					double reco_p = 0;
					if(fromBeg<fromEnd)
        				{
						reco_p = reco->TrackMomBeg(Responsible_track.first)->Mag();
        				}
        				else
        				{
						reco_p = reco->TrackMomEnd(Responsible_track.first)->Mag();
        				}
					double aprespoint = true_p - reco_p;
					double fprespoint = (true_p-reco_p)/true_p;
					if(Responsible_track.second>0 && reco_p!=0)
					{
						auto reco_angles = Reco_Direction(reco,Responsible_track.first,fromBeg,fromEnd);
						res_2Dhistos.at(3*ipdg)->Fill(true_p,reco_p);
						if(true_p<1.)
						{
							 res_2Dhistos.at(3*ipdg+1)->Fill(true_p,reco_p);
						}
						if(true_p>.3)
						{
							frac_histos.at(4*ipdg)->Fill(fprespoint);
							abs_histos.at(4*ipdg)->Fill(aprespoint);
							double dotprod = true_reco_unitdot(g4,ig4p,reco,Responsible_track.first,fromBeg,fromEnd);
							if(true_p<1.)
							{
								abs_histos.at(4*ipdg+1)->Fill(aprespoint);
								frac_histos.at(4*ipdg+1)->Fill(fprespoint);
							}
							if(1.<=true_p && true_p<3.)
							{
								abs_histos.at(4*ipdg+2)->Fill(aprespoint);
								frac_histos.at(4*ipdg+2)->Fill(fprespoint);
							}
							if(true_p>=3.)
							{
								abs_histos.at(4*ipdg+3)->Fill(aprespoint);
								frac_histos.at(4*ipdg+3)->Fill(fprespoint);
							}
							oneD_histos.at(4*ipdg+1)->Fill(reco_p);
							pola_histos.at(2*ipdg+1)->Fill(reco_angles.first);
							azim_histos.at(2*ipdg+1)->Fill(reco_angles.second);
							drifthistos.at(2*ipdg+1)->Fill(reco_angles.first,reco_angles.second);
							oneD_histos.at(4*ipdg+2)->Fill(truth_angles.first-reco_angles.first);
							oneD_histos.at(4*ipdg+3)->Fill(truth_angles.second-reco_angles.second);
							res_2Dhistos.at(3*ipdg+2)->Fill(truth_angles.first-reco_angles.first,truth_angles.second-reco_angles.second);
							dot_1Dhistos.at(ipdg)->Fill(dotprod);
							dot_2Dhistos.at(2*ipdg)->Fill(fprespoint,dotprod);
							dot_2Dhistos.at(2*ipdg+1)->Fill(aprespoint,dotprod);
						}
					}
				}
				}
			}	
		}
}

for(int i =0; i<counts.size(); i++)
{
std::cout<<"=================\n"<<counts.at(i)<<std::endl;
}
gStyle->SetOptStat(0);

//Protons
TCanvas* c1a = new TCanvas("c1a","Momentum Resolution",1500,750);
c1a->Divide(2,1);
c1a->cd(1);
res_2Dhistos.at(0)->SetTitle("Proton Momentum Resolution");
res_2Dhistos.at(0)->GetXaxis()->SetTitle("True Momentum (GeV)");
res_2Dhistos.at(0)->GetYaxis()->SetTitle("Reconstructed Momentum (GeV)");
res_2Dhistos.at(0)->Draw("col");
c1a->cd(2);
res_2Dhistos.at(1)->GetXaxis()->SetTitle("True Momentum (GeV)");
res_2Dhistos.at(1)->GetYaxis()->SetTitle("Reconstructed Momentum (GeV)");
res_2Dhistos.at(1)->Draw("col");
c1a->Print("ProtonFigures/MomResCanvas.png");

TCanvas* c1b = new TCanvas("c1b","Fractional Momentum Resolution",2000,2000);
c1b->Divide(2,2);
c1b->cd(1);
frac_histos.at(0)->SetTitle("Proton p_{true}#minus^{} p_{reco}/p_{true}");
frac_histos.at(0)->Sumw2();
frac_histos.at(0)->Draw();
c1b->cd(2);
frac_histos.at(1)->SetTitle("p_{true}#minus^{} p_{reco}/p_{true} [300 MeV - 1 GeV)");
frac_histos.at(1)->Sumw2();
frac_histos.at(1)->Draw();
c1b->cd(3);
frac_histos.at(2)->SetTitle("p_{true}#minus^{} p_{reco}/p_{true} [1 GeV - 3 GeV)");
frac_histos.at(2)->Sumw2();
frac_histos.at(2)->Draw();
c1b->cd(4);
frac_histos.at(3)->SetTitle("p_{true}#minus^{} p_{reco}/p_{true} [3 GeV - Max)");
frac_histos.at(3)->Sumw2();
frac_histos.at(3)->Draw();
c1b->Print("ProtonFigures/FracMomResCanvas.png");

TCanvas* c1c = new TCanvas("c1c","Absolute Difference Momentum Resolution",2000,2000);
c1c->Divide(2,2);
c1c->cd(1);
abs_histos.at(0)->SetTitle("Proton p_{true}#minus^{} p_{reco}");
abs_histos.at(0)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(0)->Sumw2();
abs_histos.at(0)->Draw();
c1c->cd(2);
abs_histos.at(1)->SetTitle("p_{true}#minus^{} p_{reco} [300 MeV - 1 GeV)");
abs_histos.at(1)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(1)->Sumw2();
abs_histos.at(1)->Draw();
c1c->cd(3);
abs_histos.at(2)->SetTitle("p_{true}#minus^{} p_{reco} [1 GeV - 3 GeV)");
abs_histos.at(2)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(2)->Sumw2();
abs_histos.at(2)->Draw();
c1c->cd(4);
abs_histos.at(3)->SetTitle("p_{true}#minus^{} p_{reco} [3 GeV - Max)");
abs_histos.at(3)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(3)->Sumw2();
abs_histos.at(3)->Draw();
c1c->Print("ProtonFigures/AbsMomResCanvas.png");

TCanvas* c2 = new TCanvas("c2","Angular Plots",1500,1500);
c2->Divide(2,2);
oneD_histos.at(2)->SetTitle("Angle from Drift Resolution");
oneD_histos.at(3)->SetTitle("Angle about Drift Resolution");
res_2Dhistos.at(2)->SetTitle("Proton Total Angular Resolution");
c2->cd(1);
oneD_histos.at(3)->Sumw2();
oneD_histos.at(3)->GetXaxis()->SetTitle("#phi_{true}#minus^{}#phi_{reco}");
oneD_histos.at(3)->Draw("E");
c2->cd(2);
res_2Dhistos.at(2)->GetXaxis()->SetTitle("#theta_{true}#minus^{}#theta_{reco}");
res_2Dhistos.at(2)->GetYaxis()->SetTitle("#phi_{true}#minus^{}#phi_{reco}");
res_2Dhistos.at(2)->Draw("col");
c2->cd(3);
dot_1Dhistos.at(0)->GetXaxis()->SetTitle("p_{true} #bullet p_{reco}");
dot_1Dhistos.at(0)->Draw();
c2->cd(4);
oneD_histos.at(2)->Sumw2();
oneD_histos.at(2)->GetXaxis()->SetTitle("#theta_{true}#minus^{}#theta_{reco}");
oneD_histos.at(2)->Draw("E");
c2->Print("ProtonFigures/AngResCanvas.png");

TCanvas* c3 = new TCanvas("c3","Dot Product vs True Momentum",1500,750);
c3->Divide(2,1);
c3->cd(1);
dot_2Dhistos.at(0)->SetTitle("Proton Fractional Difference");
dot_2Dhistos.at(0)->GetXaxis()->SetTitle("Fractional Difference");
dot_2Dhistos.at(0)->GetYaxis()->SetTitle("p_{true} #bullet p_{reco}");
dot_2Dhistos.at(0)->Draw("col");
c3->cd(2);
dot_2Dhistos.at(1)->SetTitle("Proton Absolute Difference");
dot_2Dhistos.at(1)->GetXaxis()->SetTitle("Absolute Difference");
dot_2Dhistos.at(1)->GetYaxis()->SetTitle("p_{true} #bullet p_{reco}");
dot_2Dhistos.at(1)->Draw("col");
c3->Print("ProtonFigures/DotvTruep.png");

//Muons
TCanvas* m1a = new TCanvas("m1a","Momentum Resolution",1500,750);
m1a->Divide(2,1);
m1a->cd(1);
res_2Dhistos.at(3)->SetTitle("Muon Momentum Resolution");
res_2Dhistos.at(3)->GetXaxis()->SetTitle("True Momentum (GeV)");
res_2Dhistos.at(3)->GetYaxis()->SetTitle("Reconstructed Momentum (GeV)");
res_2Dhistos.at(3)->Draw("col");
m1a->cd(2);
res_2Dhistos.at(4)->GetXaxis()->SetTitle("True Momentum (GeV)");
res_2Dhistos.at(4)->GetYaxis()->SetTitle("Reconstructed Momentum (GeV)");
res_2Dhistos.at(4)->Draw("col");

m1a->Print("MuonFigures/MomResCanvas.png");

TCanvas* m1b = new TCanvas("m1b","Fractional Momentum Resolution",2000,2000);
m1b->Divide(2,2);
m1b->cd(1);
frac_histos.at(4)->SetTitle("Muon p_{true}#minus^{} p_{reco}/p_{true}");
frac_histos.at(4)->Sumw2();
frac_histos.at(4)->Draw();
m1b->cd(2);
frac_histos.at(5)->SetTitle("p_{true}#minus^{} p_{reco}/p_{true} [300 MeV - 1 GeV)");
frac_histos.at(5)->Sumw2();
frac_histos.at(5)->Draw();
m1b->cd(3);
frac_histos.at(6)->SetTitle("p_{true}#minus^{} p_{reco}/p_{true} [1 GeV - 3 GeV)");
frac_histos.at(6)->Sumw2();
frac_histos.at(6)->Draw();
m1b->cd(4);
frac_histos.at(7)->SetTitle("p_{true}#minus^{} p_{reco}/p_{true} [3 GeV - Max)");
frac_histos.at(7)->Sumw2();
frac_histos.at(7)->Draw();

m1b->Print("MuonFigures/FracMomResCanvas.png");

TCanvas* m1c = new TCanvas("m1c","Absolute Difference Momentum Resolution",2000,2000);
m1c->Divide(2,2);
m1c->cd(1);
abs_histos.at(4)->SetTitle("Muon p_{true}#minus^{} p_{reco}");
abs_histos.at(4)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(4)->Sumw2();
abs_histos.at(4)->Draw();
m1c->cd(2);
abs_histos.at(5)->SetTitle("p_{true}#minus^{} p_{reco} [300 MeV - 1 GeV)");
abs_histos.at(5)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(5)->Sumw2();
abs_histos.at(5)->Draw();
m1c->cd(3);
abs_histos.at(6)->SetTitle("p_{true}#minus^{} p_{reco} [1 GeV - 3 GeV)");
abs_histos.at(6)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(6)->Sumw2();
abs_histos.at(6)->Draw();
m1c->cd(4);
abs_histos.at(7)->SetTitle("p_{true}#minus^{} p_{reco} [3 GeV - Max)");
abs_histos.at(7)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(7)->Sumw2();
abs_histos.at(7)->Draw();

m1c->Print("MuonFigures/AbsMomResCanvas.png");

TCanvas* m2 = new TCanvas("m2","Angular Plots",1500,1500);
m2->Divide(2,2);
oneD_histos.at(6)->SetTitle("Angle from Drift Resolution");
oneD_histos.at(7)->SetTitle("Angle about Drift Resolution");
res_2Dhistos.at(5)->SetTitle("Muon Total Angular Resolution");
m2->cd(1);
oneD_histos.at(7)->Sumw2();
oneD_histos.at(7)->GetXaxis()->SetTitle("#phi_{true}#minus^{}#phi_{reco}");
oneD_histos.at(7)->Draw("E");
m2->cd(2);
res_2Dhistos.at(5)->GetXaxis()->SetTitle("#theta_{true}#minus^{}#theta_{reco}");
res_2Dhistos.at(5)->GetYaxis()->SetTitle("#phi_{true}#minus^{}#phi_{reco}");
res_2Dhistos.at(5)->Draw("col");
m2->cd(3);
dot_1Dhistos.at(1)->GetXaxis()->SetTitle("p_{true} #bullet p_{reco}");
dot_1Dhistos.at(1)->Draw();
m2->cd(4);
oneD_histos.at(6)->Sumw2();
oneD_histos.at(6)->GetXaxis()->SetTitle("#theta_{true}#minus^{}#theta_{reco}");
oneD_histos.at(6)->Draw("E");

m2->Print("MuonFigures/AngResCanvas.png");

TCanvas* m3 = new TCanvas("m3","Muon Dot Product vs True Momentum",1500,750);
m3->Divide(2,1);
m3->cd(1);
dot_2Dhistos.at(2)->SetTitle("Muon Fractional Difference");
dot_2Dhistos.at(2)->GetXaxis()->SetTitle("Fractional Difference");
dot_2Dhistos.at(2)->GetYaxis()->SetTitle("p_{true} #bullet p_{reco}");
dot_2Dhistos.at(2)->Draw("col");
m3->cd(2);
dot_2Dhistos.at(3)->SetTitle("Muon Absolute Difference");
dot_2Dhistos.at(3)->GetXaxis()->SetTitle("Absolute Difference");
dot_2Dhistos.at(3)->GetYaxis()->SetTitle("p_{true} #bullet p_{reco}");
dot_2Dhistos.at(3)->Draw("col");

m3->Print("MuonFigures/DotvTruep.png");

//Charged Pions
TCanvas* cp1a = new TCanvas("cp1a","Momentum Resolution",1500,750);
cp1a->Divide(2,1);
cp1a->cd(1);
res_2Dhistos.at(6)->SetTitle("Charged Pion Momentum Resolution");
res_2Dhistos.at(6)->GetXaxis()->SetTitle("True Momentum (GeV)");
res_2Dhistos.at(6)->GetYaxis()->SetTitle("Reconstructed Momentum (GeV)");
res_2Dhistos.at(6)->Draw("col");
cp1a->cd(2);
res_2Dhistos.at(7)->GetXaxis()->SetTitle("True Momentum (GeV)");
res_2Dhistos.at(7)->GetYaxis()->SetTitle("Reconstructed Momentum (GeV)");
res_2Dhistos.at(7)->Draw("col");
cp1a->Print("CPFigures/MomResCanvas.png");

TCanvas* cp1b = new TCanvas("cp1b","Fractional Momentum Resolution",2000,2000);
cp1b->Divide(2,2);
cp1b->cd(1);
frac_histos.at(8)->SetTitle("Charged Pion p_{true}#minus^{} p_{reco}/p_{true}");
frac_histos.at(8)->Sumw2();
frac_histos.at(8)->Draw();
cp1b->cd(2);
frac_histos.at(9)->SetTitle("p_{true}#minus^{} p_{reco}/p_{true} [300 MeV - 1 GeV)");
frac_histos.at(9)->Sumw2();
frac_histos.at(9)->Draw();
cp1b->cd(3);
frac_histos.at(10)->SetTitle("p_{true}#minus^{} p_{reco}/p_{true} [1 GeV - 3 GeV)");
frac_histos.at(10)->Sumw2();
frac_histos.at(10)->Draw();
cp1b->cd(4);
frac_histos.at(11)->SetTitle("p_{true}#minus^{} p_{reco}/p_{true} [3 GeV - Max)");
frac_histos.at(11)->Sumw2();
frac_histos.at(11)->Draw();
cp1b->Print("CPFigures/FracMomResCanvas.png");

TCanvas* cp1c = new TCanvas("cp1c","Absolute Difference Momentum Resolution",2000,2000);
cp1c->Divide(2,2);
cp1c->cd(1);
abs_histos.at(8)->SetTitle("Charged Pion p_{true}#minus^{} p_{reco}");
abs_histos.at(8)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(8)->Sumw2();
abs_histos.at(8)->Draw();
cp1c->cd(2);
abs_histos.at(9)->SetTitle("p_{true}#minus^{} p_{reco} [300 MeV - 1 GeV)");
abs_histos.at(9)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(9)->Sumw2();
abs_histos.at(9)->Draw();
cp1c->cd(3);
abs_histos.at(10)->SetTitle("p_{true}#minus^{} p_{reco} [1 GeV - 3 GeV)");
abs_histos.at(10)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(10)->Sumw2();
abs_histos.at(10)->Draw();
cp1c->cd(4);
abs_histos.at(11)->SetTitle("p_{true}#minus^{} p_{reco} [3 GeV - Max)");
abs_histos.at(11)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(11)->Sumw2();
abs_histos.at(11)->Draw();
cp1c->Print("CPFigures/AbsMomResCanvas.png");

TCanvas* cp2 = new TCanvas("cp2","Angular Plots",1500,1500);
cp2->Divide(2,2);
oneD_histos.at(10)->SetTitle("Angle from Drift Resolution");
oneD_histos.at(11)->SetTitle("Angle about Drift Resolution");
res_2Dhistos.at(8)->SetTitle("Charged Pion Total Angular Resolution");
cp2->cd(1);
oneD_histos.at(11)->Sumw2();
oneD_histos.at(11)->GetXaxis()->SetTitle("#phi_{true}#minus^{}#phi_{reco}");
oneD_histos.at(11)->Draw("E");
cp2->cd(2);
res_2Dhistos.at(8)->GetXaxis()->SetTitle("#theta_{true}#minus^{}#theta_{reco}");
res_2Dhistos.at(8)->GetYaxis()->SetTitle("#phi_{true}#minus^{}#phi_{reco}");
res_2Dhistos.at(8)->Draw("col");
cp2->cd(3);
dot_1Dhistos.at(2)->GetXaxis()->SetTitle("p_{true} #bullet p_{reco}");
dot_1Dhistos.at(2)->Draw();
cp2->cd(4);
oneD_histos.at(10)->Sumw2();
oneD_histos.at(10)->GetXaxis()->SetTitle("#theta_{true}#minus^{}#theta_{reco}");
oneD_histos.at(10)->Draw("E");
cp2->Print("CPFigures/AngResCanvas.png");

TCanvas* cp3 = new TCanvas("cp3","Dot Product vs True Momentum",1500,750);
cp3->Divide(2,1);
cp3->cd(1);
dot_2Dhistos.at(4)->SetTitle("Charged Pion Fractional Difference");
dot_2Dhistos.at(4)->GetXaxis()->SetTitle("Fractional Difference");
dot_2Dhistos.at(4)->GetYaxis()->SetTitle("p_{true} #bullet p_{reco}");
dot_2Dhistos.at(4)->Draw("col");
cp3->cd(2);
dot_2Dhistos.at(5)->SetTitle("Charged Pion Absolute Difference");
dot_2Dhistos.at(5)->GetXaxis()->SetTitle("Absolute Difference");
dot_2Dhistos.at(5)->GetYaxis()->SetTitle("p_{true} #bullet p_{reco}");
dot_2Dhistos.at(5)->Draw("col");
cp3->Print("CPFigures/DotvTruep.png");

//Charged Kaons
TCanvas* k1a = new TCanvas("k1a","Momentum Resolution",1500,750);
k1a->Divide(2,1);
k1a->cd(1);
res_2Dhistos.at(9)->GetXaxis()->SetTitle("True Momentum (GeV)");
res_2Dhistos.at(9)->GetYaxis()->SetTitle("Reconstructed Momentum (GeV)");
res_2Dhistos.at(9)->Draw("col");
k1a->cd(2);
res_2Dhistos.at(10)->GetXaxis()->SetTitle("True Momentum (GeV)");
res_2Dhistos.at(10)->GetYaxis()->SetTitle("Reconstructed Momentum (GeV)");
res_2Dhistos.at(10)->Draw("col");
k1a->Print("CKFigures/MomResCanvas.png");

TCanvas* k1b = new TCanvas("k1b","Fractional Momentum Resolution",2000,2000);
k1b->Divide(2,2);
k1b->cd(1);
frac_histos.at(12)->SetTitle("p_{true}#minus^{} p_{reco}/p_{true}");
frac_histos.at(12)->Sumw2();
frac_histos.at(12)->Draw();
k1b->cd(2);
frac_histos.at(13)->SetTitle("p_{true}#minus^{} p_{reco}/p_{true} [300 MeV - 1 GeV)");
frac_histos.at(13)->Sumw2();
frac_histos.at(13)->Draw();
k1b->cd(3);
frac_histos.at(14)->SetTitle("p_{true}#minus^{} p_{reco}/p_{true} [1 GeV - 3 GeV)");
frac_histos.at(14)->Sumw2();
frac_histos.at(14)->Draw();
k1b->cd(4);
frac_histos.at(15)->SetTitle("p_{true}#minus^{} p_{reco}/p_{true} [3 GeV - Max)");
frac_histos.at(15)->Sumw2();
frac_histos.at(15)->Draw();
k1b->Print("CKFigures/FracMomResCanvas.png");

TCanvas* k1c = new TCanvas("k1c","Absolute Difference Momentum Resolution",2000,2000);
k1c->Divide(2,2);
k1c->cd(1);
abs_histos.at(12)->SetTitle("p_{true}#minus^{} p_{reco}");
abs_histos.at(12)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(12)->Sumw2();
abs_histos.at(12)->Draw();
k1c->cd(2);
abs_histos.at(13)->SetTitle("p_{true}#minus^{} p_{reco} [300 MeV - 1 GeV)");
abs_histos.at(13)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(13)->Sumw2();
abs_histos.at(13)->Draw();
k1c->cd(3);
abs_histos.at(14)->SetTitle("p_{true}#minus^{} p_{reco} [1 GeV - 3 GeV)");
abs_histos.at(14)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(14)->Sumw2();
abs_histos.at(14)->Draw();
k1c->cd(4);
abs_histos.at(15)->SetTitle("p_{true}#minus^{} p_{reco} [3 GeV - Max)");
abs_histos.at(15)->GetXaxis()->SetTitle("Difference in p (GeV)");
abs_histos.at(15)->Sumw2();
abs_histos.at(15)->Draw();
k1c->Print("CKFigures/AbsMomResCanvas.png");

TCanvas* k2 = new TCanvas("k2","Angular Plots",1500,1500);
k2->Divide(2,2);
oneD_histos.at(14)->SetTitle("Angle from Drift Resolution");
oneD_histos.at(15)->SetTitle("Angle about Drift Resolution");
res_2Dhistos.at(11)->SetTitle("Total Angular Resolution");
k2->cd(1);
oneD_histos.at(15)->Sumw2();
oneD_histos.at(15)->GetXaxis()->SetTitle("#phi_{true}#minus^{}#phi_{reco}");
oneD_histos.at(15)->Draw("E");
k2->cd(2);
res_2Dhistos.at(11)->GetXaxis()->SetTitle("#theta_{true}#minus^{}#theta_{reco}");
res_2Dhistos.at(11)->GetYaxis()->SetTitle("#phi_{true}#minus^{}#phi_{reco}");
res_2Dhistos.at(11)->Draw("col");
k2->cd(3);
dot_1Dhistos.at(3)->GetXaxis()->SetTitle("p_{true} #bullet p_{reco}");
dot_1Dhistos.at(3)->Draw();
k2->cd(4);
oneD_histos.at(14)->Sumw2();
oneD_histos.at(14)->GetXaxis()->SetTitle("#theta_{true}#minus^{}#theta_{reco}");
oneD_histos.at(14)->Draw("E");
k2->Print("CKFigures/AngResCanvas.png");

TCanvas* k3 = new TCanvas("k3","Dot Product vs True Momentum",1500,750);
k3->Divide(2,1);
k3->cd(1);
dot_2Dhistos.at(6)->SetTitle("Charged Kaon Fractional Difference");
dot_2Dhistos.at(6)->GetXaxis()->SetTitle("Fractional Difference");
dot_2Dhistos.at(6)->GetYaxis()->SetTitle("p_{true} #bullet p_{reco}");
dot_2Dhistos.at(6)->Draw("col");
k3->cd(2);
dot_2Dhistos.at(7)->SetTitle("Chraged Kaon Absolute Difference");
dot_2Dhistos.at(7)->GetXaxis()->SetTitle("Absolute Difference");
dot_2Dhistos.at(7)->GetYaxis()->SetTitle("p_{true} #bullet p_{reco}");
dot_2Dhistos.at(7)->Draw("col");
k3->Print("CKFigures/DotvTruep.png");

}
