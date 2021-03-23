#ifndef GARANA_MILL_RECOTREE_H
#define GARANA_MILL_RECOTREE_H

#include "garana/Accessors/FlatRecoTree.h"
#include "garana/Accessors/StructuredRecoTree.h"
#include "garana/Processors/Mill.h"

#include <vector>
#include <string>
#include <climits>

using std::vector;

namespace garana {

	class MillRecoTree : public Mill, public FlatRecoTree {

	 public:

		MillRecoTree(){};
		MillRecoTree(TTree* treeIn, TTree* treeOut);

		void MillTrees() override; ///< main method

	 private:

		bool VerifyBranches() override;
		void FillTrack();
		void FillVertex();
		void FillVee();
		void FillCaloCluster();

		StructuredRecoTree* fRecoIn  = nullptr; ///< points to input structured recoTree we are flattening

		//known branches, need to update if tree structure changes
		//  in garsoft/Ana/StructuredTree_module.cc
		enum RecoBranch {
			kEvent,
			kTracks,
			kVees,
			kVertices,
			kCalClusters,
			kVertTrackEnds,
			kVeeTrackEnds
		};//

		std::map<std::string,RecoBranch> nameToRecoBranch =	{
			{"Event",         kEvent,       },
			{"Tracks",        kTracks       },
			{"Vees",          kVees         },
			{"Vertices",      kVertices     },
		    {"CalClusters",   kCalClusters  },
            {"VertTrackEnds", kVertTrackEnds},
            {"VeeTrackEnds ", kVeeTrackEnds }
		};

		std::map<RecoBranch,bool> branchToDrawOpt = { ///< keep track of which branches are active
		    {kEvent        , false},
			{kTracks       , false},
			{kVees         , false},
			{kVertices     , false},
		    {kCalClusters  , false},
            {kVertTrackEnds, false},
            {kVeeTrackEnds , false}
		};
	};//class

}//namespace

#endif /* GARANA_MILL_RECOTREE_H */
