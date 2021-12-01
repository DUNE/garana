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

void ResDev()
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

const char *titles[24]    = {"Proton Momentum Resolution","Proton p_{true}#minus^{} p_{reco}/p_{true}","Proton p_{true}#minus^{} p_{reco}","Proton Total Angular Resolution","Proton Fractional Difference","Proton Absolute Difference","Muon Momentum Resolution","Muon p_{true}#minus^{} p_{reco}/p_{true}","Muon p_{true}#minus^{} p_{reco}","Muon Total Angular Resolution","Muon Fractional Difference","Muon Absolute Difference","Charged Pion Momentum Resolution","Charged Pion p_{true}#minus^{} p_{reco}/p_{true}","Charged Pion p_{true}#minus^{} p_{reco}","Charged Pion Total Angular Resolution","Charged Pion Fractional Difference","Charged Pion Absolute Difference","Charged Kaon Momentum Resolution","Charged Kaon p_{true}#minus^{} p_{reco}/p_{true}","Charged Kaon p_{true}#minus^{} p_{reco}","Charged Kaon Total Angular Resolution","Charged Kaon Fractional Difference","Charged Kaon Absolute Difference"};
const char *saves[20]     = {"ProtonFigures/MomResCanvas.png","ProtonFigures/FracMomResCanvas.png","ProtonFigures/AbsMomResCanvas.png","ProtonFigures/AngResCanvas.png","ProtonFigures/DotvTruep.png","MuonFigures/MomResCanvas.png","MuonFigures/FracMomResCanvas.png","MuonFigures/AbsMomResCanvas.png","MuonFigures/AngResCanvas.png","MuonFigures/DotvTruep.png","CPFigures/MomResCanvas.png","CPFigures/FracMomResCanvas.png","CPFigures/AbsMomResCanvas.png","CPFigures/AngResCanvas.png","CPFigures/DotvTruep.png","CKFigures/MomResCanvas.png","CKFigures/FracMomResCanvas.png","CKFigures/AbsMomResCanvas.png","CKFigures/AngResCanvas.png","CKFigures/DotvTruep.png"};

int protoncount = 0;
int muoncount = 0;
int chargedpioncount = 0;
int chargedkaoncount = 0;
vector<int> counts = {protoncount,muoncount,chargedpioncount,chargedkaoncount};
for(UInt_t ipdg = 0; ipdg<particle_types.size(); ipdg++)
{
	for(UInt_t ientry=0; ientry<treeman->NEntries(); ientry++)		//Loop through all events
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
				//const vector<UInt_t>* list_of_vertices = bt->TrackToVertices(Responsible_track.first);
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
gStyle->SetOptStat(0);

TCanvas* c1a = new TCanvas("c1a","Momentum Resolution",1500,750);
c1a->Divide(2,1);
c1a->cd(1);
res_2Dhistos.at(0)->SetTitle(titles[6*ipdg]);
res_2Dhistos.at(0)->GetXaxis()->SetTitle("True Momentum (GeV)");
res_2Dhistos.at(0)->GetYaxis()->SetTitle("Reconstructed Momentum (GeV)");
res_2Dhistos.at(0)->Draw("col");
c1a->cd(2);
res_2Dhistos.at(1)->GetXaxis()->SetTitle("True Momentum (GeV)");
res_2Dhistos.at(1)->GetYaxis()->SetTitle("Reconstructed Momentum (GeV)");
res_2Dhistos.at(1)->Draw("col");
c1a->Print(saves[5*ipdg]);

TCanvas* c1b = new TCanvas("c1b","Fractional Momentum Resolution",2000,2000);
c1b->Divide(2,2);
c1b->cd(1);
frac_histos.at(0)->SetTitle(titles[6*ipdg+1]);
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
c1b->Print(saves[5*ipdg+1]);

TCanvas* c1c = new TCanvas("c1c","Absolute Difference Momentum Resolution",2000,2000);
c1c->Divide(2,2);
c1c->cd(1);
abs_histos.at(0)->SetTitle(titles[6*ipdg+2]);
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
c1c->Print(saves[5*ipdg+2]);

TCanvas* c2 = new TCanvas("c2","Angular Plots",1500,1500);
c2->Divide(2,2);
oneD_histos.at(2)->SetTitle("Angle from Drift Resolution");
oneD_histos.at(3)->SetTitle("Angle about Drift Resolution");
res_2Dhistos.at(2)->SetTitle(titles[6*ipdg+3]);
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
c2->Print(saves[5*ipdg+3]);

TCanvas* c3 = new TCanvas("c3","Dot Product vs True Momentum",1500,750);
c3->Divide(2,1);
c3->cd(1);
dot_2Dhistos.at(0)->SetTitle(titles[6*ipdg+4]);
dot_2Dhistos.at(0)->GetXaxis()->SetTitle("Fractional Difference");
dot_2Dhistos.at(0)->GetYaxis()->SetTitle("p_{true} #bullet p_{reco}");
dot_2Dhistos.at(0)->Draw("col");
c3->cd(2);
dot_2Dhistos.at(1)->SetTitle(titles[6*ipdg+5]);
dot_2Dhistos.at(1)->GetXaxis()->SetTitle("Absolute Difference");
dot_2Dhistos.at(1)->GetYaxis()->SetTitle("p_{true} #bullet p_{reco}");
dot_2Dhistos.at(1)->Draw("col");
c3->Print(saves[5*ipdg+4]);

}

for(int i =0; i<counts.size(); i++)
{
std::cout<<"=================\n"<<counts.at(i)<<std::endl;
}
}
