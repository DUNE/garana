# truth_ana.py 
# created: April 2021
# author: chilgenb@fnal.gov
# description: macro for demonstrating how to use garana
# usage: You will most likely need to update the file path given to TreeManager.
#        Then, in your terminal, enter the command 'python truth_ana.py' 
#        and that's all there is to it :)
#        you can build off the example below to access other trees/variables.
#        documentation is a work in progress. for now see documentation in
#        accessor base classes (garana/Base/*.h).


import garanainit # script for loading garana libs
import ROOT # loads all ROOT libs
from ROOT import TH1F
from ROOT import TH2F
from ROOT import TCanvas
from ROOT import TEfficiency
import numpy as np
garanainit.init() # loads the garana libs

#####################################################################
# central garana tree manager
# it links to all of the individual tree accessors given a file
# with garana trees produced in the default garana format
tm = ROOT.TreeManager("./structuredtree.root") #change to your file path
bt = ROOT.Backtracker(tm) # backtracker for association handling

pdgDB = ROOT.TDatabasePDG()
pdgDB.ReadPDGTable()

pdgToName = {11 : "e^{-}",          #leptons
            -11 : "e^{+}",
             12 : "#nu_{e}",
            -12 : "#bar{#nu}_{e}",
             13 : "#mu^{-}",
            -13 : "#mu^{+}",
             14 : "#nu_{#mu}",
            -14 : "#bar{#nu}_{#mu}",
             15 : "#tau^{-}",
            -15 : "#tau^{+}",
             16 : "#nu_{#tau}",
            -16 : "#bar{#nu}_{#tau}",
             22 : "#gamma",         # bosons
            111 : "#pi^{0}",        # light mesons
            211 : "#pi^{+}",
           -211 : "#pi^{-}",
            221 : "#eta",
            130 : "K_{L}^{0}",      # strange mesons
            310 : "K_{S}^{0}",
            311 : "K^{0}",
           -311 : "#bar{K^{0}}",
            321 : "K^{+}",
           -321 : "K^{-}",
           2112 : "n",              # light baryons
           2212 : "p", 
           1114 : "#Delta^{-}",
           2114 : "#Delta^{0}",
           2214 : "#Delta^{+}",
           2224 : "#Delta^{++}",
           3122 : "#Lambda",        # strange baryons
           3222 : "#Sigma^{+}",
           3212 : "#Sigma^{0}",
           3112 : "#Sigma^{-}"
}

# get accessors
gen = tm.GetGenTree() # genTree (generator level info)
g4 = tm.GetG4Tree() # g4Tree (geant4 level info)

# generator information
hg4nus = TH2F("hg4nus","g4Tree;N^{0} #nu's;GENIE scatter code",3,0,3,30,0,30)
hnureg = TH1F("hnureg",";#nu vertex region;",10,0,10)
hngen = TH1F("hngen","genTree;N^{0} MCTruth;",5,0,5)

# histograms for counting primaries
hnprim = TH1F("hnprim","g4Tree;N^{0} primaries;",40,0,40)
hprim_pdg = TH1F("hprim_pdg","g4Tree; MCParticle PDG code;",3400,-400,3000)
hprim_mumom = TH1F("hprim_mumom","g4Tree;true momentum [GeV/c];",50,0,5)
hprim_pmom = TH1F("hprim_pmom","g4Tree;true momentum [GeV/c];",50,0,5)
hprim_mumult = TH1F("hprim_mumult","g4Tree;primary particle multiplicity;",19,0,19)
hprim_pmult = TH1F("hprim_pmult","g4Tree;primary particle multiplicity;",19,0,19)
hprim_stopmult_tpc = TH1F("hprim_stopmult_tpc","g4Tree; N^{0} primaries stopping in active volume",10,0,10)
hprim_stopmult_calo = TH1F("hprim_stopmult_calo","g4Tree; N^{0} primaries stopping in active volume",10,0,10)
hprim_chgmult_tpc = TH1F("hprim_chgmult_tpc","g4Tree;N^{0} charged primaries;",19,0,19)
hprim_chgmult_calo = TH1F("hprim_chgmult_calo","g4Tree;N^{0} charged primaries;",19,0,19)

# primaries polar angle (w.r.t. beam direction)
hprim_theta_all = TH1F("hprim_theta_all","g4Tree: primaries;#theta [deg]",90,0,180)
hprim_theta_mu  = TH1F("hprim_theta_mu", "g4Tree: primaries;#theta [deg]",90,0,180)
hprim_theta_p   = TH1F("hprim_theta_p",  "g4Tree: primaries;#theta [deg]",90,0,180)
hprim_theta_pic = TH1F("hprim_theta_pic","g4Tree: primaries;#theta [deg]",90,0,180)

# initial and final particle times
hprim_t0 = TH1F("hprim_t0", "g4Tree; time [ns];",100,0,1e4)
hprim_tf = TH1F("hprim_tf", "g4Tree; time [ns];",100,0,1e4)
hall_t0 = TH1F("hall_t0",   "g4Tree; time [ns];",100,0,1e4)
hall_tf = TH1F("hall_tf",   "g4Tree; time [ns];",100,0,1e4)
henu_mu    = TH1F("henu_mu","genTree;E_{#nu} [GeV]",   50,0,10)
henu_mubar = TH1F("henu_mubar","genTree;E_{#nu} [GeV]",50,0,10)
henu_e     = TH1F("henu_e","genTree;E_{#nu} [GeV]",    50,0,10)
henu_ebar  = TH1F("henu_ebar","genTree;E_{#nu} [GeV]", 50,0,10)

# positions of G4Particles
hx = TH1F("hx","g4Tree;x [cm]",100,-300,300)
hy = TH1F("hy","g4Tree;y [cm]",100,-450,120)
hz = TH1F("hz","g4Tree;z [cm]",100,1250,1750)

pdgcts = {13:0} # all numu CC events should have at least one muon
pdgcts_calo = {13:0} # primaries passing through ECal


# loop over genTree entries
for ientry in range(gen.NEntries()):

	tm.GetEntry(ientry) # fill data members with data for current event

	if not (gen.IsGenie(0) and gen.IsCC(0) and gen.NuPDG(0)==14 and gen.NuInAV(0)) : continue #nu_mu CC w/vtx in TPC active volume only
	bt.FillMaps() # load the Backtracker maps for this tree entry

	# no. of primaries per neutrino interaction
	hnprim.Fill(g4.NPrimary())

	# counters 
	nnu = 0 # number of neutrinos 
	nprim_mu = 0 # no. primary muons
	nprim_p = 0 # no. primary protons
	nstop_tpc = 0 # no. primaries stopping in the TPC
	nstop_calo = 0 # no. primaries stopping in the ECal
	nprim_chg_tpc = 0 # no. charged primaries in the TPC
	nprim_chg_calo = 0 # no. charged primaries in the ECal
	inu = -1
	# loop over entries in the g4Tree
	for ig4 in range(g4.NSim()) :

		if g4.IsPrimary(ig4) :

			theta = ROOT.TMath.RadToDeg()*g4.SimMomBegin(ig4).Theta()
			hprim_theta_all.Fill(theta)
			hx.Fill(g4.SimPosBegin(ig4).X())
			hy.Fill(g4.SimPosBegin(ig4).Y())
			hz.Fill(g4.SimPosBegin(ig4).Z())

			if g4.IsCathodeCrosser(ig4) : print('found cathode crossing primary!')

			pdgcode = g4.PDG(ig4)
			if abs(pdgcode) > 6000 : continue # ignore recoil nucleus

			partPDG = pdgDB.GetParticle(pdgcode) # get info about particle by PDG code

			if not pdgcode in pdgcts :
				pdgcts[pdgcode] = 0

			pdgcts[pdgcode] += 1

			if g4.HasPassedCalo(ig4) :
				if not pdgcode in pdgcts_calo :
					pdgcts_calo[pdgcode] = 0
				pdgcts_calo[pdgcode] += 1

			hprim_pdg.Fill(pdgcode)
			if g4.IsStoppedTPC(ig4) : nstop_tpc +=1
			if g4.IsStoppedCalo(ig4) : nstop_calo +=1
			if partPDG.Charge()!=0 :
				if g4.HasPassedTPC(ig4): nprim_chg_tpc +=1
				if g4.HasPassedCalo(ig4): nprim_chg_calo +=1
			

			if abs(g4.PDG(ig4)) == 13 : # is it a muon?
				hprim_mumom.Fill(g4.SimMomBegin(ig4).P())
				hprim_theta_mu.Fill(theta)
				nprim_mu+=1

			if abs(g4.PDG(ig4)) == 211 : # is it a charged pion?
				hprim_theta_pic.Fill(theta)

			if g4.PDG(ig4) == 2212 : # is it a proton?
				hprim_pmom.Fill(g4.SimMomBegin(ig4).P())
				hprim_theta_p.Fill(theta)
				nprim_p+=1

		else : 
			if g4.IsCathodeCrosser(ig4) : print('found cathode crossing secondary!')
			continue

		if (abs(g4.PDG(ig4))==12 or abs(g4.PDG(ig4))==14) :
			nnu+=1

	hprim_mumult.Fill(nprim_mu)
	hprim_pmult.Fill(nprim_p)
	hprim_stopmult_tpc.Fill(nstop_tpc)
	hprim_stopmult_calo.Fill(nstop_calo)
	hprim_chgmult_tpc.Fill(nprim_chg_tpc)
	hprim_chgmult_calo.Fill(nprim_chg_calo)

        # loop over all interactions in this event
	hngen.Fill(gen.NGen())
	for igen in range(gen.NGen()):

		if not gen.IsGenie(igen) : continue
		enu = gen.NuP(igen).E()

		if gen.NuPDG(igen)==14  : henu_mu.Fill(enu)
		if gen.NuPDG(igen)==-14 : henu_mubar.Fill(enu)
		if gen.NuPDG(igen)==12  : henu_e.Fill(enu)
		if gen.NuPDG(igen)==-12 : henu_ebar.Fill(enu)

		hnureg.Fill(gen.NuRegion(igen))


# make pretty plots using particle names instead of PDG codes
hpdgtxt = TH1F("hpdgtxt","g4Tree: primaries;; counts per species",len(pdgcts),0,len(pdgcts))
hpdgtxt_calo = TH1F("hpdgtxt_calo","g4Tree: primaries;; counts per species",len(pdgcts),0,len(pdgcts))

# loop over counts per pdg in ascending order of counts
for i, (k,v) in enumerate(dict(sorted(pdgcts.items(), key=lambda item: item[1])).items()):
	hpdgtxt.SetBinContent(i+1,v)
	hpdgtxt.GetXaxis().SetBinLabel(i+1,pdgToName[k])

	if k in pdgcts_calo.keys():
		hpdgtxt_calo.SetBinContent(i+1,pdgcts_calo[k])

# draw our histogram and save it to file
cngen = TCanvas()
hngen.Draw("e0hist")

cnprim = TCanvas()
hnprim.Draw("e0hist")

cg4nus = TCanvas()
hg4nus.Draw("colz")	

cnureg = TCanvas()
hnureg.Draw("e0hist")

#
henu_mubar.SetLineColor(ROOT.kCyan)
henu_e.SetLineColor(ROOT.kRed)
henu_ebar.SetLineColor(ROOT.kMagenta)

cenu = TCanvas()
henu_mu.Draw("e0hist")
henu_mubar.Draw("e0hist same")
henu_e.Draw("e0hist same")
henu_ebar.Draw("e0hist same")

#
cprim_pdg = TCanvas()
hprim_pdg.Draw("e0hist") 

#
hprim_pmom.SetLineColor(ROOT.kRed)
hprim_mumom.SetLineWidth(2)
hprim_pmom.SetLineWidth(2)

cprim_mom = TCanvas()
hprim_pmom.Draw("e0hist")
hprim_mumom.Draw("e0hist same")

#
hprim_pmult.SetLineColor(ROOT.kRed)
hprim_mumult.SetLineWidth(2)
hprim_pmult.SetLineWidth(2)

cprim_mult = TCanvas()
hprim_mumult.Draw("e0hist")
hprim_pmult.Draw("e0hist same")
leg3 = ROOT.TLegend(0.6,0.6,0.8,0.8)
leg3.SetBorderSize(0)
leg3.AddEntry(hprim_mumult,"#mu^{#pm}","l")
leg3.AddEntry(hprim_pmult,"p^{+}","l")
leg3.Draw()

#
hprim_stopmult_calo.SetLineColor(ROOT.kRed)
hprim_stopmult_tpc.SetLineWidth(2)
hprim_stopmult_calo.SetLineWidth(2)

cprim_stopmult = TCanvas()
hprim_stopmult_tpc.Draw("e0hist")
hprim_stopmult_calo.Draw("e0hist same")
leg4 = ROOT.TLegend(0.6,0.6,0.8,0.8)
leg4.SetBorderSize(0)
leg4.AddEntry(hprim_stopmult_tpc,"TPC","l")
leg4.AddEntry(hprim_stopmult_calo,"TPC","l")
leg4.Draw()

#
hprim_chgmult_calo.SetLineColor(ROOT.kRed)
hprim_chgmult_tpc.SetLineWidth(2)
hprim_chgmult_calo.SetLineWidth(2)

cprim_chgmult = TCanvas()
hprim_chgmult_tpc.Draw("e0hist")
hprim_chgmult_calo.Draw("e0hist same")
leg4.Draw()

#
hpdgtxt.SetFillColor(ROOT.kBlue)
hpdgtxt_calo.SetFillColor(ROOT.kRed)
hpdgtxt.GetXaxis().SetLabelSize(0.07)

ROOT.gStyle.SetOptStat(0)
cpdgtxt = TCanvas()
cpdgtxt.SetLogx()
hpdgtxt.Draw("HBAR1 E0")
hpdgtxt_calo.Draw("HBAR1 E0 same")

leg = ROOT.TLegend(0.6,0.2,0.8,0.4)
leg.SetBorderSize(0)
leg.AddEntry("hpdgtxt","primaries in TPC","F")
leg.AddEntry("hpdgtxt_calo","primaries in ECal","F")
leg.Draw()

#
hprim_theta_all.SetLineWidth(2)
hprim_theta_mu.SetLineWidth(2)
hprim_theta_p.SetLineWidth(2)
hprim_theta_pic.SetLineWidth(2)

hprim_theta_mu.SetLineColor(ROOT.kGreen-1)
hprim_theta_p.SetLineColor(ROOT.kRed)
hprim_theta_pic.SetLineColor(ROOT.kMagenta)

ctheta = TCanvas()
hprim_theta_all.Draw("e0hist")
hprim_theta_mu.Draw("e0hist same")
hprim_theta_p.Draw("e0hist same")
hprim_theta_pic.Draw("e0hist same")
leg2 = ROOT.TLegend(0.6,0.6,0.8,0.8)
leg2.SetBorderSize(0)
leg2.AddEntry(hprim_theta_all,"all","l")
leg2.AddEntry(hprim_theta_mu,"#mu^{#pm}","l")
leg2.AddEntry(hprim_theta_p,"p^{+}","l")
leg2.AddEntry(hprim_theta_pic,"#pi^{#pm}","l")
leg2.Draw()

cx = TCanvas()
hx.Draw()

cy = TCanvas()
hy.Draw()

cz = TCanvas()
hz.Draw()

# ask for user input as a way to keep the program from ending so we can
# see the histogram.
# python doesn't like empty input strings so I abuse exception handling
try:
	null = input("press <Enter> to close canvas and exit program.") 

except:
	null = 'null'
#
