R__ADD_LIBRARY_PATH(/dune/app/users/birwin/garana_local_build/localProducts_garana_v00_00_13_e20_prof/garana/v00_00_13/slf7.x86_64.e20.prof/lib)
R__LOAD_LIBRARY(libGaranaAccessors.so)
R__LOAD_LIBRARY(libGaranaUtility.so)
R__ADD_INCLUDE_PATH(/dune/app/users/birwin/garana_local_build/localProducts_garana_v00_00_13_e20_prof/garana/v00_00_13/include)

/* Macro: FS Proton Reco Efficiency
 * Purpose: See how many tracks protons are split into on average and how much energy a proton gives to each ot these tracks*/

#include "garana/Accessors/TreeManager.h"
#include "garana/Utility/Backtracker.h"
#include <TH1F.h>
#include <iostream>
#include <math.h>

/* Macro: Proton Splitting
 * Purpose 1: Determine how often FS protons are split into multiple reconstruction tracks
 * Purpose 2: Determine how much energy protons give to track 1, track 2, etc. (track 1 being the track where most energy goes)
 * Purpose 3: Determine the cleanliness of these tracks: what fraction of energy from these tracks are from the proton
 */


using namespace garana;

void SplitClean()
{
string infile = "/dune/data/users/chilgenb/for_burke/structuredtree_bigish.root";

TreeManager* treeman = new TreeManager(infile);
Backtracker* bt = new Backtracker(treeman);

GenTree* gen = treeman->GetGenTree();
G4Tree* g4 = treeman->GetG4Tree();
RecoTree* reco = treeman->GetRecoTree();

//Protons
TH1D* np = new TH1D("np","Number of Tracks FS Protons are split into",10,.5,10.5);
TH1F* t1p = new TH1F("t1p","Energy Deposited in Primary Track",20,0.,2.0);
TH1F* t2p = new TH1F("t2p","Energy Deposited in Secondary Track",20,0.,1.0);
TH1F* t3p = new TH1F("t3p","Energy Deposited in Tertiary Track",20,0.,.5);
TH1F* t4p = new TH1F("t4p","Energy Deposited in Quaternary Track",20,0.,.5);
TH1D* clp = new TH1D("clp","Cleanliness",20,0.,1.);
TH1F* cl8p = new TH1F("cl8p","Momentum spectrum for protons >80% responsible for a track",100,0.0,10);
TH1F* clmidp = new TH1F("clmidp","Momentum spectrum for protons between 20 and 80% responsible for a track",100,0.0,10);
TH1F* cl2p = new TH1F("cl2p","Momentum spectrum for protons <20% responsible for a track",100,0.0,10);

//Muons
TH1D* nm = new TH1D("nm","Number of Tracks FS Muons are split into",10,.5,10.5);
TH1F* t1m = new TH1F("t1m","Energy Deposited in Primary Track",20,0.,2.0);
TH1F* t2m = new TH1F("t2m","Energy Deposited in Secondary Track",20,0.,1.0);
TH1F* t3m = new TH1F("t3m","Energy Deposited in Tertiary Track",20,0.,.5);
TH1F* t4m = new TH1F("t4m","Energy Deposited in Quaternary Track",20,0.,.5);
TH1D* clm = new TH1D("clm","Cleanliness",20,0.,1.);
TH1F* cl8m = new TH1F("cl8m","Momentum spectrum for protons >80% responsible for a track",100,0.0,10);
TH1F* clmidm = new TH1F("clmidm","Momentum spectrum for protons between 20 and 80% responsible for a track",100,0.0,10);
TH1F* cl2m = new TH1F("cl2m","Momentum spectrum for protons <20% responsible for a track",100,0.0,10);

//Charged Pions
TH1D* ncp = new TH1D("ncp","Number of Tracks FS Charged Pions are split into",10,.5,10.5);
TH1F* t1cp = new TH1F("t1cp","Energy Deposited in Primary Track",20,0.,2.0);
TH1F* t2cp = new TH1F("t2cp","Energy Deposited in Secondary Track",20,0.,1.0);
TH1F* t3cp = new TH1F("t3cp","Energy Deposited in Tertiary Track",20,0.,.5);
TH1F* t4cp = new TH1F("t4cp","Energy Deposited in Quaternary Track",20,0.,.5);
TH1D* clcp = new TH1D("clcp","Cleanliness",20,0.,1.);
TH1F* cl8cp = new TH1F("cl8cp","Momentum spectrum for protons >80% responsible for a track",100,0.0,10);
TH1F* clmidcp = new TH1F("clmidcp","Momentum spectrum for protons between 20 and 80% responsible for a track",100,0.0,10);
TH1F* cl2cp = new TH1F("cl2cp","Momentum spectrum for protons <20% responsible for a track",100,0.0,10);

//Charged Kaons
TH1D* nk = new TH1D("nk","Number of Tracks FS Charged Kaons are split into",10,.5,10.5);
TH1F* t1k = new TH1F("t1k","Energy Deposited in Primary Track",20,0.,2.0);
TH1F* t2k = new TH1F("t2k","Energy Deposited in Secondary Track",20,0.,1.0);
TH1F* t3k = new TH1F("t3k","Energy Deposited in Tertiary Track",20,0.,.5);
TH1F* t4k = new TH1F("t4k","Energy Deposited in Quaternary Track",20,0.,.5);
TH1D* clk = new TH1D("clk","Cleanliness",20,0.,1.);
TH1F* cl8k = new TH1F("cl8k","Momentum spectrum for protons >80% responsible for a track",100,0.0,10);
TH1F* clmidk = new TH1F("clmidk","Momentum spectrum for protons between 20 and 80% responsible for a track",100,0.0,10);
TH1F* cl2k = new TH1F("cl2k","Momentum spectrum for protons <20% responsible for a track",100,0.0,10);

vector<int> particle_types= {2212,13,211,321};

vector<TH1D*> ns = {np,nm,ncp,nk};
vector<TH1F*> ts = {t1p,t2p,t3p,t4p,t1m,t2m,t3m,t4m,t1cp,t2cp,t3cp,t4cp,t1k,t2k,t3k,t4k};
vector<TH1F*> specs = {cl8p,clmidp,cl2p,cl8m,clmidm,cl2m,cl8cp,clmidcp,cl2cp,cl8k,clmidk,cl2k};
vector<TH1D*> cls = {clp,clm,clcp,clk};

TH1I* tempnorm = new TH1I("tempnorm","Using this to divide",10,.5,10.5);

for(UInt_t ipdg = 0; ipdg<particle_types.size(); ipdg++)
{
	std::cout<<"IPDG: "<<ipdg<<std::endl;
	for(UInt_t ientry=0; ientry<treeman->NEntries(); ientry++)	//Loop through all events
		{
		treeman->GetEntry(ientry);
		bt->FillMaps();
		for(UInt_t ig4p = 0; ig4p<g4->NSim(); ig4p++)		//Loop through all true particles
		{
			int split = 0;
			vector<double> EnergyOrder;
			//vector<double> EOrder;
			if(g4->IsPrimary(ig4p) && g4->PDG(ig4p) == particle_types.at(ipdg))	//Only select FS Protons
			{
				for(UInt_t itrk = 0; itrk<reco->NTrack(); itrk++) //Loop through all tracks for event
				{
					auto ParticleList = bt->TrackToG4ParticlesDeposits(itrk);
					for(auto iter = ParticleList.begin(); iter != ParticleList.end(); iter++) //Loop through resposible particles for given track
					{
						if(ig4p==iter->first && iter->second>.005)	//associate protons to tracks and assert lower cutoff to energy reconstruction
						{
							split += 1;
							EnergyOrder.push_back(iter->second/g4->SimMomEnter(ig4p,0)->E());
							if(iter->second/reco->TrackTrueEnergy(itrk)<1)
							{
								cls.at(ipdg)->Fill(iter->second/reco->TrackTrueEnergy(itrk));
							}
							if(iter->second/reco->TrackTrueEnergy(itrk)==1)
							{
								cls.at(ipdg)->Fill(.99);
							}
							if(iter->second/reco->TrackTrueEnergy(itrk)>.8)
							{
								specs.at(3*ipdg)->Fill(g4->SimMomEnter(iter->first,0)->P());
							}
							if(.8>iter->second/reco->TrackTrueEnergy(itrk))
							{
								specs.at(3*ipdg+1)->Fill(g4->SimMomEnter(iter->first,0)->P());
							}
						}
					}
				}	
			}
			if(split!=0)
			{
				ns.at(ipdg)->Fill(split);
			}
			sort(EnergyOrder.begin(), EnergyOrder.end(), greater<double>());
			if(EnergyOrder.size()>0)
			{
				ts.at(4*ipdg)->Fill(EnergyOrder.at(0));
			}
			if(EnergyOrder.size()>1)
			{
				ts.at(4*ipdg+1)->Fill(EnergyOrder.at(1));
			}
			if(EnergyOrder.size()>2)
			{
				ts.at(4*ipdg+2)->Fill(EnergyOrder.at(2));
			}
			if(EnergyOrder.size()>3)
			{
				ts.at(4*ipdg+3)->Fill(EnergyOrder.at(3));
			}
		}
		}
}
gStyle->SetOptStat(0);
//Protons

TCanvas* c1 = new TCanvas("c1","Proton Splitting",1000,1000);
ns.at(0)->Scale(1./ns.at(0)->GetEntries());
ns.at(0)->GetXaxis()->SetTitle("Number of splittings");
ns.at(0)->GetXaxis()->SetRangeUser(1.,6.);
ns.at(0)->Draw("E");
c1->Print("ProtonFigures/prosplit.png");

TCanvas* c2 = new TCanvas("c2","Proton Energy Deposition per Track",1000,1000);
c2->Divide(2,2);
c2->cd(1);
ts.at(0)->SetTitle("Proton Primary Track");
ts.at(0)->GetXaxis()->SetTitle("Percent of true energy deposited");
ts.at(0)->Draw("E");

c2->cd(2);
ts.at(1)->SetTitle("Proton Secondary Track");
ts.at(1)->GetXaxis()->SetTitle("Percent of true energy deposited");
ts.at(1)->Draw("E");

c2->cd(3);
ts.at(2)->SetTitle("Proton Tertiary Track");
ts.at(2)->GetXaxis()->SetTitle("Percent of true energy deposited");
ts.at(2)->Draw("E");

c2->cd(4);
ts.at(3)->SetTitle("Proton Quaternary Track");
ts.at(3)->GetXaxis()->SetTitle("Percent of true energy deposited");
ts.at(3)->Draw("E");
c2->Print("ProtonFigures/propertrack.png");

TCanvas* c3 = new TCanvas("c3","Proton Cleanliness",1000,1000);
c3->Divide(2,2);
c3->cd(1);
cls.at(0)->SetTitle("Proton Cleanliness");
cls.at(0)->GetXaxis()->SetTitle("Percent of Track's True Energy that is deposited by proton");
cls.at(0)->Draw("E");

c3->cd(2);
specs.at(0)->SetTitle("Spectrum for protons >80% responsible for a track");
specs.at(0)->GetXaxis()->SetTitle("Momentum (GeV/c)");
specs.at(0)->GetXaxis()->SetRangeUser(0.,3.);
specs.at(0)->Draw("E");

c3->cd(4);
specs.at(1)->SetTitle("Spectrum for protons <80% responsible for a track");
specs.at(1)->GetXaxis()->SetTitle("Momentum (GeV/c)");
specs.at(1)->GetXaxis()->SetRangeUser(0.,3.);
specs.at(1)->Draw("E");
c3->Print("ProtonFigures/proclean.png");

//Muons
TCanvas* c4 = new TCanvas("c4","Muon Splitting",1000,1000);
ns.at(1)->Scale(1./ns.at(1)->GetEntries());
ns.at(1)->GetXaxis()->SetTitle("Number of splittings");
ns.at(1)->GetXaxis()->SetRangeUser(1.,6.);
ns.at(1)->Draw("E");
c4->Print("MuonFigures/musplit.png");

TCanvas* c5 = new TCanvas("c5","Muon Energy Deposition per Track",1000,1000);
c5->Divide(2,2);
c5->cd(1);
ts.at(4)->SetTitle("Muon Primary Track");
ts.at(4)->GetXaxis()->SetTitle("Percent of true energy deposited (GeV)");
ts.at(4)->Draw("E");

c5->cd(2);
ts.at(5)->SetTitle("Muon Secondary Track");
ts.at(5)->GetXaxis()->SetTitle("Percent of true energy deposited (GeV)");
ts.at(5)->Draw("E");

c5->cd(3);
ts.at(6)->SetTitle("Muon Tertiary Track");
ts.at(6)->GetXaxis()->SetTitle("Percent of true energy deposited (GeV)");
ts.at(6)->Draw("E");

c5->cd(4);
ts.at(7)->SetTitle("Muon Quaternary Track");
ts.at(7)->GetXaxis()->SetTitle("Percent of true energy deposited (GeV)");
ts.at(7)->Draw("E");
c5->Print("MuonFigures/mupertrack.png");

TCanvas* c6 = new TCanvas("c6","Muon Cleanliness",1000,1000);
c6->Divide(2,2);
c6->cd(1);
cls.at(1)->SetTitle("Muon Cleanliness");
cls.at(1)->GetXaxis()->SetTitle("Percent of Track's True Energy that is deposited by muon");
cls.at(1)->Draw("E");

c6->cd(2);
specs.at(3)->SetTitle("Spectrum for muons >80% responsible for a track");
specs.at(3)->GetXaxis()->SetTitle("Momentum (GeV)");
specs.at(3)->GetXaxis()->SetRangeUser(0.,3.);
specs.at(3)->Draw("E");

c6->cd(4);
specs.at(4)->SetTitle("Spectrum for muons <80% responsible for a track");
specs.at(4)->GetXaxis()->SetTitle("Momentum (GeV)");
specs.at(4)->GetXaxis()->SetRangeUser(0.,3.);
specs.at(4)->Draw("E");
c6->Print("MuonFigures/muclean.png");

//Charged Pions
TCanvas* c7 = new TCanvas("c7","Charged Pion Splitting",1000,1000);
ns.at(2)->Scale(1./ns.at(2)->GetEntries());
ns.at(2)->GetXaxis()->SetTitle("Number of splittings");
ns.at(2)->GetXaxis()->SetRangeUser(1.,6.);
ns.at(2)->Draw("E");
c7->Print("CPFigures/pisplit.png");

TCanvas* c8 = new TCanvas("c8","Charged Pion Energy Deposition per Track",1000,1000);
c8->Divide(2,2);
c8->cd(1);
ts.at(8)->SetTitle("Charged Pion Primary Track");
ts.at(8)->GetXaxis()->SetTitle("Percent of true energy deposited (GeV)");
ts.at(8)->Draw("E");

c8->cd(2);
ts.at(9)->SetTitle("Charged Pion Secondary Track");
ts.at(9)->GetXaxis()->SetTitle("Percent of true energy deposited (GeV)");
ts.at(9)->Draw("E");

c8->cd(3);
ts.at(10)->SetTitle("Charged Pion Tertiary Track");
ts.at(10)->GetXaxis()->SetTitle("Percent of true energy deposited (GeV)");
ts.at(10)->Draw("E");

c8->cd(4);
ts.at(11)->SetTitle("Chagred Pion Quaternary Track");
ts.at(11)->GetXaxis()->SetTitle("Percent of true energy deposited (GeV)");
ts.at(11)->Draw("E");
c8->Print("CPFigures/pipertrack.png");

TCanvas* c9 = new TCanvas("c9","Charged Pion Cleanliness",1000,1000);
c9->Divide(2,2);
c9->cd(1);
cls.at(2)->SetTitle("Charged Pion Cleanliness");
cls.at(2)->GetXaxis()->SetTitle("Percent of TrackTrueEnergy that is deposited by charged pion");
cls.at(2)->Draw("E");

c9->cd(2);
specs.at(6)->SetTitle("Spectrum for charged pions >80% responsible for a track");
specs.at(6)->GetXaxis()->SetTitle("Momentum (GeV)");
specs.at(6)->GetXaxis()->SetRangeUser(0.,3.);
specs.at(6)->Draw("E");

c9->cd(4);
specs.at(7)->SetTitle("Spectrum for charged pions <80% responsible for a track");
specs.at(7)->GetXaxis()->SetTitle("Momentum (GeV)");
specs.at(7)->GetXaxis()->SetRangeUser(0.,3.);
specs.at(7)->Draw("E");
c9->Print("CPFigures/piclean.png");

//Charged Kaons
TCanvas* c10 = new TCanvas("c10","Charged Kaon Splitting",1000,1000);
ns.at(3)->Scale(1./ns.at(3)->GetEntries());
ns.at(3)->GetXaxis()->SetTitle("Number of splittings");
ns.at(3)->GetXaxis()->SetRangeUser(1.,6.);
ns.at(3)->Draw("E");
c10->Print("CKFigures/ksplit.png");

TCanvas* c11 = new TCanvas("c11","Charged Kaon Energy Deposition per Track",1000,1000);
c11->Divide(2,2);
c11->cd(1);
ts.at(12)->SetTitle("Charged Kaon Primary Track");
ts.at(12)->GetXaxis()->SetTitle("Percent of true energy deposited (GeV)");
ts.at(12)->Draw("E");

c11->cd(2);
ts.at(13)->SetTitle("Charged Kaon Secondary Track");
ts.at(13)->GetXaxis()->SetTitle("Percent of true energy deposited (GeV)");
ts.at(13)->Draw("E");

c11->cd(3);
ts.at(14)->SetTitle("Charged Kaon Tertiary Track");
ts.at(14)->GetXaxis()->SetTitle("Percent of true energy deposited (GeV)");
ts.at(14)->Draw("E");

c11->cd(4);
ts.at(15)->SetTitle("Charged Kaon Quaternary Track");
ts.at(15)->GetXaxis()->SetTitle("Percent of true energy deposited (GeV)");
ts.at(15)->Draw("E");
c11->Print("CKFigures/kpertrack.png");

TCanvas* c12 = new TCanvas("c12","Charged Kaon Cleanliness",1000,1000);
c12->Divide(2,2);
c12->cd(1);
cls.at(3)->SetTitle("Charged Kaon Cleanliness");
cls.at(3)->GetXaxis()->SetTitle("Percent of TrackTrueEnergy that is deposited by charged kaon");
cls.at(3)->Draw("E");

c12->cd(2);
specs.at(9)->SetTitle("Spectrum for charged kaons >80% responsible for a track");
specs.at(9)->GetXaxis()->SetTitle("Momentum (GeV)");
specs.at(9)->GetXaxis()->SetRangeUser(0.,3.);
specs.at(9)->Draw("E");

c12->cd(4);
specs.at(10)->SetTitle("Spectrum for charged kaons <80% responsible for a track");
specs.at(10)->GetXaxis()->SetTitle("Momentum (GeV)");
specs.at(10)->GetXaxis()->SetRangeUser(0.,3.);
specs.at(10)->Draw("E");
c12->Print("CKFigures/kclean.png");

}
