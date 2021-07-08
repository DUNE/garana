import garanainit # loads garana libs
import ROOT #load ROOT libs
from ROOT import TCanvas
from ROOT import TH1F
from ROOT import TH2F
from ROOT import TMath
from ROOT import TEfficiency

def trackmatch():

	garanainit.init()
	#ROOT.gROOT.SetBatch(True) # run in batch mode (don't display plots)
	
	tm = ROOT.TreeManager("./test.root") #structuredtree.root")
	
	# truth matching utility
	bt = ROOT.Backtracker(tm);
	
	print("constructed treemanager")
	
	#tree accessors
	#gen = tm.GetGenTree()
	g4  = tm.GetG4Tree()
	rec = tm.GetRecoTree()

	nmatch = 0 # number of reco tracks matched to a G4Particle
	ntrack = 0 # number of reco tracks
	nprimary = 0 # true number of primaries
	nprimary_match = 0 #number of primaries matched to at least one track

	hg4_nmatch = TH1F('hg4_nmatch','G4Particle -> Track matching;N^{0} matches',10,0,10)

	hfrac = TH1F("hfrac","particle contributing most energy;fraction of total",50,0,1.1)
	hncont = TH1F("hncont","particles contributing energy;N^{0} particles",10,0,10)
	hncontfrac = TH2F('hncontfrac','particles contributing energy;N^{0} particles;max fraction of total',10,0,25,0,1.1)

	eff_g4match = TEfficiency('eff_g4match','G4Particle -> Track matching; initial energy [GeV]; efficiency',10,0,5)

        # loop over events
	for ientry in range(rec.NEntries()):

		if ientry%100 == 0 : print('processing event '+str(ientry))
		
		tm.GetEntry(ientry)
		bt.FillMaps()      #load associations for this entry

		#nprimary += g4.NPrimary()
		for ig4 in range(g4.NSim()):
			if not g4.IsPrimary(ig4) : continue # only consider primaries
			if not abs(g4.PDG(ig4)) == 2212 : continue # muons only
			nprimary += 1
			if bt.G4ParticleToTracks(ig4).size() > 0 : nprimary_match += 1 # matched to something?
			hg4_nmatch.Fill(bt.G4ParticleToTracks(ig4).size())
			eff_g4match.Fill(bt.G4ParticleToTracks(ig4).size() > 0, g4.SimMomEnter(ig4,0).E())

		ntrack += rec.NTrack()
		for itrack in range(rec.NTrack()):
               
			imatch = bt.TrackToG4Particle(itrack);
			if imatch < g4.NSim(): nmatch += 1

			#imatches = bt.TrackToG4Particles(itrack)
			hncont.Fill(rec.TrackNTrueTrack(itrack)) #len(imatches))
			for ip in range(rec.TrackNTrueTrack(itrack)):
				hfrac.Fill(rec.TrackMaxDepositFrac(itrack))
				hncontfrac.Fill(rec.TrackNTrueTrack(itrack),rec.TrackMaxDepositFrac(itrack))

	if nprimary != 0 :
		print('number of primaries found: ',nprimary)
		print('number of matched primaries: ',nprimary_match)
		print('g4particle -> track matching efficiency: ',1.0*nprimary_match/nprimary)
	else : print('no G4particles found!')

	if ntrack != 0 :print('track -> g4particle matching efficiency: ',1.0*nmatch/ntrack)
	else : print('no tracks found!')

	print('hncont size is ',hncont.Integral())
	print('hfrac size is ',hfrac.Integral())

	cg4_nmatch = TCanvas()
	hg4_nmatch.Draw()
	cg4_nmatch.SaveAs('g4_nmatch.png')

	cncont = TCanvas()
	hncont.Draw()
	cncont.SaveAs('ncont.png')

	cfrac = TCanvas()
	hfrac.Draw()
	cfrac.SaveAs('frac.png')

	cncontfrac = TCanvas()
	hncontfrac.Draw()
	cncontfrac.SaveAs('ncont_v_frac.png')

	ceff_g4match = TCanvas()
	eff_g4match.Draw()
	ceff_g4match.SaveAs('g4match_eff.png')

	# ask for user input as a way to keep the program from ending so we can
	# see the histogram.
	# python doesn't like empty input strings so I abuse exception handling
	try:
		null = input("press <Enter> to close canvas and exit program.")
	
	except:
		null = 'null'

#execute as a script
if __name__ == '__main__':
    trackmatch()
