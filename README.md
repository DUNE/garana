# garana
garana is a lightweight, portable software package for the analysis of simulation (and eventually data) from the DUNE ND-GAr detector. The package is available on the DUNE nodes or can be installed locally. The most painful dependency of garana is ROOT. 

DISCLAIMER: garana is in beta! Currently, an end-to-end test on structured trees with the default analysis configuration has been performed. Use other functionality at your own risk! Contact chilgenb@fnal.gov with questions or to report a bug.

The intent with garana is for it to be a useful tool for simplifying analysis. Current functionality includes
* Accessors for predefined tree formats 
* Data products providing distilled information from garsoft products with other relevant informaiton
* Truth matching utilities
* Tools for converting garana class based or "structured" trees to flat ntuples and verifying consistency between them

Functionality currently being implimented includes
* ROOT TEve based, standalone event display

## Installation

DISCLAIMER: the installation procedure has only been tested with Ubuntu 20.04 and on the DUNE nodes (SLF 7.9 (Nitrogen))

### Dependencies

* [ROOT](https://root.cern/install/) v6_22_00 through v6_22_06
* [Python 3](https://www.python.org/download/releases/3.0/) (also a dependency of ROOT)
* [CMake](https://cmake.org/) v3.8 through v3.19

### CMake based build
1. In your installation area, clone the garana git repository  
```shell
git clone https://github.com/chilge/garana 
```
2. Make a directory to contain the build, garana_build for example
3. cd into the build directory
4. Generate the CMake files
``` cmake
cmake /path/to/garana
```
5. Build
``` cmake
cmake --build . -j<number of cores>
```
6. Install (depending on the default install area on your system, this may require super user permissions)
``` cmake
cmake --install .
```
You should now have access to the garana libraries. You can verify this by checking for a path to one of the garana executibles
``` shell
which gar
```
## Trees
garana provides tools to easily access several different trees, each representing a stage in the simulation and reconstruction chain:
* headerTree: sample provenance information, run and subrun numbers, analysis configuration
* genTree: generator level information, e.g. GENIE interactions
* g4Tree: GEANT4 level information, e.g. particle ID, ancestry, and kinematics
* detTree: readout simulation information, e.g. raw digits
* recoTree: reconstruction level information, e.g. tracks and vertices
* displayTree: truth-level and reconstruction-level trajectory information for the garana event display

garana supports three analysis configurations: general purpose (default), reconstruction developement, and readout simulation developement. The tree content can vary for each configuration. At present, this is true only for the recoTree. The content of the recoTree varies depending on the configuration.  For general purpose, recoTree contains tracks, vertices, vees, and ECal clusters. For reconstruction development, it is the same as for general purpose except it also contains all reconstructed objects, including intermediate objects (e.g. tracks from the first pass). For readout simulation developement, recoTree only contains TPC and ECal hits.

In the following subsections, tables of the branches in each tree are provided for the default analysis configuration with structured trees (note that flat trees contain the same information).

### genTree
garana supports overlay samples, e.g. cosmics with multiple genie interactions per beam spill. most of the time, this tree will only contain GENIE interactions.

branch name   | data type                                        | description
--------------|--------------------------------------------------|---------------------------------------------------------------
 Event        | Int_t                                            | event number
 GIndex       | std::vector\<Int_t\>                             | index of GENIE interaction in this event; = -1 if it's not a GENIE interaction
 GTruth       | std::vector\<garana::GTruth\>                    | GENIE ghep record for each GENIE interaction
 FSParticles  | std::vector\<std::vector\<garana\<FSParticle\>\> | final state particle kinematics (applies to GENIE or cosmics)

### g4Tree

branch name   | data type                                        | description
--------------|--------------------------------------------------|---------------------------------------------------------------
 Event        | Int_t                                            | event number
 G4Particles  | std::vector\<garana::G4Particle\>                | for particles tracked by GEANT4, contains particle ID, ancestry, and position/momentum 4-vectors
 TruthIndex   | std::vector\<UInt_t\>                            | index in genTree for truth object associated with this G4Particle (1-to-1 matching)

### recoTree

branch name   | data type                                        | description
--------------|--------------------------------------------------|---------------------------------------------------------------
 Event        | Int_t                                            | event number
 Tracks       | std::vector\<garana::Track\>                     | TPC track fit parameters, ionization, and PID info
 Vertices     | std::vector\<garana::Vertex\>                    | TPC vertex 4-position and covariance matrix
 CalClusters  | std::vector\<garana::CaloCluster\>               | ECal cluster fit parameters and 4-position
 TrackG4Indices   | std::vector\<vector\<UInt_t\>\>              | index in g4Tree for G4 particle(s) associated with this track (one-to-many matching)
 VertTrackIndices | std::vector\<vector\<UInt_t\>\>              | index in recoTree for track(s) associated with this vertex (one-to-many matching)
 VertTrackEnds    | std::vector\<vector\<Int_t\>\>               | which end of track associated to this vertex is attached to the vertex
 VeeTrackIndices  | std::vector\<vector\<UInt_t\>\>              | index in recoTree for track(s) associated with this vee (one-to-many matching)
 VeeTrackEnds     | std::vector\<vector\<Int_t\>\>               | which end of track associated to this vee is attached to the vertex
 CalTrackIndices  | std::vector\<vector\<UInt_t\>\>              | index in recoTree for track(s) associated with this ECal cluster (one-to-many matching)

## Usage
Analyzers should be provided with a root file produced by an analyzer module in garsoft, garsoft/Ana/StructuredTree_module.cc. The file must contain a complete set of garana-compatible trees for one of the pre-defined analysis configurations:
* General use (default) : genTree, g4Tree, recoTree (tracks, vertices, vees, and ECal clusters)
* Reconstruction developement: genTree, g4Tree, recoTree (TPC hits, TPC clusters, TPC tracks, vertices, vees, ECal hits and ECal clusters)
* Readout simulation developement: genTree, g4Tree, detTree, recoTree (TPC and ECal hits)
This file is the only input required for garana. 

C++ executables, ROOT C++ macros, and python modules can all be used with garana libraries. An example for each of these implimentations can be found at garana/bin with file name demo.cc, demo.C or demo.py respectively.

A garana accessor class, TreeManager, that takes the path to the input file(s) as the only argument in its constructor, manages all basic I/O operations and initialization of and access to tree-specific accessor classes. For example, 
in C++
```c++
  TreeManager* treeman = new TreeManager("/path/to/input/file.root");
  GenTree*  gentree  = treeman->GetGenTree();
  G4Tree*   g4tree   = treeman->GetG4Tree();
  RecoTree* recotree = treeman->GetRecoTree();
```
or in Python
```python
  TreeManager treeman("/path/to/input/file.root")
  gentree  = treeman.GetGenTree()
  g4tree   = treeman.GetG4Tree()
  recotree = treeman.GetRecoTree()
```
From the tree accessors, the analyzer can call the tree accessor methods. See the garana accessor class headers for more information (garana/Accessors/\*.h).

In most cases, the analyzer will develop their analysis using a structured tree as it is more user friendly. In garana, there are abstract base classes (see garana/Base/\*.h) that define common accessor methods that can be used with structured or flat trees. Flat trees are usually better for computing performance. Analyzers (or producers) can convert the structured trees into flat trees containing the same information. So long as only the common methods defined in the base classes are used in the analysis, the same analysis code can be used on either the structured or flat trees.

However, it may be that structured trees are sufficient for the lifetime of the analysis. In this case, the analyzer can get access to the garana data products directly. While the abstract methods from each accessors base class can still be used, the analyzer can call additional methods native to the derived class. For example,
```c++
StructuredGenTree* structgen = treeman->GetGenTree();
GTruth* gtruth = structgen->GetGTruth(0);
```

## Copyright and Licensing
Copyright © 2023 FERMI NATIONAL ACCELERATOR LABORATORY for the benefit of the DUNE Collaboration.

This repository, and all software contained within, except where noted within the individual source files, is licensed under
the Apache License, Version 2.0 (the "License"); you may not use this
file except in compliance with the License. You may obtain a copy of
the License at

    http://www.apache.org/licenses/LICENSE-2.0

Copyright is granted to FERMI NATIONAL ACCELERATOR LABORATORY on behalf
of the Deep Underground Neutrino Experiment (DUNE). Unless required by
applicable law or agreed to in writing, software distributed under the
License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for
the specific language governing permissions and limitations under the
License.
