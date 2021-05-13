#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclasses;

#pragma link C++ class std::vector<std::vector<UInt_t>>+;
#pragma link C++ class std::vector<std::vector<Int_t>>+;
#pragma link C++ class std::vector<std::vector<Double_t>>+;
#pragma link C++ class std::vector<std::vector<std::vector<Double_t>>>+;
#pragma link C++ class std::vector<TLorentzVector>+;
#pragma link C++ class std::vector<pair<UInt_t,TLorentzVector>>+;

#pragma link C++ class garana::GTruth+;
#pragma link C++ class std::vector<garana::GTruth>+;

#pragma link C++ class garana::FSParticle+;
#pragma link C++ class std::vector<garana::FSParticle>+;
#pragma link C++ class std::vector<std::vector<garana::FSParticle>>+;

#pragma link C++ class garana::G4Particle+;
#pragma link C++ class std::vector<garana::G4Particle>+;
//#pragma link C++ class std::vector<std::vector<garana::G4Particle>>+;

#pragma link C++ class garana::Track+;
#pragma link C++ class std::vector<garana::Track>+;

#pragma link C++ class garana::Vertex+;
#pragma link C++ class std::vector<garana::Vertex>+;

#pragma link C++ class garana::Vee+;
#pragma link C++ class std::vector<garana::Vee>+;

#pragma link C++ class garana::CaloCluster+;
#pragma link C++ class std::vector<garana::CaloCluster>+;

#endif
