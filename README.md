# garana
garana is a lightweight, portable software package for the analysis of simulation (and eventually data) from the DUNE ND-GAr detector. The package is available on the DUNE nodes or can be installed locally. The most painful dependency of garana is ROOT. 

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

## Usage
C++ executables, ROOT macros, and python modules can all be used with garana libraries. The only required input to garana is a root file containing one or more garana-compatible trees. These trees are produced by an art analyzer module in garsoft/Ana called StructuredTree_module.cc. You can find example executables in ```garana/bin```
