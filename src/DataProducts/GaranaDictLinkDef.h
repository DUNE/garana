#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclasses;

#pragma link C++ class std::vector<std::vector<Int_t>>+;
#pragma link C++ class std::vector<std::vector<Double_t>>+;
#pragma link C++ class std::vector<std::vector<std::vector<Double_t>>>+;

#pragma link C++ class garana::GTruth+;
#pragma link C++ class std::vector<garana::GTruth>+;
#pragma link C++ class garana::FSParticle+;
#pragma link C++ class std::vector<garana::FSParticle>+;
#pragma link C++ class std::vector<std::vector<garana::FSParticle>>+;

#endif
