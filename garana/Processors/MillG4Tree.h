#ifndef GARANA_MILL_G4TREE_H
#define GARANA_MILL_G4TREE_H

#include "garana/Accessors/FlatG4Tree.h"
#include "garana/Accessors/StructuredG4Tree.h"
#include "garana/Processors/Mill.h"

#include <vector>
#include <string>
#include <climits>

using std::vector;

namespace garana {

	class MillG4Tree : public Mill, public FlatG4Tree {

	 public:

		MillG4Tree(){};
		MillG4Tree(TTree* treeIn, TTree* treeOut);

		void MillTrees() override;

	 private:

		bool VerifyBranches() override;


		StructuredG4Tree* fG4In  = nullptr;

		//known branches, need to update if tree structure changes
		//  in garsoft/Ana/StructuredTree_module.cc
		enum G4Branch {
			kEvent,
			kG4Particles,
			kG4TruthIndex
		};//

		std::map<std::string,G4Branch> nameToG4Branch =	{
			{"Event",        kEvent},
			{"G4Particles",  kG4Particles},
			{"G4TruthIndex", kG4TruthIndex}

		};//

		std::map<G4Branch,bool> branchToDrawOpt = {
		    {kEvent,        false},
			{kG4Particles,  false},
			{kG4TruthIndex, false}
		};

	};//class

}//namespace

#endif /* GARANA_MILL_G4TREE_H */
