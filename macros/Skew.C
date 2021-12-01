R__ADD_LIBRARY_PATH(/dune/app/users/birwin/garana_local_build/localProducts_garana_v00_00_13_e20_prof/garana/v00_00_13/slf7.x86_64.e20.prof/lib)
R__LOAD_LIBRARY(libGaranaAccessors.so)
R__LOAD_LIBRARY(libGaranaUtility.so)
R__ADD_INCLUDE_PATH(/dune/app/users/birwin/garana_local_build/localProducts_garana_v00_00_13_e20_prof/garana/v00_00_13/include)

/* Macro: FS Proton Skew vs. True Momentum
 * Purpose 1: Study the skew in the resolution distribution for different bins of true momenta
 * Purpose 2:*/

#include "garana/Accessors/TreeManager.h"
#include "garana/Utility/Backtracker.h"
#include <TH1F.h>
#include <iostream>
#include <math.h>
#include <TStyle.h>
#include "functions.h"

using namespace garana;

void Skew()
{
	string infile =  "/dune/data/users/birwin/structuredtree_files/structuredtree_full.root";

	TreeManager* treeman = new TreeManager(infile);
	Backtracker* bt = new Backtracker(treeman);
	GenTree* gen = treeman->GetGenTree();
	G4Tree*  g4  = treeman->GetG4Tree();
	RecoTree* reco = treeman->GetRecoTree();

	vector<int> particle_types= {2212,13,211,321};

	double sbins[28] = {.3,.4,.5,.6,.7,.8,.9,1.,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.};

	//Protons
	TH1D* pfmean = new TH1D("pfmean","Fractional Resonlution Mean vs True Momentum",27,sbins);
	TH1D* pamean = new TH1D("pamean","Absolute Difference Mean vs True Momentum",27,sbins);
	TH1D* pfrms  = new TH1D("pfrms","Fractional Resolution RMS vs True Momentum",27,sbins);
	TH1D* parms  = new TH1D("parms","Absolutel Difference RMS vs True Momentum",27,sbins);
	TH1D* pfskew = new TH1D("pfskew","Fractional Resolution Skew vs True Momentum",27,sbins);
	TH1D* paskew = new TH1D("paskew","Absolute Difference Skew vs True Momentum",27,sbins);
	//Muons
	TH1D* mfmean = new TH1D("mfmean","Fractional Resonlution Mean vs True Momentum",27,sbins);
	TH1D* mamean = new TH1D("mamean","Absolute Difference Mean vs True Momentum",27,sbins);
	TH1D* mfrms  = new TH1D("mfrms","Fractional Resolution RMS vs True Momentum",27,sbins);
	TH1D* marms  = new TH1D("marms","Absolutel Difference RMS vs True Momentum",27,sbins);
	TH1D* mfskew = new TH1D("mfskew","Fractional Resolution Skew vs True Momentum",27,sbins);
	TH1D* maskew = new TH1D("maskew","Absolute Difference Skew vs True Momentum",27,sbins);
	//Charged Pions
	TH1D* cpfmean = new TH1D("cpfmean","Fractional Resonlution Mean vs True Momentum",27,sbins);
        TH1D* cpamean = new TH1D("cpamean","Absolute Difference Mean vs True Momentum",27,sbins);
        TH1D* cpfrms  = new TH1D("cpfrms","Fractional Resolution RMS vs True Momentum",27,sbins);
        TH1D* cparms  = new TH1D("cparms","Absolutel Difference RMS vs True Momentum",27,sbins);
        TH1D* cpfskew = new TH1D("cpfskew","Fractional Resolution Skew vs True Momentum",27,sbins);
        TH1D* cpaskew = new TH1D("cpaskew","Absolute Difference Skew vs True Momentum",27,sbins);
	//Charged Kaons
	TH1D* kfmean = new TH1D("kfmean","Fractional Resonlution Mean vs True Momentum",27,sbins);
        TH1D* kamean = new TH1D("kamean","Absolute Difference Mean vs True Momentum",27,sbins);
        TH1D* kfrms  = new TH1D("kfrms","Fractional Resolution RMS vs True Momentum",27,sbins);
        TH1D* karms  = new TH1D("karms","Absolutel Difference RMS vs True Momentum",27,sbins);
        TH1D* kfskew = new TH1D("kfskew","Fractional Resolution Skew vs True Momentum",27,sbins);
        TH1D* kaskew = new TH1D("kaskew","Absolute Difference Skew vs True Momentum",27,sbins);

	vector<TH1D*> frac_histos = {pfmean,pfrms,pfskew,mfmean,mfrms,mfskew,cpfmean,cpfrms,cpfskew,kfmean,kfrms,kfskew};
	vector<TH1D*> abs_histos  = {pamean,parms,paskew,mamean,marms,maskew,cpamean,cparms,cpaskew,kamean,karms,kaskew};
	const char *titles[24]	  = {"Proton Fractional Difference Mean vs True Momentum","Proton Absolute Difference Mean vs True Momentum","Proton Fractional Difference RMS vs True Momentum","Proton Absolute Difference RMS vs True Momentum","Proton Fractional Difference Skewness vs True Momentum","Proton Absolute Difference Skewness vs True Momentum","Muon Fractional Difference Mean vs True Momentum","Muon Absolute Difference Mean vs True Momentum","Muon Fractional Difference RMS vs True Momentum","Muon Absolute Difference RMS vs True Momentum","Muon Fractional Difference Skewness vs True Momentum","Muon Absolute Difference Skewness vs True Momentum","Charged Pion Fractional Difference Mean vs True Momentum","Charged Pion Absolute Difference Mean vs True Momentum","Charged Pion Fractional Difference RMS vs True Momentum","Charged Pion Absolute Difference RMS vs True Momentum","Charged Pion Fractional Difference Skewness vs True Momentum","Charged Pion Absolute Difference Skewness vs True Momentum","Charged Kaon Fractional Difference Mean vs True Momentum","Charged Kaon Absolute Difference Mean vs True Momentum","Charged Kaon Fractional Difference RMS vs True Momentum","Charged Kaon Absolute Difference RMS vs True Momentum","Charged Kaon Fractional Difference Skewness vs True Momentum","Charged Kaon Absolute Difference Skewness vs True Momentum"};
	const char *saves[4]      = {"ProtonFigures/MeanRMSSkew.png","MuonFigures/MeanRMSSkew.png","CPFigures/MeanRMSSkew.png","CKFigures/MeanRMSSkew.png"};

	for(UInt_t ipdg = 0; ipdg<particle_types.size(); ipdg++)
	{
		std::cout<<"Particle: "<<ipdg<<std::endl;
		//Skew Histos
		TH1F* f1 = new TH1F("f1","Get fskew per true_p bin",100,1.5,1.);
		TH1F* a1 = new TH1F("a1","Get askew per true_p bin",30,-3.,3.);
                TH1F* f2 = new TH1F("f2","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a2 = new TH1F("a2","Get askew per true_p bin",30,-3.,3.);
                TH1F* f3 = new TH1F("f3","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a3 = new TH1F("a3","Get askew per true_p bin",30,-3.,3.);
                TH1F* f4 = new TH1F("f4","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a4 = new TH1F("a4","Get askew per true_p bin",30,-3.,3.);
                TH1F* f5 = new TH1F("f5","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a5 = new TH1F("a5","Get askew per true_p bin",30,-3.,3.);
                TH1F* f6 = new TH1F("f6","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a6 = new TH1F("a6","Get askew per true_p bin",30,-3.,3.);
                TH1F* f7 = new TH1F("f7","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a7 = new TH1F("a7","Get askew per true_p bin",30,-3.,3.);
                TH1F* f8 = new TH1F("f8","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a8 = new TH1F("a8","Get askew per true_p bin",30,-3.,3.);
                TH1F* f9 = new TH1F("f9","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a9 = new TH1F("a9","Get askew per true_p bin",30,-3.,3.);
                TH1F* f10 = new TH1F("f10","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a10 = new TH1F("a10","Get askew per true_p bin",30,-3.,3.);
                TH1F* f11 = new TH1F("f11","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a11 = new TH1F("a11","Get askew per true_p bin",30,-3.,3.);
                TH1F* f12 = new TH1F("f12","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a12 = new TH1F("a12","Get askew per true_p bin",30,-3.,3.);
                TH1F* f13 = new TH1F("f13","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a13 = new TH1F("a13","Get askew per true_p bin",30,-3.,3.);
                TH1F* f14 = new TH1F("f14","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a14 = new TH1F("a14","Get askew per true_p bin",30,-3.,3.);
                TH1F* f15 = new TH1F("f15","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a15 = new TH1F("a15","Get askew per true_p bin",30,-3.,3.);
                TH1F* f16 = new TH1F("f16","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a16 = new TH1F("a16","Get askew per true_p bin",30,-3.,3.);
                TH1F* f17 = new TH1F("f17","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a17 = new TH1F("a17","Get askew per true_p bin",30,-3.,3.);
                TH1F* f18 = new TH1F("f18","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a18 = new TH1F("a18","Get askew per true_p bin",30,-3.,3.);
                TH1F* f19 = new TH1F("f19","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a19 = new TH1F("a19","Get askew per true_p bin",30,-3.,3.);
                TH1F* f20 = new TH1F("f20","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a20 = new TH1F("a20","Get askew per true_p bin",30,-3.,3.);
                TH1F* f21 = new TH1F("f21","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a21 = new TH1F("a21","Get askew per true_p bin",30,-3.,3.);
                TH1F* f22 = new TH1F("f22","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a22 = new TH1F("a22","Get askew per true_p bin",30,-3.,3.);
                TH1F* f23 = new TH1F("f23","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a23 = new TH1F("a23","Get askew per true_p bin",30,-3.,3.);
                TH1F* f24 = new TH1F("f24","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a24 = new TH1F("a24","Get askew per true_p bin",30,-3.,3.);
                TH1F* f25 = new TH1F("f25","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a25 = new TH1F("a25","Get askew per true_p bin",30,-3.,3.);
                TH1F* f26 = new TH1F("f26","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a26 = new TH1F("a26","Get askew per true_p bin",30,-3.,3.);
                TH1F* f27 = new TH1F("f27","Get fskew per true_p bin",100,1.5,1.);
                TH1F* a27 = new TH1F("a27","Get askew per true_p bin",30,-3.,3.);
		vector<TH1F*> fhistos = {f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15,f16,f17,f18,f19,f20,f21,f22,f23,f24,f25,f26,f27};
		vector<TH1F*> ahistos = {a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27};


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
				int association = 0;
				pair<int,float> Responsible_track;
				//FS Proton Check, FV Cut
                        	if(g4->IsPrimary(ig4p) && g4->PDG(ig4p) == particle_types.at(ipdg))
				{
				        if(-220.<gen->NuVertex(bt->G4ParticleToGTruth(ig4p))->X()<220. && sqrt(pow(gen->NuVertex(bt->G4ParticleToGTruth(ig4p))->Y(),2)+pow(gen->NuVertex(bt->G4ParticleToGTruth(ig4p))->Z(),2))<230.)
                                	{
					for(UInt_t itrk=0; itrk<reco->NTrack(); itrk++) //Loop through reconstructed tracks
                                        {
						auto PrimeParticle = bt->TrackToG4ParticleDeposit(itrk);
                                                if(ig4p==PrimeParticle.first)
                                                {
                        	                        association += 1;
                        				//Find the track that the proton gave the most energy to
							if(PrimeParticle.second>Responsible_track.second)
                                                                {
                                                                        Responsible_track = make_pair(itrk,PrimeParticle.second);
                                                                }
                                                        }
                                                }
                                        }
				}
                                if(association != 0)
                                {
					double true_p = g4->SimMomEnter(ig4p,0)->P();
					for(UInt_t ia = 0; ia<27; ia++)
					{
						if(true_p>sbins[ia] && true_p<sbins[ia+1])
						{
							double reco_p = reco->TrackMomBeg(Responsible_track.first)->Mag();
							double aprespoint = true_p-reco_p;
							double fprespoint = (true_p-reco_p)/(sbins[ia]+.05);
							fhistos.at(ia)->Fill(fprespoint);
							ahistos.at(ia)->Fill(aprespoint);
						}
					}
				}
			}//Particle Loop
		}//Event Loop	
		for(UInt_t idata = 1; idata<28; idata++)
		{
			frac_histos.at(3*ipdg)->SetBinContent(idata,fhistos.at(idata-1)->GetMean(1));
                        abs_histos.at(3*ipdg)->SetBinContent(idata,ahistos.at(idata-1)->GetMean(1));
			frac_histos.at(3*ipdg+1)->SetBinContent(idata,fhistos.at(idata-1)->GetRMS(1));
			abs_histos.at(3*ipdg+1)->SetBinContent(idata,ahistos.at(idata-1)->GetRMS(1));
			frac_histos.at(3*ipdg+2)->SetBinContent(idata,fhistos.at(idata-1)->GetSkewness(1));
			abs_histos.at(3*ipdg+2)->SetBinContent(idata,ahistos.at(idata-1)->GetSkewness(1));
			delete fhistos.at(idata-1);
			delete ahistos.at(idata-1);
		}

gStyle->SetOptStat(0);

TCanvas* c1 = new TCanvas("c1","Skewness vs True Momentum",1500,1000);
c1->Divide(3,2);
c1->cd(1);
frac_histos.at(3*ipdg)->SetTitle(titles[6*ipdg]);
frac_histos.at(3*ipdg)->GetXaxis()->SetTitle("True p (GeV/c)");
frac_histos.at(3*ipdg)->GetYaxis()->SetTitle("Mean");
frac_histos.at(3*ipdg)->Draw();
c1->cd(4);
abs_histos.at(3*ipdg)->SetTitle(titles[6*ipdg+1]);
abs_histos.at(3*ipdg)->GetXaxis()->SetTitle("True p (GeV/c)");
abs_histos.at(3*ipdg)->GetYaxis()->SetTitle("Mean");
abs_histos.at(3*ipdg)->Draw();
c1->cd(2);
frac_histos.at(3*ipdg+1)->SetTitle(titles[6*ipdg+2]);
frac_histos.at(3*ipdg+1)->GetXaxis()->SetTitle("True p (GeV/c)");
frac_histos.at(3*ipdg+1)->GetYaxis()->SetTitle("RMS");
frac_histos.at(3*ipdg+1)->Draw();
c1->cd(5);
abs_histos.at(3*ipdg+1)->SetTitle(titles[6*ipdg+3]);
abs_histos.at(3*ipdg+1)->GetXaxis()->SetTitle("True p (GeV/c)");
abs_histos.at(3*ipdg+1)->GetYaxis()->SetTitle("RMS");
abs_histos.at(3*ipdg+1)->Draw();
c1->cd(3);
frac_histos.at(3*ipdg+2)->SetTitle(titles[6*ipdg+4]);
frac_histos.at(3*ipdg+2)->GetXaxis()->SetTitle("True p (GeV/c)");
frac_histos.at(3*ipdg+2)->GetYaxis()->SetTitle("Skewness");
frac_histos.at(3*ipdg+2)->Draw();
c1->cd(6);
abs_histos.at(3*ipdg+2)->SetTitle(titles[6*ipdg+5]);
abs_histos.at(3*ipdg+2)->GetXaxis()->SetTitle("True p (GeV/c)");
abs_histos.at(3*ipdg+2)->GetYaxis()->SetTitle("Skewness");
abs_histos.at(3*ipdg+2)->Draw();
c1->Print(saves[ipdg]);
}//ipdg loop
}
