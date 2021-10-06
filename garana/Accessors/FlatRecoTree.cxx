/*
 * FlatRecoTree.cxx
 *
 *  Created on: Feb 9, 2021
 *      Author: chilgenb
 */

#include "garana/Accessors/FlatRecoTree.h"
#include <utility>

using namespace std; //::vector;
using namespace garana;

FlatRecoTree::FlatRecoTree(TTree* tree)
{
    SetupRead(tree);
}

FlatRecoTree::FlatRecoTree(TTree* tree, char opt)
{
	CheckOpt(opt);//sets TreeReader::fOpt

    if(fOpt=='r'){
    	std::cout << "constructed FlatRecoTree object in read-only mode" << std::endl;
    	SetupRead(tree);
    	SetBranchAddresses();
    }
    else {
    	std::cout << "constructed FlatRecoTree object in write mode" << std::endl;
    	fTreeIn = tree;
    	SetBranchAddresses();
    	SetVecs();
    }

}

bool FlatRecoTree::SetBranchAddresses(){

std::cout << "FlatRecoTree SetBranchAddresses()" << std::endl;

	if(fOpt=='r'){
		fTreeIn->SetBranchAddress("Event",               &fEvent,               &b_Event              );
		fTreeIn->SetBranchAddress("TrkLenFwd",           &fTrkLenFwd,           &b_TrkLenFwd          );
		fTreeIn->SetBranchAddress("TrkLenBac",           &fTrkLenBac,           &b_TrkLenBac          );
		fTreeIn->SetBranchAddress("TrkMomBeg",           &fTrkMomBeg,           &b_TrkMomBeg          );
		fTreeIn->SetBranchAddress("TrkMomEnd",           &fTrkMomEnd,           &b_TrkMomEnd          );
		fTreeIn->SetBranchAddress("TrkVtxX",             &fTrkVtxX,             &b_TrkVtxX            );
		fTreeIn->SetBranchAddress("TrkVtxY",             &fTrkVtxY,             &b_TrkVtxY            );
		fTreeIn->SetBranchAddress("TrkVtxZ",             &fTrkVtxZ,             &b_TrkVtxZ            );
		fTreeIn->SetBranchAddress("TrkVtxT",             &fTrkVtxT,             &b_TrkVtxT            );
		fTreeIn->SetBranchAddress("TrkEndX",             &fTrkEndX,             &b_TrkEndX            );
		fTreeIn->SetBranchAddress("TrkEndY",             &fTrkEndY,             &b_TrkEndY            );
		fTreeIn->SetBranchAddress("TrkEndZ",             &fTrkEndZ,             &b_TrkEndZ            );
		fTreeIn->SetBranchAddress("TrkEndT",             &fTrkEndT,             &b_TrkEndT            );

		fTreeIn->SetBranchAddress("TrkVtxDirX",          &fTrkVtxDirX,          &b_TrkVtxDirX         );
		fTreeIn->SetBranchAddress("TrkVtxDirY",          &fTrkVtxDirY,          &b_TrkVtxDirY         );
		fTreeIn->SetBranchAddress("TrkVtxDirZ",          &fTrkVtxDirZ,          &b_TrkVtxDirZ         );
		fTreeIn->SetBranchAddress("TrkEndDirX",          &fTrkEndDirX,          &b_TrkEndDirX         );
		fTreeIn->SetBranchAddress("TrkEndDirY",          &fTrkEndDirY,          &b_TrkEndDirY         );
		fTreeIn->SetBranchAddress("TrkEndDirZ",          &fTrkEndDirZ,          &b_TrkEndDirZ         );
		fTreeIn->SetBranchAddress("TrkChiFwd",           &fTrkChiFwd,           &b_TrkChiFwd          );
		fTreeIn->SetBranchAddress("TrkChiBac",           &fTrkChiBac,           &b_TrkChiBac          );
		fTreeIn->SetBranchAddress("TrkNHits",            &fTrkNHits,            &b_TrkNHits           );

		fTreeIn->SetBranchAddress("TrackXBeg",           &fTrackXBeg,           &b_TrackXBeg          );
		fTreeIn->SetBranchAddress("TrackYBeg",           &fTrackYBeg,           &b_TrackYBeg          );
		fTreeIn->SetBranchAddress("TrackZBeg",           &fTrackZBeg,           &b_TrackZBeg          );
		fTreeIn->SetBranchAddress("TrackCurvBeg",        &fTrackCurvBeg,        &b_TrackCurvBeg       );
		fTreeIn->SetBranchAddress("TrackPhiBeg",         &fTrackPhiBeg,         &b_TrackPhiBeg        );
		fTreeIn->SetBranchAddress("TrackLambBeg",        &fTrackLambBeg,        &b_TrackLambBeg       );
		fTreeIn->SetBranchAddress("TrackXEnd",           &fTrackXEnd,           &b_TrackXEnd          );
		fTreeIn->SetBranchAddress("TrackYEnd",           &fTrackYEnd,           &b_TrackYEnd          );
		fTreeIn->SetBranchAddress("TrackZEnd",           &fTrackZEnd,           &b_TrackZEnd          );
		fTreeIn->SetBranchAddress("TrackCurvEnd",        &fTrackCurvEnd,        &b_TrackCurvEnd       );
		fTreeIn->SetBranchAddress("TrackPhiEnd ",        &fTrackPhiEnd ,        &b_TrackPhiEnd        );
		fTreeIn->SetBranchAddress("TrackLambEnd",        &fTrackLambEnd,        &b_TrackLambEnd       );
		fTreeIn->SetBranchAddress("TrkCovMat1Beg",       &fTrkCovMat1Beg,       &b_TrkCovMat1Beg      );
		fTreeIn->SetBranchAddress("TrkCovMat2Beg",       &fTrkCovMat2Beg,       &b_TrkCovMat2Beg      );
		fTreeIn->SetBranchAddress("TrkCovMat3Beg",       &fTrkCovMat3Beg,       &b_TrkCovMat3Beg      );
		fTreeIn->SetBranchAddress("TrkCovMat4Beg",       &fTrkCovMat4Beg,       &b_TrkCovMat4Beg      );
		fTreeIn->SetBranchAddress("TrkCovMat5Beg",       &fTrkCovMat5Beg,       &b_TrkCovMat5Beg      );
		fTreeIn->SetBranchAddress("TrkCovMat6Beg",       &fTrkCovMat6Beg,       &b_TrkCovMat6Beg      );
		fTreeIn->SetBranchAddress("TrkCovMat7Beg",       &fTrkCovMat7Beg,       &b_TrkCovMat7Beg      );
		fTreeIn->SetBranchAddress("TrkCovMat8Beg",       &fTrkCovMat8Beg,       &b_TrkCovMat8Beg      );
		fTreeIn->SetBranchAddress("TrkCovMat9Beg",       &fTrkCovMat9Beg,       &b_TrkCovMat9Beg      );
		fTreeIn->SetBranchAddress("TrkCovMat10Beg",      &fTrkCovMat10Beg,      &b_TrkCovMat10Beg     );
		fTreeIn->SetBranchAddress("TrkCovMat11Beg",      &fTrkCovMat11Beg,      &b_TrkCovMat11Beg     );
		fTreeIn->SetBranchAddress("TrkCovMat12Beg",      &fTrkCovMat12Beg,      &b_TrkCovMat12Beg     );
		fTreeIn->SetBranchAddress("TrkCovMat13Beg",      &fTrkCovMat13Beg,      &b_TrkCovMat13Beg     );
		fTreeIn->SetBranchAddress("TrkCovMat14Beg",      &fTrkCovMat14Beg,      &b_TrkCovMat14Beg     );
		fTreeIn->SetBranchAddress("TrkCovMat15Beg",      &fTrkCovMat15Beg,      &b_TrkCovMat15Beg     );
		fTreeIn->SetBranchAddress("TrkCovMat1End",       &fTrkCovMat1End,       &b_TrkCovMat1End      );
		fTreeIn->SetBranchAddress("TrkCovMat2End",       &fTrkCovMat2End,       &b_TrkCovMat2End      );
		fTreeIn->SetBranchAddress("TrkCovMat3End",       &fTrkCovMat3End,       &b_TrkCovMat3End      );
		fTreeIn->SetBranchAddress("TrkCovMat4End",       &fTrkCovMat4End,       &b_TrkCovMat4End      );
		fTreeIn->SetBranchAddress("TrkCovMat5End",       &fTrkCovMat5End,       &b_TrkCovMat5End      );
		fTreeIn->SetBranchAddress("TrkCovMat6End",       &fTrkCovMat6End,       &b_TrkCovMat6End      );
		fTreeIn->SetBranchAddress("TrkCovMat7End",       &fTrkCovMat7End,       &b_TrkCovMat7End      );
		fTreeIn->SetBranchAddress("TrkCovMat8End",       &fTrkCovMat8End,       &b_TrkCovMat8End      );
		fTreeIn->SetBranchAddress("TrkCovMat9End",       &fTrkCovMat9End,       &b_TrkCovMat9End      );
		fTreeIn->SetBranchAddress("TrkCovMat10End",      &fTrkCovMat10End,      &b_TrkCovMat10End     );
		fTreeIn->SetBranchAddress("TrkCovMat11End",      &fTrkCovMat11End,      &b_TrkCovMat11End     );
		fTreeIn->SetBranchAddress("TrkCovMat12End",      &fTrkCovMat12End,      &b_TrkCovMat12End     );
		fTreeIn->SetBranchAddress("TrkCovMat13End",      &fTrkCovMat13End,      &b_TrkCovMat13End     );
		fTreeIn->SetBranchAddress("TrkCovMat14End",      &fTrkCovMat14End,      &b_TrkCovMat14End     );
		fTreeIn->SetBranchAddress("TrkCovMat15End",      &fTrkCovMat15End,      &b_TrkCovMat15End     );

		fTreeIn->SetBranchAddress("TrkIonizFwd",         &fTrkIonizFwd,         &b_TrkIonizFwd        );
		fTreeIn->SetBranchAddress("TrkIonizBac",         &fTrkIonizBac,         &b_TrkIonizBac        );
		fTreeIn->SetBranchAddress("TrkChgFwd",           &fTrkChgFwd,           &b_TrkChgFwd          );
		fTreeIn->SetBranchAddress("TrkChgBac",           &fTrkChgBac,           &b_TrkChgBac          );

		fTreeIn->SetBranchAddress("VeeVtxX",             &fVeeVtxX,             &b_VeeVtxX            );
		fTreeIn->SetBranchAddress("VeeVtxY",             &fVeeVtxY,             &b_VeeVtxY            );
		fTreeIn->SetBranchAddress("VeeVtxZ",             &fVeeVtxZ,             &b_VeeVtxZ            );
		fTreeIn->SetBranchAddress("VeeVtxT",             &fVeeVtxT,             &b_VeeVtxT            );
		fTreeIn->SetBranchAddress("VeeVtxCovar11",       &fVeeVtxCovar11,       &b_VeeVtxCovar11      );
		fTreeIn->SetBranchAddress("VeeVtxCovar12",       &fVeeVtxCovar12,       &b_VeeVtxCovar12      );
		fTreeIn->SetBranchAddress("VeeVtxCovar13",       &fVeeVtxCovar13,       &b_VeeVtxCovar13      );
		fTreeIn->SetBranchAddress("VeeVtxCovar21",       &fVeeVtxCovar21,       &b_VeeVtxCovar21      );
		fTreeIn->SetBranchAddress("VeeVtxCovar22",       &fVeeVtxCovar22,       &b_VeeVtxCovar22      );
		fTreeIn->SetBranchAddress("VeeVtxCovar23",       &fVeeVtxCovar23,       &b_VeeVtxCovar23      );
		fTreeIn->SetBranchAddress("VeeVtxCovar31",       &fVeeVtxCovar31,       &b_VeeVtxCovar31      );
		fTreeIn->SetBranchAddress("VeeVtxCovar32",       &fVeeVtxCovar32,       &b_VeeVtxCovar32      );
		fTreeIn->SetBranchAddress("VeeVtxCovar33",       &fVeeVtxCovar33,       &b_VeeVtxCovar33      );

		fTreeIn->SetBranchAddress("VeePxKshort",         &fVeePxKshort,         &b_VeePxKshort        );
		fTreeIn->SetBranchAddress("VeePyKshort",         &fVeePyKshort,         &b_VeePyKshort        );
		fTreeIn->SetBranchAddress("VeePzKshort",         &fVeePzKshort,         &b_VeePzKshort        );
		fTreeIn->SetBranchAddress("VeeEKshort",          &fVeeEKshort,          &b_VeeEKshort         );
		fTreeIn->SetBranchAddress("VeePxLamb1",          &fVeePxLamb1,          &b_VeePxLamb1         );
		fTreeIn->SetBranchAddress("VeePyLamb1",          &fVeePyLamb1,          &b_VeePyLamb1         );
		fTreeIn->SetBranchAddress("VeePzLamb1",          &fVeePzLamb1,          &b_VeePzLamb1         );
		fTreeIn->SetBranchAddress("VeeELamb1",           &fVeeELamb1,           &b_VeeELamb1          );
		fTreeIn->SetBranchAddress("VeePxLamb2",          &fVeePxLamb2,          &b_VeePxLamb2         );
		fTreeIn->SetBranchAddress("VeePyLamb2",          &fVeePyLamb2,          &b_VeePyLamb2         );
		fTreeIn->SetBranchAddress("VeePzLamb2",          &fVeePzLamb2,          &b_VeePzLamb2         );
		fTreeIn->SetBranchAddress("VeeELamb2",           &fVeeELamb2,           &b_VeeELamb2          );
		fTreeIn->SetBranchAddress("VeeChisqr",           &fVeeChisqr,           &b_VeeChisqr          );

		fTreeIn->SetBranchAddress("VtxX",                &fVtxX,                &b_VtxX               );
		fTreeIn->SetBranchAddress("VtxY",                &fVtxY,                &b_VtxY               );
		fTreeIn->SetBranchAddress("VtxZ",                &fVtxZ,                &b_VtxZ               );
		fTreeIn->SetBranchAddress("VtxT",                &fVtxT,                &b_VtxT               );
		fTreeIn->SetBranchAddress("VtxCovar11",          &fVtxCovar11,          &b_VtxCovar11         );
		fTreeIn->SetBranchAddress("VtxCovar12",          &fVtxCovar12,          &b_VtxCovar12         );
		fTreeIn->SetBranchAddress("VtxCovar13",          &fVtxCovar13,          &b_VtxCovar13         );
		fTreeIn->SetBranchAddress("VtxCovar21",          &fVtxCovar21,          &b_VtxCovar21         );
		fTreeIn->SetBranchAddress("VtxCovar22",          &fVtxCovar22,          &b_VtxCovar22         );
		fTreeIn->SetBranchAddress("VtxCovar23",          &fVtxCovar23,          &b_VtxCovar23         );
		fTreeIn->SetBranchAddress("VtxCovar31",          &fVtxCovar31,          &b_VtxCovar31         );
		fTreeIn->SetBranchAddress("VtxCovar32",          &fVtxCovar32,          &b_VtxCovar32         );
		fTreeIn->SetBranchAddress("VtxCovar33",          &fVtxCovar33,          &b_VtxCovar33         );

		fTreeIn->SetBranchAddress("CalClustX",           &fCalClustX,           &b_CalClustX          );
		fTreeIn->SetBranchAddress("CalClustY",           &fCalClustY,           &b_CalClustY          );
		fTreeIn->SetBranchAddress("CalClustZ",           &fCalClustZ,           &b_CalClustZ          );
		fTreeIn->SetBranchAddress("CalClustT",           &fCalClustT,           &b_CalClustT          );
		fTreeIn->SetBranchAddress("CalClustEnergy",      &fCalClustEnergy,      &b_CalClustEnergy     );
		fTreeIn->SetBranchAddress("CalClustEnergyError", &fCalClustEnergyError, &b_CalClustEnergyError);
		fTreeIn->SetBranchAddress("CalClustTdiff",       &fCalClustTdiff,       &b_CalClustTdiff      );
		fTreeIn->SetBranchAddress("CalClustEllip",       &fCalClustEllip,       &b_CalClustEllip      );
		fTreeIn->SetBranchAddress("CalClustR1",          &fCalClustR1,          &b_CalClustR1         );
		fTreeIn->SetBranchAddress("CalClustR2",          &fCalClustR2,          &b_CalClustR2         );
		fTreeIn->SetBranchAddress("CalClustR3",          &fCalClustR3,          &b_CalClustR3         );
		fTreeIn->SetBranchAddress("CalClustVol",         &fCalClustVol,         &b_CalClustVol        );
		fTreeIn->SetBranchAddress("CalClustWidth",       &fCalClustWidth,       &b_CalClustWidth      );
		fTreeIn->SetBranchAddress("CalClustTheta",       &fCalClustTheta,       &b_CalClustTheta      );
		fTreeIn->SetBranchAddress("CalClustPhi",         &fCalClustPhi,         &b_CalClustPhi        );
		fTreeIn->SetBranchAddress("CalClustEigen1X",     &fCalClustEigen1X,     &b_CalClustEigen1X    );
		fTreeIn->SetBranchAddress("CalClustEigen1Y",     &fCalClustEigen1Y,     &b_CalClustEigen1Y    );
		fTreeIn->SetBranchAddress("CalClustEigen1Z",     &fCalClustEigen1Z,     &b_CalClustEigen1Z    );
		fTreeIn->SetBranchAddress("CalClustEigen2X",     &fCalClustEigen2X,     &b_CalClustEigen2X    );
		fTreeIn->SetBranchAddress("CalClustEigen2Y",     &fCalClustEigen2Y,     &b_CalClustEigen2Y    );
		fTreeIn->SetBranchAddress("CalClustEigen2Z",     &fCalClustEigen2Z,     &b_CalClustEigen2Z    );
		fTreeIn->SetBranchAddress("CalClustEigen3X",     &fCalClustEigen3X,     &b_CalClustEigen3X    );
		fTreeIn->SetBranchAddress("CalClustEigen3Y",     &fCalClustEigen3Y,     &b_CalClustEigen3Y    );
		fTreeIn->SetBranchAddress("CalClustEigen3Z",     &fCalClustEigen3Z,     &b_CalClustEigen3Z    );

		fTreeIn->SetBranchAddress("TrackG4PIndices ",    &fTrackG4PIndices,     &b_TrackG4PIndices    );
		fTreeIn->SetBranchAddress("VertTrackIndices",    &fVertTrackIndices,    &b_VertTrackIndices   );
		fTreeIn->SetBranchAddress("VeeTrackIndices ",    &fVeeTrackIndices,     &b_VeeTrackIndices    );
		//fTreeIn->SetBranchAddress("CalTrackIndices ",    &fCalTrackIndices,     &b_CalTrackIndices    );
	    fTreeIn->SetBranchAddress("CalTrackIndices",  &fCalClusterTrackIndices , &b_CalClusterTrackIndices );
	    //fTreeIn->SetBranchAddress("CalTrackEnds",     &fCalTrackEnds    , &b_CalTrackEnds    );
	    fTreeIn->SetBranchAddress("CalG4Indices",     &fCalClusterG4Indices ,    &b_CalClusterG4Indices    );

		fTreeIn->SetBranchAddress("VertTrackEnds",       &fVertTrackEnds,       &b_VertTrackEnds      );
		fTreeIn->SetBranchAddress("VeeTrackEnds",        &fVeeTrackEnds,        &b_VeeTrackEnds       );

	}


	if(fOpt=='w'){

		fTreeIn->Branch("Event",               &fEvent,                  "Event/I"            );
		fTreeIn->Branch("TrkLenFwd",           "vector<float>",          &fTrkLenFwd          );
		fTreeIn->Branch("TrkLenBac",           "vector<float>",          &fTrkLenBac          );
		fTreeIn->Branch("TrkMomBeg",           "vector<float>",          &fTrkMomBeg          );
		fTreeIn->Branch("TrkMomEnd",           "vector<float>",          &fTrkMomEnd          );
		fTreeIn->Branch("TrkVtxX",             "vector<float>",          &fTrkVtxX            );
		fTreeIn->Branch("TrkVtxY",             "vector<float>",          &fTrkVtxY            );
		fTreeIn->Branch("TrkVtxZ",             "vector<float>",          &fTrkVtxZ            );
		fTreeIn->Branch("TrkVtxT",             "vector<float>",          &fTrkVtxT            );
		fTreeIn->Branch("TrkEndX",             "vector<float>",          &fTrkEndX            );
		fTreeIn->Branch("TrkEndY",             "vector<float>",          &fTrkEndY            );
		fTreeIn->Branch("TrkEndZ",             "vector<float>",          &fTrkEndZ            );
		fTreeIn->Branch("TrkEndT",             "vector<float>",          &fTrkEndT            );

		fTreeIn->Branch("TrkVtxDirX",          "vector<float>",          &fTrkVtxDirX         );
		fTreeIn->Branch("TrkVtxDirY",          "vector<float>",          &fTrkVtxDirY         );
		fTreeIn->Branch("TrkVtxDirZ",          "vector<float>",          &fTrkVtxDirZ         );
		fTreeIn->Branch("TrkEndDirX",          "vector<float>",          &fTrkEndDirX         );
		fTreeIn->Branch("TrkEndDirY",          "vector<float>",          &fTrkEndDirY         );
		fTreeIn->Branch("TrkEndDirZ",          "vector<float>",          &fTrkEndDirZ         );
		fTreeIn->Branch("TrkChiFwd",           "vector<float>",          &fTrkChiFwd          );
		fTreeIn->Branch("TrkChiBac",           "vector<float>",          &fTrkChiBac          );
		fTreeIn->Branch("TrkNHits",            "vector<size_t>",         &fTrkNHits           );

		fTreeIn->Branch("TrackXBeg",           "vector<float>",          &fTrackXBeg          );
		fTreeIn->Branch("TrackYBeg",           "vector<float>",          &fTrackYBeg          );
		fTreeIn->Branch("TrackZBeg",           "vector<float>",          &fTrackZBeg          );
		fTreeIn->Branch("TrackCurvBeg",        "vector<float>",          &fTrackCurvBeg       );
		fTreeIn->Branch("TrackPhiBeg",         "vector<float>",          &fTrackPhiBeg        );
		fTreeIn->Branch("TrackLambBeg",        "vector<float>",          &fTrackLambBeg       );
		fTreeIn->Branch("TrackXEnd",           "vector<float>",          &fTrackXEnd          );
		fTreeIn->Branch("TrackYEnd",           "vector<float>",          &fTrackYEnd          );
		fTreeIn->Branch("TrackZEnd",           "vector<float>",          &fTrackZEnd          );
		fTreeIn->Branch("TrackCurvEnd",        "vector<float>",          &fTrackCurvEnd       );
		fTreeIn->Branch("TrackPhiEnd ",        "vector<float>",          &fTrackPhiEnd        );
		fTreeIn->Branch("TrackLambEnd",        "vector<float>",          &fTrackLambEnd       );
		fTreeIn->Branch("TrkCovMat1Beg",       "vector<float>",          &fTrkCovMat1Beg      );
		fTreeIn->Branch("TrkCovMat2Beg",       "vector<float>",          &fTrkCovMat2Beg      );
		fTreeIn->Branch("TrkCovMat3Beg",       "vector<float>",          &fTrkCovMat3Beg      );
		fTreeIn->Branch("TrkCovMat4Beg",       "vector<float>",          &fTrkCovMat4Beg      );
		fTreeIn->Branch("TrkCovMat5Beg",       "vector<float>",          &fTrkCovMat5Beg      );
		fTreeIn->Branch("TrkCovMat6Beg",       "vector<float>",          &fTrkCovMat6Beg      );
		fTreeIn->Branch("TrkCovMat7Beg",       "vector<float>",          &fTrkCovMat7Beg      );
		fTreeIn->Branch("TrkCovMat8Beg",       "vector<float>",          &fTrkCovMat8Beg      );
		fTreeIn->Branch("TrkCovMat9Beg",       "vector<float>",          &fTrkCovMat9Beg      );
		fTreeIn->Branch("TrkCovMat10Beg",      "vector<float>",          &fTrkCovMat10Beg     );
		fTreeIn->Branch("TrkCovMat11Beg",      "vector<float>",          &fTrkCovMat11Beg     );
		fTreeIn->Branch("TrkCovMat12Beg",      "vector<float>",          &fTrkCovMat12Beg     );
		fTreeIn->Branch("TrkCovMat13Beg",      "vector<float>",          &fTrkCovMat13Beg     );
		fTreeIn->Branch("TrkCovMat14Beg",      "vector<float>",          &fTrkCovMat14Beg     );
		fTreeIn->Branch("TrkCovMat15Beg",      "vector<float>",          &fTrkCovMat15Beg     );
		fTreeIn->Branch("TrkCovMat1End",       "vector<float>",          &fTrkCovMat1End      );
		fTreeIn->Branch("TrkCovMat2End",       "vector<float>",          &fTrkCovMat2End      );
		fTreeIn->Branch("TrkCovMat3End",       "vector<float>",          &fTrkCovMat3End      );
		fTreeIn->Branch("TrkCovMat4End",       "vector<float>",          &fTrkCovMat4End      );
		fTreeIn->Branch("TrkCovMat5End",       "vector<float>",          &fTrkCovMat5End      );
		fTreeIn->Branch("TrkCovMat6End",       "vector<float>",          &fTrkCovMat6End      );
		fTreeIn->Branch("TrkCovMat7End",       "vector<float>",          &fTrkCovMat7End      );
		fTreeIn->Branch("TrkCovMat8End",       "vector<float>",          &fTrkCovMat8End      );
		fTreeIn->Branch("TrkCovMat9End",       "vector<float>",          &fTrkCovMat9End      );
		fTreeIn->Branch("TrkCovMat10End",      "vector<float>",          &fTrkCovMat10End     );
		fTreeIn->Branch("TrkCovMat11End",      "vector<float>",          &fTrkCovMat11End     );
		fTreeIn->Branch("TrkCovMat12End",      "vector<float>",          &fTrkCovMat12End     );
		fTreeIn->Branch("TrkCovMat13End",      "vector<float>",          &fTrkCovMat13End     );
		fTreeIn->Branch("TrkCovMat14End",      "vector<float>",          &fTrkCovMat14End     );
		fTreeIn->Branch("TrkCovMat15End",      "vector<float>",          &fTrkCovMat15End     );

		fTreeIn->Branch("TrkIonizFwd",         "vector<UInt_t>",         &fTrkIonizFwd        );
		fTreeIn->Branch("TrkIonizBac",         "vector<UInt_t>",         &fTrkIonizBac        );
		fTreeIn->Branch("TrkChgFwd",           "vector<UInt_t>",         &fTrkChgFwd          );
		fTreeIn->Branch("TrkChgBac",           "vector<UInt_t>",         &fTrkChgBac          );

		fTreeIn->Branch("VeeVtxX",             "vector<float>",          &fVeeVtxX            );
		fTreeIn->Branch("VeeVtxY",             "vector<float>",          &fVeeVtxY            );
		fTreeIn->Branch("VeeVtxZ",             "vector<float>",          &fVeeVtxZ            );
		fTreeIn->Branch("VeeVtxT",             "vector<float>",          &fVeeVtxT            );
		fTreeIn->Branch("VeeVtxCovar11",       "vector<float>",          &fVeeVtxCovar11      );
		fTreeIn->Branch("VeeVtxCovar12",       "vector<float>",          &fVeeVtxCovar12      );
		fTreeIn->Branch("VeeVtxCovar13",       "vector<float>",          &fVeeVtxCovar13      );
		fTreeIn->Branch("VeeVtxCovar21",       "vector<float>",          &fVeeVtxCovar21      );
		fTreeIn->Branch("VeeVtxCovar22",       "vector<float>",          &fVeeVtxCovar22      );
		fTreeIn->Branch("VeeVtxCovar23",       "vector<float>",          &fVeeVtxCovar23      );
		fTreeIn->Branch("VeeVtxCovar31",       "vector<float>",          &fVeeVtxCovar31      );
		fTreeIn->Branch("VeeVtxCovar32",       "vector<float>",          &fVeeVtxCovar32      );
		fTreeIn->Branch("VeeVtxCovar33",       "vector<float>",          &fVeeVtxCovar33      );

		fTreeIn->Branch("VeePxKshort",         "vector<float>",          &fVeePxKshort        );
		fTreeIn->Branch("VeePyKshort",         "vector<float>",          &fVeePyKshort        );
		fTreeIn->Branch("VeePzKshort",         "vector<float>",          &fVeePzKshort        );
		fTreeIn->Branch("VeeEKshort",          "vector<float>",          &fVeeEKshort         );
		fTreeIn->Branch("VeePxLamb1",          "vector<float>",          &fVeePxLamb1         );
		fTreeIn->Branch("VeePyLamb1",          "vector<float>",          &fVeePyLamb1         );
		fTreeIn->Branch("VeePzLamb1",          "vector<float>",          &fVeePzLamb1         );
		fTreeIn->Branch("VeeELamb1",           "vector<float>",          &fVeeELamb1          );
		fTreeIn->Branch("VeePxLamb2",          "vector<float>",          &fVeePxLamb2         );
		fTreeIn->Branch("VeePyLamb2",          "vector<float>",          &fVeePyLamb2         );
		fTreeIn->Branch("VeePzLamb2",          "vector<float>",          &fVeePzLamb2         );
		fTreeIn->Branch("VeeELamb2",           "vector<float>",          &fVeeELamb2          );
		fTreeIn->Branch("VeeChisqr",           "vector<float>",          &fVeeChisqr          );

		fTreeIn->Branch("VtxX",                "vector<float>",          &fVtxX               );
		fTreeIn->Branch("VtxY",                "vector<float>",          &fVtxY               );
		fTreeIn->Branch("VtxZ",                "vector<float>",          &fVtxZ               );
		fTreeIn->Branch("VtxT",                "vector<float>",          &fVtxT               );
		fTreeIn->Branch("VtxCovar11",          "vector<float>",          &fVtxCovar11         );
		fTreeIn->Branch("VtxCovar12",          "vector<float>",          &fVtxCovar12         );
		fTreeIn->Branch("VtxCovar13",          "vector<float>",          &fVtxCovar13         );
		fTreeIn->Branch("VtxCovar21",          "vector<float>",          &fVtxCovar21         );
		fTreeIn->Branch("VtxCovar22",          "vector<float>",          &fVtxCovar22         );
		fTreeIn->Branch("VtxCovar23",          "vector<float>",          &fVtxCovar23         );
		fTreeIn->Branch("VtxCovar31",          "vector<float>",          &fVtxCovar31         );
		fTreeIn->Branch("VtxCovar32",          "vector<float>",          &fVtxCovar32         );
		fTreeIn->Branch("VtxCovar33",          "vector<float>",          &fVtxCovar33         );

		fTreeIn->Branch("CalClustX",           "vector<float>",          &fCalClustX          );
		fTreeIn->Branch("CalClustY",           "vector<float>",          &fCalClustY          );
		fTreeIn->Branch("CalClustZ",           "vector<float>",          &fCalClustZ          );
		fTreeIn->Branch("CalClustT",           "vector<float>",          &fCalClustT          );
		fTreeIn->Branch("CalClustEnergy",      "vector<float>",          &fCalClustEnergy     );
		fTreeIn->Branch("CalClustEnergyError", "vector<float>",          &fCalClustEnergyError);
		fTreeIn->Branch("CalClustTdiff",       "vector<float>",          &fCalClustTdiff      );
		fTreeIn->Branch("CalClustEllip",       "vector<float>",          &fCalClustEllip      );
		fTreeIn->Branch("CalClustR1",          "vector<float>",          &fCalClustR1         );
		fTreeIn->Branch("CalClustR2",          "vector<float>",          &fCalClustR2         );
		fTreeIn->Branch("CalClustR3",          "vector<float>",          &fCalClustR3         );
		fTreeIn->Branch("CalClustVol",         "vector<float>",          &fCalClustVol        );
		fTreeIn->Branch("CalClustWidth",       "vector<float>",          &fCalClustWidth      );
		fTreeIn->Branch("CalClustTheta",       "vector<float>",          &fCalClustTheta      );
		fTreeIn->Branch("CalClustPhi",         "vector<float>",          &fCalClustPhi        );
		fTreeIn->Branch("CalClustEigen1X",     "vector<float>",          &fCalClustEigen1X    );
		fTreeIn->Branch("CalClustEigen1Y",     "vector<float>",          &fCalClustEigen1Y    );
		fTreeIn->Branch("CalClustEigen1Z",     "vector<float>",          &fCalClustEigen1Z    );
		fTreeIn->Branch("CalClustEigen2X",     "vector<float>",          &fCalClustEigen2X    );
		fTreeIn->Branch("CalClustEigen2Y",     "vector<float>",          &fCalClustEigen2Y    );
		fTreeIn->Branch("CalClustEigen2Z",     "vector<float>",          &fCalClustEigen2Z    );
		fTreeIn->Branch("CalClustEigen3X",     "vector<float>",          &fCalClustEigen3X    );
		fTreeIn->Branch("CalClustEigen3Y",     "vector<float>",          &fCalClustEigen3Y    );
		fTreeIn->Branch("CalClustEigen3Z",     "vector<float>",          &fCalClustEigen3Z    );

		fTreeIn->Branch("TrackG4PIndices ",    "vector<vector<UInt_t>>", &fTrackG4PIndices    );
		fTreeIn->Branch("VertTrackIndices",    "vector<vector<UInt_t>>", &fVertTrackIndices   );
		fTreeIn->Branch("VeeTrackIndices ",    "vector<vector<UInt_t>>", &fVeeTrackIndices    );
		//fTreeIn->Branch("CalTrackIndices ",    "vector<vector<UInt_t>>", &fCalTrackIndices    );
	    fTreeIn->Branch("CalTrackIndices", "vector<vector<UInt_t>>", &fCalClusterTrackIndices );
	    //fTreeIn->Branch("CalTrackEnds",     &fCalTrackEnds    , &b_CalTrackEnds    );
	    fTreeIn->Branch("CalG4Indices",    "vector<vector<UInt_t>>", &fCalClusterG4Indices );

		fTreeIn->Branch("VertTrackEnds",       "vector<vector<Int_t>>",  &fVertTrackEnds      );
		fTreeIn->Branch("VeeTrackEnds",        "vector<vector<Int_t>>",  &fVeeTrackEnds       );

	}

	return true;
}

//implement accessors inherited from RecoTree
 void FlatRecoTree::SetVecs() {

	 fTrkLenFwd           = new vector<float>();
	 fTrkLenBac           = new vector<float>();
	 fTrkMomBeg           = new vector<float>();
	 fTrkMomEnd           = new vector<float>();
	 fTrkVtxX             = new vector<float>();
	 fTrkVtxY             = new vector<float>();
	 fTrkVtxZ             = new vector<float>();
	 fTrkVtxT             = new vector<float>();
	 fTrkEndX             = new vector<float>();
	 fTrkEndY             = new vector<float>();
	 fTrkEndZ             = new vector<float>();
	 fTrkEndT             = new vector<float>();

	 fTrkVtxDirX          = new vector<float>();
	 fTrkVtxDirY          = new vector<float>();
	 fTrkVtxDirZ          = new vector<float>();
	 fTrkEndDirX          = new vector<float>();
	 fTrkEndDirY          = new vector<float>();
	 fTrkEndDirZ          = new vector<float>();
	 fTrkChiFwd           = new vector<float>();
	 fTrkChiBac           = new vector<float>();
	 fTrkNHits            = new vector<size_t>();

	 fTrackXBeg           = new vector<float>();
	 fTrackYBeg           = new vector<float>();
	 fTrackZBeg           = new vector<float>();
	 fTrackCurvBeg        = new vector<float>();
	 fTrackPhiBeg         = new vector<float>();
	 fTrackLambBeg        = new vector<float>();
	 fTrackXEnd           = new vector<float>();
	 fTrackYEnd           = new vector<float>();
	 fTrackZEnd           = new vector<float>();
	 fTrackCurvEnd        = new vector<float>();
	 fTrackPhiEnd         = new vector<float>();
	 fTrackLambEnd        = new vector<float>();
	 fTrkCovMat1Beg       = new vector<float>();
	 fTrkCovMat2Beg       = new vector<float>();
	 fTrkCovMat3Beg       = new vector<float>();
	 fTrkCovMat4Beg       = new vector<float>();
	 fTrkCovMat5Beg       = new vector<float>();
	 fTrkCovMat6Beg       = new vector<float>();
	 fTrkCovMat7Beg       = new vector<float>();
	 fTrkCovMat8Beg       = new vector<float>();
	 fTrkCovMat9Beg       = new vector<float>();
	 fTrkCovMat10Beg      = new vector<float>();
	 fTrkCovMat11Beg      = new vector<float>();
	 fTrkCovMat12Beg      = new vector<float>();
	 fTrkCovMat13Beg      = new vector<float>();
	 fTrkCovMat14Beg      = new vector<float>();
	 fTrkCovMat15Beg      = new vector<float>();
	 fTrkCovMat1End       = new vector<float>();
	 fTrkCovMat2End       = new vector<float>();
	 fTrkCovMat3End       = new vector<float>();
	 fTrkCovMat4End       = new vector<float>();
	 fTrkCovMat5End       = new vector<float>();
	 fTrkCovMat6End       = new vector<float>();
	 fTrkCovMat7End       = new vector<float>();
	 fTrkCovMat8End       = new vector<float>();
	 fTrkCovMat9End       = new vector<float>();
	 fTrkCovMat10End      = new vector<float>();
	 fTrkCovMat11End      = new vector<float>();
	 fTrkCovMat12End      = new vector<float>();
	 fTrkCovMat13End      = new vector<float>();
	 fTrkCovMat14End      = new vector<float>();
	 fTrkCovMat15End      = new vector<float>();

	 fTrkIonizFwd         = new vector<float>();
	 fTrkIonizBac         = new vector<float>();
	 fTrkChgFwd           = new vector<int>();
	 fTrkChgBac           = new vector<int>();

	 fVeeVtxX             = new vector<float>();
	 fVeeVtxY             = new vector<float>();
	 fVeeVtxZ             = new vector<float>();
	 fVeeVtxT             = new vector<float>();
	 fVeeVtxCovar11       = new vector<float>();
	 fVeeVtxCovar12       = new vector<float>();
	 fVeeVtxCovar13       = new vector<float>();
	 fVeeVtxCovar21       = new vector<float>();
	 fVeeVtxCovar22       = new vector<float>();
	 fVeeVtxCovar23       = new vector<float>();
	 fVeeVtxCovar31       = new vector<float>();
	 fVeeVtxCovar32       = new vector<float>();
	 fVeeVtxCovar33       = new vector<float>();

	 fVeePxKshort         = new vector<float>();
	 fVeePyKshort         = new vector<float>();
	 fVeePzKshort         = new vector<float>();
	 fVeeEKshort          = new vector<float>();
	 fVeePxLamb1          = new vector<float>();
	 fVeePyLamb1          = new vector<float>();
	 fVeePzLamb1          = new vector<float>();
	 fVeeELamb1           = new vector<float>();
	 fVeePxLamb2          = new vector<float>();
	 fVeePyLamb2          = new vector<float>();
	 fVeePzLamb2          = new vector<float>();
	 fVeeELamb2           = new vector<float>();
	 fVeeChisqr           = new vector<float>();

	 fVtxX                = new vector<float>();
	 fVtxY                = new vector<float>();
	 fVtxZ                = new vector<float>();
	 fVtxT                = new vector<float>();
	 fVtxCovar11          = new vector<float>();
	 fVtxCovar12          = new vector<float>();
	 fVtxCovar13          = new vector<float>();
	 fVtxCovar21          = new vector<float>();
	 fVtxCovar22          = new vector<float>();
	 fVtxCovar23          = new vector<float>();
	 fVtxCovar31          = new vector<float>();
	 fVtxCovar32          = new vector<float>();
	 fVtxCovar33          = new vector<float>();

	 fCalClustX           = new vector<float>();
	 fCalClustY           = new vector<float>();
	 fCalClustZ           = new vector<float>();
	 fCalClustT           = new vector<float>();
	 fCalClustEnergy      = new vector<float>();
	 fCalClustEnergyError = new vector<float>();
	 fCalClustTdiff       = new vector<float>();
	 fCalClustEllip       = new vector<float>();
	 fCalClustR1          = new vector<float>();
	 fCalClustR2          = new vector<float>();
	 fCalClustR3          = new vector<float>();
	 fCalClustVol         = new vector<float>();
	 fCalClustWidth       = new vector<float>();
	 fCalClustTheta       = new vector<float>();
	 fCalClustPhi         = new vector<float>();
	 fCalClustEigen1X     = new vector<float>();
	 fCalClustEigen1Y     = new vector<float>();
	 fCalClustEigen1Z     = new vector<float>();
	 fCalClustEigen2X     = new vector<float>();
	 fCalClustEigen2Y     = new vector<float>();
	 fCalClustEigen2Z     = new vector<float>();
	 fCalClustEigen3X     = new vector<float>();
	 fCalClustEigen3Y     = new vector<float>();
	 fCalClustEigen3Z     = new vector<float>();

	 fTrackG4PIndices     = new vector<vector<UInt_t>>();
	 fVertTrackIndices    = new vector<vector<UInt_t>>();
	 fVeeTrackIndices     = new vector<vector<UInt_t>>();
	 fCalTrackIndices     = new vector<vector<UInt_t>>();

	 fVertTrackEnds       = new vector<vector<Int_t>>();
	 fVeeTrackEnds        = new vector<vector<Int_t>>();

 }


 void FlatRecoTree::ClearVecs() {

	 fTrkLenFwd->clear();
	 fTrkLenBac->clear();
	 fTrkMomBeg->clear();
	 fTrkMomEnd->clear();
	 fTrkVtxX->clear();
	 fTrkVtxY->clear();
	 fTrkVtxZ->clear();
	 fTrkVtxT->clear();
	 fTrkEndX->clear();
	 fTrkEndY->clear();
	 fTrkEndZ->clear();
	 fTrkEndT->clear();

	 fTrkVtxDirX->clear();
	 fTrkVtxDirY->clear();
	 fTrkVtxDirZ->clear();
	 fTrkEndDirX->clear();
	 fTrkEndDirY->clear();
	 fTrkEndDirZ->clear();
	 fTrkChiFwd->clear();
	 fTrkChiBac->clear();
	 fTrkNHits->clear();

	 fTrackXBeg->clear();
	 fTrackYBeg->clear();
	 fTrackZBeg->clear();
	 fTrackCurvBeg->clear();
	 fTrackPhiBeg->clear();
	 fTrackLambBeg->clear();
	 fTrackXEnd->clear();
	 fTrackYEnd->clear();
	 fTrackZEnd->clear();
	 fTrackCurvEnd->clear();
	 fTrackPhiEnd->clear();
	 fTrackLambEnd->clear();
	 fTrkCovMat1Beg->clear();
	 fTrkCovMat2Beg->clear();
	 fTrkCovMat3Beg->clear();
	 fTrkCovMat4Beg->clear();
	 fTrkCovMat5Beg->clear();
	 fTrkCovMat6Beg->clear();
	 fTrkCovMat7Beg->clear();
	 fTrkCovMat8Beg->clear();
	 fTrkCovMat9Beg->clear();
	 fTrkCovMat10Beg->clear();
	 fTrkCovMat11Beg->clear();
	 fTrkCovMat12Beg->clear();
	 fTrkCovMat13Beg->clear();
	 fTrkCovMat14Beg->clear();
	 fTrkCovMat15Beg->clear();
	 fTrkCovMat1End->clear();
	 fTrkCovMat2End->clear();
	 fTrkCovMat3End->clear();
	 fTrkCovMat4End->clear();
	 fTrkCovMat5End->clear();
	 fTrkCovMat6End->clear();
	 fTrkCovMat7End->clear();
	 fTrkCovMat8End->clear();
	 fTrkCovMat9End->clear();
	 fTrkCovMat10End->clear();
	 fTrkCovMat11End->clear();
	 fTrkCovMat12End->clear();
	 fTrkCovMat13End->clear();
	 fTrkCovMat14End->clear();
	 fTrkCovMat15End->clear();

	 fTrkIonizFwd->clear();
	 fTrkIonizBac->clear();
	 fTrkChgFwd->clear();
	 fTrkChgBac->clear();

	 fVeeVtxX->clear();
	 fVeeVtxY->clear();
	 fVeeVtxZ->clear();
	 fVeeVtxT->clear();
	 fVeeVtxCovar11->clear();
	 fVeeVtxCovar12->clear();
	 fVeeVtxCovar13->clear();
	 fVeeVtxCovar21->clear();
	 fVeeVtxCovar22->clear();
	 fVeeVtxCovar23->clear();
	 fVeeVtxCovar31->clear();
	 fVeeVtxCovar32->clear();
	 fVeeVtxCovar33->clear();

	 fVeePxKshort->clear();
	 fVeePyKshort->clear();
	 fVeePzKshort->clear();
	 fVeeEKshort->clear();
	 fVeePxLamb1->clear();
	 fVeePyLamb1->clear();
	 fVeePzLamb1->clear();
	 fVeeELamb1->clear();
	 fVeePxLamb2->clear();
	 fVeePyLamb2->clear();
	 fVeePzLamb2->clear();
	 fVeeELamb2 ->clear();
	 fVeeChisqr->clear();

	 fVtxX->clear();
	 fVtxY->clear();
	 fVtxZ->clear();
	 fVtxT->clear();
	 fVtxCovar11->clear();
	 fVtxCovar12->clear();
	 fVtxCovar13->clear();
	 fVtxCovar21->clear();
	 fVtxCovar22->clear();
	 fVtxCovar23->clear();
	 fVtxCovar31->clear();
	 fVtxCovar32->clear();
	 fVtxCovar33->clear();

	 fCalClustX->clear();
	 fCalClustY->clear();
	 fCalClustZ->clear();
	 fCalClustT->clear();
	 fCalClustEnergy->clear();
	 fCalClustEnergyError->clear();
	 fCalClustTdiff->clear();
	 fCalClustEllip->clear();
	 fCalClustR1->clear();
	 fCalClustR2->clear();
	 fCalClustR3->clear();
	 fCalClustVol->clear();
	 fCalClustWidth->clear();
	 fCalClustTheta->clear();
	 fCalClustPhi->clear();
	 fCalClustEigen1X->clear();
	 fCalClustEigen1Y->clear();
	 fCalClustEigen1Z->clear();
	 fCalClustEigen2X->clear();
	 fCalClustEigen2Y->clear();
	 fCalClustEigen2Z->clear();
	 fCalClustEigen3X->clear();
	 fCalClustEigen3Y->clear();
	 fCalClustEigen3Z->clear();

	 fTrackG4PIndices->clear();
	 fVertTrackIndices->clear();
	 fVeeTrackIndices->clear();
	 fCalTrackIndices->clear();

	 fVertTrackEnds->clear();
	 fVeeTrackEnds->clear();

 }

 // sizes
 const size_t FlatRecoTree::NTrack()      const {
	 return fTrkNHits->size();
 }

 const size_t FlatRecoTree::NVertex()     const {
	 return fVtxX->size();
 }

 const size_t FlatRecoTree::NVee()        const {
	 return fVeeVtxX->size();
 }

 const size_t FlatRecoTree::NCalCluster() const {
	 return fCalClustX->size();
 }

 const TLorentzVector* FlatRecoTree::TrackVertex(const size_t& itrack) const {
	 TLorentzVector* v = new TLorentzVector(fTrkVtxX->at(itrack),
			                                fTrkVtxY->at(itrack),
			                                fTrkVtxZ->at(itrack),
			                                fTrkVtxT->at(itrack) );
	 return v;
 }

 const TLorentzVector* FlatRecoTree::TrackEnd(const size_t& itrack)    const {
	 TLorentzVector* v = new TLorentzVector(fTrkEndX->at(itrack),
			                                fTrkEndY->at(itrack),
			                                fTrkEndZ->at(itrack),
			                                fTrkEndT->at(itrack) );
	 return v;
 }

 const size_t  FlatRecoTree::NTrackHit(const size_t& itrack)   const {
	 return fTrkNHits->at(itrack);
 }

 const TVector3* FlatRecoTree::TrackMomBeg(const size_t& itrack) const {
	 TVector3* v = new TVector3(fTrkVtxDirX->at(itrack),
			                    fTrkVtxDirX->at(itrack),
			                    fTrkVtxDirX->at(itrack) );
	 (*v) *= fTrkMomBeg->at(itrack);
	 return v; //*fTrkMomBeg->at(itrack);

 }

 const TVector3* FlatRecoTree::TrackMomEnd(const size_t& itrack) const {
	 TVector3* v = new TVector3(fTrkEndDirX->at(itrack),
			                    fTrkEndDirX->at(itrack),
			                    fTrkEndDirX->at(itrack) );
	 (*v) *= fTrkMomEnd->at(itrack);
	 return v;//*fTrkMomEnd->at(itrack);
 }

 const float FlatRecoTree::TrackVtxDirectionX(const size_t& itrack) const {
	 return fTrkVtxDirX->at(itrack);
 }

 const float FlatRecoTree::TrackVtxDirectionY(const size_t& itrack) const {
	 return fTrkVtxDirY->at(itrack);
 }

 const float FlatRecoTree::TrackVtxDirectionZ(const size_t& itrack) const {
	 return fTrkVtxDirZ->at(itrack);
 }

 const float FlatRecoTree::TrackEndDirectionX(const size_t& itrack) const {
	 return fTrkEndDirX->at(itrack);
 }

 const float FlatRecoTree::TrackEndDirectionY(const size_t& itrack) const {
	 return fTrkEndDirY->at(itrack);
 }

 const float FlatRecoTree::TrackEndDirectionZ(const size_t& itrack) const {
	 return fTrkEndDirZ->at(itrack);
 }

 const float FlatRecoTree::TrackLenFwd(const size_t& itrack) const {
 	return fTrkLenFwd->at(itrack);
 }

 const float FlatRecoTree::TrackLenBkd(const size_t& itrack) const {
 	return fTrkLenBac->at(itrack);
 }

 const float FlatRecoTree::TrackIonizFwd(const size_t& itrack) const {
 	return fTrkIonizFwd->at(itrack);
 }

 const float FlatRecoTree::TrackIonizBkd(const size_t& itrack) const {
 	return fTrkIonizBac->at(itrack);
 }

 const int FlatRecoTree::TrackChiSqrFwd(const size_t& itrack) const {
	 return fTrkChiFwd->at(itrack);
 }

 const int FlatRecoTree::TrackChiSqrBkd(const size_t& itrack) const {
	 return fTrkChiBac->at(itrack);
 }

 const int FlatRecoTree::TrackChgFwd(const size_t& itrack) const {
 	return fTrkChgFwd->at(itrack);
 }

 const int FlatRecoTree::TrackChgBkd(const size_t& itrack) const {
	 return fTrkChgBac->at(itrack);
 }

 void FlatRecoTree::TrackParBeg(const size_t& itrack, float pars[5]) const {

 	pars[0] = fTrackXBeg   ->at(itrack);
 	pars[1] = fTrackYBeg   ->at(itrack);
 	pars[2] = fTrackZBeg   ->at(itrack);
 	pars[3] = fTrackCurvBeg->at(itrack);
 	pars[4] = fTrackPhiBeg ->at(itrack);
 	pars[5] = fTrackLambBeg->at(itrack);
 }

 void FlatRecoTree::TrackParEnd(const size_t& itrack, float pars[5]) const {
	pars[0] = fTrackXEnd   ->at(itrack);
	pars[1] = fTrackYEnd   ->at(itrack);
	pars[2] = fTrackZEnd   ->at(itrack);
	pars[3] = fTrackCurvEnd->at(itrack);
	pars[4] = fTrackPhiEnd ->at(itrack);
	pars[5] = fTrackLambEnd->at(itrack);
 }

 void FlatRecoTree::TrackCovarBeg(const size_t& itrack, float covar[15]) const {

 	covar[0]  = fTrkCovMat1Beg->at(itrack);
 	covar[1]  = fTrkCovMat2Beg->at(itrack);
 	covar[2]  = fTrkCovMat3Beg->at(itrack);
 	covar[3]  = fTrkCovMat4Beg->at(itrack);
 	covar[4]  = fTrkCovMat5Beg->at(itrack);
 	covar[5]  = fTrkCovMat6Beg->at(itrack);
 	covar[6]  = fTrkCovMat7Beg->at(itrack);
 	covar[7]  = fTrkCovMat8Beg->at(itrack);
 	covar[8]  = fTrkCovMat9Beg->at(itrack);
 	covar[9]  = fTrkCovMat10Beg->at(itrack);
 	covar[10] = fTrkCovMat11Beg->at(itrack);
 	covar[11] = fTrkCovMat12Beg->at(itrack);
 	covar[12] = fTrkCovMat13Beg->at(itrack);
 	covar[13] = fTrkCovMat14Beg->at(itrack);
 	covar[14] = fTrkCovMat15Beg->at(itrack);
 }

 void FlatRecoTree::TrackCovarEnd(const size_t& itrack, float covar[15]) const {

	covar[0]  = fTrkCovMat1End->at(itrack);
	covar[1]  = fTrkCovMat2End->at(itrack);
	covar[2]  = fTrkCovMat3End->at(itrack);
	covar[3]  = fTrkCovMat4End->at(itrack);
	covar[4]  = fTrkCovMat5End->at(itrack);
	covar[5]  = fTrkCovMat6End->at(itrack);
	covar[6]  = fTrkCovMat7End->at(itrack);
	covar[7]  = fTrkCovMat8End->at(itrack);
	covar[8]  = fTrkCovMat9End->at(itrack);
	covar[9]  = fTrkCovMat10End->at(itrack);
	covar[10] = fTrkCovMat11End->at(itrack);
	covar[11] = fTrkCovMat12End->at(itrack);
	covar[12] = fTrkCovMat13End->at(itrack);
	covar[13] = fTrkCovMat14End->at(itrack);
	covar[14] = fTrkCovMat15End->at(itrack);
 }

 // FIXME implement methods
 const TLorentzVector* FlatRecoTree::TrackTruePosBeg(const size_t& itrack) const {
	 if(itrack)return 0;
	 else return 0;
 }

 const TLorentzVector* FlatRecoTree::TrackTruePosEnd(const size_t& itrack) const {
	 if(itrack)return 0;
	 else return 0;
 }

 const TLorentzVector* FlatRecoTree::TrackTrueMomBeg(const size_t& itrack) const {
	 if(itrack)return 0;
	 else return 0;
 }

 const TLorentzVector* FlatRecoTree::TrackTrueMomEnd(const size_t& itrack) const {
	 if(itrack)return 0;
	 else return 0;
 }

 //TODO implement methods
 const float                 FlatRecoTree::TrackTrueEnergy(const size_t& itrack)     const { return itrack*0+FLT_MAX;}
 const size_t                FlatRecoTree::TrackNTrueTrack(const size_t& itrack)     const {return itrack*0+UINT_MAX;}
 const int                   FlatRecoTree::TrackTrkIdMaxDeposit(const size_t& itrack)const { return itrack*0+INT_MAX;}
 const float                 FlatRecoTree::TrackMaxDeposit(const size_t& itrack)     const { return itrack*0+FLT_MAX;}
 const pair<int,float>*      FlatRecoTree::TrackTrueDeposit(const size_t& itrack, size_t& itrue) const { if(itrack&&itrue) return nullptr; else return nullptr;}
 const vector<pair<int,float>>* FlatRecoTree::TrackTrueDeposits(const size_t& itrack)            const{ if(itrack) return nullptr; else return nullptr;}
 /// ================ vertex ==========================
 const TLorentzVector* FlatRecoTree::GetVertex(const size_t& ivertex) const {


     const TLorentzVector* v = new TLorentzVector(  fVtxX->at(ivertex),
	                                                fVtxY->at(ivertex),
	                                                fVtxZ->at(ivertex),
	                                                fVtxT->at(ivertex) );
	 return v;

 }

 void FlatRecoTree::VertexCovariance(const size_t& ivertex, float covar[][3]) const {

	 covar[0][0] = fVtxCovar11->at(ivertex);
	 covar[0][1] = fVtxCovar12->at(ivertex);
	 covar[0][2] = fVtxCovar13->at(ivertex);
	 covar[1][0] = fVtxCovar21->at(ivertex);
	 covar[1][1] = fVtxCovar22->at(ivertex);
	 covar[1][2] = fVtxCovar23->at(ivertex);
	 covar[2][0] = fVtxCovar31->at(ivertex);
	 covar[2][1] = fVtxCovar32->at(ivertex);
	 covar[2][2] = fVtxCovar33->at(ivertex);

 }

 /// =============== Vee =======================
 const TLorentzVector* FlatRecoTree::VeeVertex(const size_t& ivee) const {
 	return new TLorentzVector(fVeeVtxX->at(ivee), fVeeVtxY->at(ivee), fVeeVtxZ->at(ivee), fVeeVtxT->at(ivee)); } void FlatRecoTree::VeeCovariance(const size_t& ivee, float covar[][3]) const {
	 covar[0][0] = fVeeVtxCovar11->at(ivee);
	 covar[0][1] = fVeeVtxCovar12->at(ivee);
	 covar[0][2] = fVeeVtxCovar13->at(ivee);
	 covar[1][0] = fVeeVtxCovar21->at(ivee);
	 covar[1][1] = fVeeVtxCovar22->at(ivee);
	 covar[1][2] = fVeeVtxCovar23->at(ivee);
	 covar[2][0] = fVeeVtxCovar31->at(ivee);
	 covar[2][1] = fVeeVtxCovar32->at(ivee);
	 covar[2][2] = fVeeVtxCovar33->at(ivee); } const vector<TLorentzVector>* FlatRecoTree::VeeMomentumPerHypothesis(const size_t& ivee) const {

	vector<TLorentzVector>* v = new vector<TLorentzVector>();
	v->push_back(TLorentzVector(fVeePxKshort->at(ivee),fVeePyKshort->at(ivee),
			fVeePzKshort->at(ivee),fVeeEKshort->at(ivee)));
	v->push_back(TLorentzVector(fVeePxLamb1->at(ivee),fVeePyLamb1->at(ivee),
			fVeePzLamb1->at(ivee),fVeeELamb1->at(ivee)));
	v->push_back(TLorentzVector(fVeePxLamb2->at(ivee),fVeePyLamb2->at(ivee),
			fVeePzLamb2->at(ivee),fVeeELamb2->at(ivee)));
 	return v; } const float FlatRecoTree::VeeChiSquared(const size_t& ivee) const { 	return fVeeChisqr->at(ivee); } /// ================ ECal cluster ====================== const TLorentzVector*   FlatRecoTree::CalClustPosition(const size_t& icluster) const { 	return new TLorentzVector(fCalClustX->at(icluster),fCalClustY->at(icluster),
 			            fCalClustZ->at(icluster),fCalClustT->at(icluster)); } const float  FlatRecoTree::CalClustEnergy(const size_t& icluster) const { 	return fCalClustEnergy->at(icluster); } const float  FlatRecoTree::CalClustEnergyError(const size_t& icluster) const { 	return fCalClustEnergyError->at(icluster); }
const float   FlatRecoTree::CalClustTrueEnergy(const size_t& icluster)     const { //FIXME
	return  icluster;
}
const size_t  FlatRecoTree::CalClustNTrueTrack(const size_t& icluster)     const {
	return icluster;
}
const int     FlatRecoTree::CalClustTrkIdMaxDeposit(const size_t& icluster) const {
	return icluster;
}
const float   FlatRecoTree::CalClustMaxDeposit(const size_t& icluster) const {
	return  icluster;
}
const std::pair<int,float>* FlatRecoTree::CalClustTrueDeposit(const size_t& ivee, const size_t& itrack) const {
	auto b=ivee;
	auto c = itrack;
	b++;
	c++;
	return nullptr;
} //FIXME
 const float  FlatRecoTree::CalClustTimeDifference(const size_t& icluster) const { 	return fCalClustTdiff->at(icluster); } const float* FlatRecoTree::CalClustShape(const size_t& icluster) const {

	float* shape = new float[6];
	shape[0] = fCalClustEllip->at(icluster);
	shape[1] = fCalClustR1->at(icluster);
	shape[2] = fCalClustR2->at(icluster);
	shape[3] = fCalClustR3->at(icluster);
	shape[4] = fCalClustVol->at(icluster);
	shape[5] = fCalClustWidth->at(icluster);
 	return shape; } const float  FlatRecoTree::CalClustTheta(const size_t& icluster) const { 	return fCalClustTheta->at(icluster); } const float  FlatRecoTree::CalClustPhi(const size_t& icluster) const { 	return fCalClustPhi->at(icluster); } const vector<TVector3>* FlatRecoTree::CalClustEigenVecs(const size_t& icluster) const{

	vector<TVector3>* v = new vector<TVector3>();
	v->push_back(TVector3(fCalClustEigen1X->at(icluster),fCalClustEigen1Y->at(icluster),fCalClustEigen1Z->at(icluster)));
	v->push_back(TVector3(fCalClustEigen2X->at(icluster),fCalClustEigen2Y->at(icluster),fCalClustEigen2Z->at(icluster)));
	v->push_back(TVector3(fCalClustEigen3X->at(icluster),fCalClustEigen3Y->at(icluster),fCalClustEigen3Z->at(icluster)));
 	return v; }
