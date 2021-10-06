# tracks.py 
# created: April 2021
# author: chilgenb@fnal.gov
# description: macro for demonstrating how to use garana
# usage: in your terminal, enter the command 'python tracks.py' 
#        and that's all there is to it :)
#        you can build off the example below to access other trees/variables.
#        documentation is a work in progress. for now see documentation in
#        accessor base classes (garana/Base/*.h).


import garanainit # script for loading garana libs
import ROOT, sys
from ROOT import TH1F, TH2F, TCanvas
from ROOT import gStyle, gROOT
#from ROOT import TCanvas
import numpy as np
import math

######################################################################################
#python wrapper for track parameters array
# N.B. assume backward and forward fit give very similar track params and use forward only
def GetTrackPars(rec,itrk) :
	parsvec = ROOT.std.vector("float")(5)
	pars = np.asarray(parsvec) # python-friendly array
	rec.TrackParBeg(itrk,pars)
	return pars


# inputs
#  - pos : trajectory point on a fit track (TLorentzvector)
#  - x0 : 6th track parameter (independent of track fit)
#  - params[5] : track fit parameters(y0,z0,c,phi0,lambda)
# output
#  - phi (radians)
def GetPhi(pos,x0,pars):

	# give params human-readable names
	y0 = pars[0]
	z0 = pars[1]
	r = 1.0/pars[2] # radius of curvature of circle in y-z plane
	phi0 = pars[3]
	lam = pars[4]

	# circle center
	yc = y0 + r * math.cos(phi0)
	zc = z0 - r * math.sin(phi0)

	# need to get phi from x-coordinate
	# in y,z, phi is degenerate: phi = phi + m*2pi, m is int
	return (pos.X()-x0)/(r*math.tan(lam))+phi0
	



# phi-difference between track endpoints
# input: rec (recoTree accessor) and track index (int)
# output: value of delta phi (float)
# N.B. assume backward and forward fit give very similar track params and use forward only
def GetDeltaPhi(rec, itrk) :

	#parsvec = ROOT.std.vector("float")(5)
	#pars = np.asarray(parsvec) # python-friendly array
	#rec.TrackParBeg(itrk,pars)
	pars = GetTrackPars(rec,itrk)

	vtx = rec.TrackVertex(itrk)
	end = rec.TrackEnd(itrk)

	phivtx = GetPhi(vtx,vtx.X(),pars)
	phiend = GetPhi(end,vtx.X(),pars)
	return phiend-phivtx

	

############################################################
garanainit.init() # loads the garana libs

# central garana tree manager
# it links to all of the individual tree accessors given a file
# with garana trees produced in the default garana format
tm = ROOT.TreeManager("../structuredtree.root") #change to your file path
bt = ROOT.Backtracker(tm)

# get accessors
gen = tm.GetGenTree() # genTree
g4  = tm.GetG4Tree()  # g4Tree
rec = tm.GetRecoTree() # recoTree

print("found trees with "+str(rec.NEntries())+" entries")

# set up histograms
# counting
hntrack = TH1F("hntrack", ";N^{0} tracks per #nu;",               50,-0.5,49.5)
hnhit   = TH1F("hnhit",   "TPC track reco; N^{0} hits per track;",200,0.5,1000.5)
hnvtx   = TH1F("hnvtx",   ";N^{0} vertices per #nu;",             6,1.5,7.5)
hnvtxtrk= TH1F("hnvtxtrk",";N^{0} vertices per track;",           5,-0.5,4.5)
hntrkvtx= TH1F("hntrkvtx",";N^{0} tracks per vertex;",            7,2.5,9.5)

# track parameters
hx0     = TH1F("hx0",     "TPC track reco: fit parameters;x_{0} [cm]", 50,-280,280)
hy0     = TH1F("hy0",     "TPC track reco: fit parameters;y_{0} [cm]", 50,-450,150)
hz0     = TH1F("hz0",     "TPC track reco: fit parameters;z_{0} [cm]", 50,1250,1750)
hr      = TH1F("hr",      "TPC track reco: fit parameters;radius in y-z plane [cm]", 100,0,800)
hphi0   = TH1F("hphi0",   "TPC track reco: fit parameters;#phi_{0} [rad]", 40,-20,-20)
hlambda = TH1F("hlambda", "TPC track reco: fit parameters;#lambda [rad]", 50,-3.2,3.2)
hdeltaphi = TH1F("hdeltaphi", "TPC track reco: fit parameters;#phi_{end}- #phi_{vertex} [rad]",50,-2*math.pi,2*math.pi)
hdeltaphilen = TH1F("hdeltaphilen", "TPC track reco: fit parameters;(#phi_{end}- #phi_{vertex})/track length [rad/cm]",50,-0.005,0.005)

# reco track length fwd and back
hlength_fwd = TH1F("hlength_fwd",";track length [cm]",100,0,500)
hlength_bkd = TH1F("hlength_bkd",";track length [cm]",100,0,500)

#reco mom fwd and back
hmom_fwd = TH1F("hmom_fwd",";momentum [GeV/c]",100,0,5)
hmom_bkd = TH1F("hmom_bkd",";momentum [GeV/c]",100,0,5)

# truth matching
hpval           = TH1F("hpval","Track reco;p-value;",100,0,1)
hpdg            = TH1F("hpdg",";PDG code",2800,-500,2300)
hpdg_max        = TH1F("hpdg_max",";PDG code",2800,-500,2300) #MCParticles contributing most energy to track
hpdg_max_pval   = TH2F("hpdg_max_pval",";track fit p-value;PDG code",40,0,1,2800,-500,2300)
hng4p           = TH1F("hng4p",";number MCParticles matched to track",7,-0.5,6.5) # num MCParticles associated to track
hg4mom          = TH1F("hg4mom",";momentum per particle [GeV/c]",100,0,5) # MCParticle momenta
hg4mom_tot_pval = TH2F("hg4mom_tot_pval","TPC track reco;track fit p-value ; p_{true} [GeV/c]",40,0,1,40,0,3)
hg4mom1         = TH1F("hg4mom1",";maximum single-particle momentum [GeV/c]",100,0,5) # MCParticle momenta w/max edep
hg4mom1_frac    = TH1F("hg4mom1_frac",";fraction of total momentum held by single-particle max",100,0,1.01) 

hntrkpart       = TH1F("hntrkpart",   "MCParticle #rightarrow Track ; N^{0} tracks per particle",10,-0.5,9.5) # num tracks associated to G4Particle
hntrkpart_p     = TH1F("hntrkpart_p",  "MCParticle #rightarrow Track ; N^{0} tracks per particle",9,0.5,9.5) 
hntrkpart_mu    = TH1F("hntrkpart_mu", "MCParticle #rightarrow Track ; N^{0} tracks per particle",9,0.5,9.5)
hntrkpart_pic   = TH1F("hntrkpart_pic","MCParticle #rightarrow Track ; N^{0} tracks per particle",9,0.5,9.5)
hntrkpart_e     = TH1F("hntrkpart_e",  "MCParticle #rightarrow Track ; N^{0} tracks per particle",9,0.5,9.5)
hntrkpart_vs_mom = TH2F('hntrkpart_vs_mom','MCParticle #rightarrow Track ; N^{0} tracks per particle; true initial momentum [GeV/c]',10,-0.5,9.5,50,0,3)
hntrkpart_vs_gyro = TH2F('hntrkpart_vs_gyro','MCParticle #rightarrow Track ; N^{0} tracks per particle;gyroradius [m]',10,-0.5,9.5,50,0,10)

hnmom1_frac = TH2F("hnmom1_frac",";fraction of total momentum ; number of particles",50,0,1.01,14,0.5,14.5)

# resolution
hmomres2d = TH2F("hmomres2d",";P_{true} [GeV/c] ; P_{reco} [GeV/c]",50,0,3,50,0,3)
hmomres2d_pval = TH2F("hmomres2d_pval",";track fit p-value;p_{true} - p_{reco} [GeV/c]",50,0,1,50,-3,5)
hmomres2d_frac_pval = TH2F("hmomres2d_frac_pval",";track fit p-value;(p_{true} - p_{reco})/p_{true}",50,0,1,50,-1,1)
hmomres_diff = TH1F("hmomres_diff","TPC track reco; p_{true} - p_{reco} [GeV/c];",80,-3,5)
hmomres_frac = TH1F("hmomres_frac","TPC track reco; ( p_{true} - p_{reco})/p_{true};",60,-1,1)

hxdiff = TH1F("hxdiff","TPC track reco;true - reco [cm]",100,-35,35)
hydiff = TH1F("hydiff","TPC track reco;true - reco [cm]",100,-35,35)
hzdiff = TH1F("hzdiff","TPC track reco;true - reco [cm]",100,-35,35)

# loop over events
for ientry in range(tm.NEntries()) :

	tm.GetEntry(ientry) # fill data members with data for current event

	if not (gen.IsGenie(0) and gen.IsCC(0) and gen.NuPDG(0)==14 and gen.NuInAV(0)) : continue #nu_mu CC w/vtx in TPC active volume only
	bt.FillMaps()

	hntrack.Fill(rec.NTrack())
	hnvtx.Fill(rec.NVertex())


        # loop over all reco tracks
	for itrk in range(rec.NTrack()):

		hnhit.Fill(rec.NTrackHit(itrk))
		hnvtxtrk.Fill(len(bt.TrackToVertices(itrk)))

		pval = ROOT.TMath.Prob(rec.TrackChiSqrFwd(itrk),rec.NTrackHit(itrk)-5)
		hpval.Fill(pval)
		if pval<1e-9 : continue

		trkpars = GetTrackPars(rec,itrk)
		trkvtx = rec.TrackVertex(itrk)
		hx0.Fill(trkvtx.X())
		hy0.Fill(trkpars[0])
		hz0.Fill(trkpars[1])
		hr.Fill(1.0/trkpars[2])
		hphi0.Fill(trkpars[3])
		hlambda.Fill(trkpars[4])
		hdeltaphi.Fill(GetDeltaPhi(rec,itrk))
		hdeltaphilen.Fill(GetDeltaPhi(rec,itrk)/rec.TrackLenFwd(itrk))

		hlength_fwd.Fill(rec.TrackLenFwd(itrk))
		hlength_bkd.Fill(rec.TrackLenBkd(itrk))

		if rec.TrackMomBeg(itrk).Mag()>0 :
			hmom_fwd.Fill(rec.TrackMomBeg(itrk).Mag())

		if rec.TrackMomEnd(itrk).Mag()>0 :
			hmom_bkd.Fill(rec.TrackMomEnd(itrk).Mag())

		ig4ps = bt.TrackToG4Particles(itrk)
		hng4p.Fill(len(ig4ps))

		imax = 0
		maxp = -1.
		sump = 0.
		for ig4p in ig4ps :

			hg4mom.Fill(g4.SimMomEnter(ig4p)[0].P())
			hpdg.Fill(g4.PDG(ig4p))
			sump += g4.SimMomEnter(ig4p)[0].P()
			if g4.SimMomEnter(ig4p)[0].P() > maxp :
				maxp = g4.SimMomEnter(ig4p)[0].P()
				imax = ig4p

		hg4mom1.Fill(maxp)
		hg4mom1_frac.Fill(maxp/sump)
		hnmom1_frac.Fill(maxp/sump,len(ig4ps))

		hpdg_max.Fill(g4.PDG(imax))
		hpdg_max_pval.Fill(pval,g4.PDG(imax))

		posbeg = rec.TrackVertex(itrk)
		posend = rec.TrackEnd(itrk)
		trueposbeg = rec.TrackTruePosBeg(itrk);
		trueposend = rec.TrackTruePosEnd(itrk);

		if trueposend.Vect().Mag() != 0 :
			hxdiff.Fill(trueposend.X() - posend.X())
			hydiff.Fill(trueposend.Y() - posend.Y())
			hzdiff.Fill(trueposend.Z() - posend.Z())


		if g4.PDG(imax)==13 and rec.TrackMomBeg(itrk).Mag() > 0:
			hmomres2d.Fill(sump,rec.TrackMomBeg(itrk).Mag())
		

		hg4mom_tot_pval.Fill(pval,maxp)
		hmomres_diff.Fill(maxp-rec.TrackMomBeg(itrk).Mag())
		hmomres_frac.Fill((maxp-rec.TrackMomBeg(itrk).Mag())/sump)
		hmomres2d_pval.Fill(pval,maxp-rec.TrackMomBeg(itrk).Mag())
		hmomres2d_frac_pval.Fill(pval,(maxp-rec.TrackMomBeg(itrk).Mag())/sump)

	# loop over G4Particles
	for ig4p in range(g4.NSim()) :

		# track indices matched to this particle
		itrks = bt.G4ParticleToTracks(ig4p)

		if len(itrks) > 0 : # could have no matches

			# try to avoid cathode crossers (for now)
			if g4.IsCathodeCrosser(ig4p) : continue

			ntracks = 0
			for itrk in itrks :
				if len(bt.TrackToG4Particles(itrk)) > 1 : continue
				ntracks += 1

			if ntracks==0 : continue

			hntrkpart.Fill(ntracks) #len(itrks))
			hntrkpart_vs_mom.Fill(len(itrks),g4.SimMomEnter(ig4p,0).P())
			hntrkpart_vs_gyro.Fill(len(itrks),3.3*g4.SimMomEnter(ig4p,0).Pt()/0.5)

			if abs(g4.PDG(ig4p)) == 2212 : # proton
				hntrkpart_p.Fill(ntracks) #len(itrks))

			if abs(g4.PDG(ig4p)) == 13 : # mu^+/-
				hntrkpart_mu.Fill(ntracks) #len(itrks))

			if abs(g4.PDG(ig4p)) == 211 : # pi^+/-
				hntrkpart_pic.Fill(ntracks) #len(itrks))

			if abs(g4.PDG(ig4p)) == 11 : # e^+/-
				hntrkpart_e.Fill(ntracks)

		for ivtx in range(rec.NVertex()) :
			hntrkvtx.Fill(len(bt.VertexToTracks(ivtx)))

print('fraction of all tracks with multiple MCParticle matches: '
         + str( 1.0*(hng4p.Integral()-hng4p.GetBinContent(hng4p.FindBin(1.001)))/hng4p.Integral() ) )
                      

#style opts

hlength_bkd.SetLineColor(ROOT.kRed)
hlength_bkd.SetLineWidth(2)
hlength_fwd.SetLineWidth(2)

hmom_bkd.SetLineColor(ROOT.kRed)
hmom_bkd.SetLineWidth(2)
hmom_fwd.SetLineWidth(2)

hpdg_max.SetLineColor(ROOT.kRed)
hpdg_max.SetLineWidth(2)
hpdg.SetLineWidth(2)

hntrkpart_p.SetLineColor(ROOT.kRed)
hntrkpart_mu.SetLineColor(ROOT.kGreen-1)
hntrkpart_pic.SetLineColor(ROOT.kOrange)
hntrkpart_e.SetLineColor(ROOT.kMagenta)
hntrkpart_p.SetLineWidth(2)
hntrkpart_mu.SetLineWidth(2)
hntrkpart_pic.SetLineWidth(2)
hntrkpart.SetLineWidth(2)
hntrkpart_e.SetLineWidth(2)

hxdiff.SetLineWidth(2)
hydiff.SetLineWidth(2)
hzdiff.SetLineWidth(2)

hxdiff.SetLineColor(ROOT.kRed)
hzdiff.SetLineColor(ROOT.kGreen-2)

# draw our histogram and save it to file
clength = TCanvas()
hlength_fwd.Draw("ehist")	
hlength_bkd.Draw("same ehist")
clength.SaveAs('track-length.png')

cmom = TCanvas()
hmom_fwd.Draw("ehist")
hmom_bkd.Draw("same ehist")
cmom.SaveAs('reco_momentum.png')

cng4p = TCanvas()
hng4p.Draw()
cng4p.SaveAs('num_g4particles_per_track.png')

cg4mom = TCanvas()
hg4mom.Draw()


cg4mom1 = TCanvas()
hg4mom1.Draw()

cg4mom1_frac = TCanvas()
hg4mom1_frac.Draw()

cnmom1_frac = TCanvas()
hnmom1_frac.Draw("colz")

cmomres2d = TCanvas()
hmomres2d.Draw("colz")

cpdg = TCanvas()
hpdg.Draw()
hpdg_max.Draw("same")

#
ROOT.gStyle.SetOptStat(0)
hntrkpart.GetXaxis().SetNdivisions(10)
cntrkpart = TCanvas()
hntrkpart_p.Draw("ehist")
hntrkpart_mu.Draw("same ehist")
hntrkpart_pic.Draw("same ehist")
hntrkpart_e.Draw("same ehist")

leg = ROOT.TLegend(0.65,0.4,0.8,0.75)
leg.SetBorderSize(0)
leg.AddEntry("hntrkpart_p", "p", "L")
leg.AddEntry("hntrkpart_mu", "#mu^{#pm}", "L")
leg.AddEntry("hntrkpart_pic", "#pi^{#pm}", "L")
leg.AddEntry("hntrkpart_e",  "e^{#pm}", "L")
leg.Draw()
cntrkpart.Modified()
cntrkpart.SaveAs('track_ntracks_per_mcp.png')

cntrkpart.SetLogy()
cntrkpart.SaveAs('track_ntracks_per_mcp_logy.png')

ROOT.gStyle.SetOptStat(1)
cmomres_diff = TCanvas()
hmomres_diff.Draw()
cmomres_diff.SaveAs('momentum_res_diff.png')

cmomres_frac = TCanvas()
hmomres_frac.Draw()
cmomres_frac.SaveAs('momentum_res_frac.png')

#
hntrack.SetLineWidth(2)
hntrack.GetXaxis().SetNdivisions(10)
cntrack = TCanvas()
hntrack.Draw()
cntrack.SaveAs('track_ntrack_per_nu.png')

hnhit.GetXaxis().SetNdivisions(10)
cnhit = TCanvas()
hnhit.Draw()
cnhit.SaveAs('nhit_per_track.png')

cmomres2d_pval = TCanvas()
hmomres2d_pval.Draw("colz")

cg4mom_tot_pval = TCanvas()
hg4mom_tot_pval.Draw("colz")

cpdg_max_pval = TCanvas()
hpdg_max_pval.Draw("colz")

#
cposdiff = TCanvas()
hxdiff.GetYaxis().SetRangeUser(0,1.1*max((hxdiff.GetMaximum(),hydiff.GetMaximum(),hzdiff.GetMaximum())))
hxdiff.Draw()
hydiff.Draw("sames")
hzdiff.Draw("sames")

legdiff = ROOT.TLegend(0.2,0.6,0.35,0.85)
legdiff.SetBorderSize(0)
legdiff.AddEntry(hxdiff,"x","l")
legdiff.AddEntry(hydiff,"y","l")
legdiff.AddEntry(hzdiff,"z","l")
legdiff.Draw()

#
hpval.SetLineWidth(2)
cpval = TCanvas()
cpval.SetLogy()
hpval.Draw()
cpval.SaveAs('track_reco_pval.png')

#
cmomfracres2d_pval = TCanvas()
hmomres2d_frac_pval.Draw("colz")

#
hnvtx.GetXaxis().SetNdivisions(10)
cnvtx = TCanvas()
hnvtx.SetLineWidth(2)
hnvtx.Draw()
cnvtx.SaveAs('num_vertex_per_nu.png')

#
hnvtxtrk.GetXaxis().SetNdivisions(10)
cnvtxtrk = TCanvas()
hnvtxtrk.SetLineWidth(2)
hnvtxtrk.Draw()
cnvtxtrk.SaveAs('num_vertex_per_track.png')

#
hntrkvtx.GetXaxis().SetNdivisions(10)
cntrkvtx = TCanvas()
hntrkvtx.SetLineWidth(2)
hntrkvtx.Draw()
cnvtx.SaveAs('num_track_per_vertex.png')

#
hx0.SetLineWidth(2)
cx0 = TCanvas()
hx0.Draw()
cx0.SaveAs('reco_x0.png')

hy0.SetLineWidth(2)
cy0 = TCanvas()
hy0.Draw()
cy0.SaveAs('reco_y0.png')

hz0.SetLineWidth(2)
cz0 = TCanvas()
hz0.Draw()
cz0.SaveAs('reco_z0.png')

hr.SetLineWidth(2)
cr = TCanvas()
hr.Draw()
cr.SaveAs('reco_r.png')

hphi0.SetLineWidth(2)
cphi0 = TCanvas()
hphi0.Draw()
cphi0.SaveAs('reco_phi0.png')

hlambda.SetLineWidth(2)
clambda = TCanvas()
hlambda.Draw()
clambda.SaveAs('reco_lambda.png')

hdeltaphi.SetLineWidth(2)
cdeltaphi = TCanvas()
hdeltaphi.Draw()
cdeltaphi.SaveAs('reco_delta-phi.png')

hdeltaphilen.SetLineWidth(2)
cdeltaphilen = TCanvas()
hdeltaphilen.Draw()
cdeltaphilen.SaveAs('reco_delta-phi-per-length.png')

ROOT.gStyle.SetOptStat(0)
cntrkpart_vs_mom = TCanvas()
cntrkpart_vs_mom.SetLogz()
hntrkpart_vs_mom.Draw("colz")
prof = hntrkpart_vs_mom.ProfileX()
prof.SetLineWidth(2)
prof.SetLineColor(ROOT.kRed)
prof.Draw('same')

cntrkpart_vs_gyro = TCanvas()
cntrkpart_vs_gyro.SetLogz()
hntrkpart_vs_gyro.Draw("colz")
prof = hntrkpart_vs_gyro.ProfileX()
prof.SetLineWidth(2)
prof.SetLineColor(ROOT.kRed)
prof.Draw('same')

# end draw plots
########################################################################
# ask for user input as a way to keep the program from ending so we can
# see the histogram.
# python doesn't like empty input strings so I abuse exception handling
try:
	null = input("press <Enter> to close canvas and exit program.") 

except:
	null = 'null'

