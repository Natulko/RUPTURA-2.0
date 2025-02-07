# RUPTURA 2.0
## Changes made in comparison to RUPTURA 1.0
The 4 main additions are:
1) implicit solver implementation;
2) isothermal implementation;
3) Ergun equation implementation;
4) Danckwerts boundary condition implementation;

Implementations of (2), (3), and (4) can be found in the corresponding added folders in src. Each folder contains all the files that are different from RUPTURA 1.0.

The current version of the code is implemented with an implicit solver and thus indicates the implementation of (1).

Alternatively, correspondent files/folders can also be identified by the last commit message.

## Usage
Instructions for running RUPTURA are in the README file of RUPTURA 1.0 below. 

To run the implementations of (2), (3) or (4), all the files present in the corresponding folder should be placed instead of the old ones.

The current code is implemented with implicit solvers (1), meaning that (1) does not require any additional action to be run.

## Authors
Max Blankestijn,        Delft University of Technology, The Netherlands<br>
Nataliia Bagan,         Leiden University, The Netherlands<br>
Dennis van Os,          Delft University of Technology, The Netherlands<br>
Eliot Azoulay,          Delft University of Technology, The Netherlands<br>
Bas Teisman,            Leiden University, The Netherlands<br>
Soham Katewale,         Delft University of Technology, The Netherlands<br>
Constantijn Kroep,      Delft University of Technology, The Netherlands<br>

# RUPTURA 1.0

## Breakthrough, IAST, and isotherm fitting code
This software is a simulation package to compute breakthrough curves and 
IAST mixture predictions. It has been developed at the Delft University of 
Technology (Delft, The Netherlands), during 2022 in active collaboration
with the University of Amsterdam (Amsterdam, The Netherlands), Eindhoven 
University of Technology (Eindhoven, Netherlands), Pablo de Olavide 
University (Seville, Spain), and Shell Global Solutions International B.V.
Amsterdam.

## Features
* Unlimited amount of components
* Fast (sub-second) IAST mixture computation
* Stable breakthrough computation, including
  - step breakthrough
  - pulse breakthrough
  - Linearized driving model (LDF)
  - Axial disperion
  - Pressure gradient
* Automatic picture/movie generation
* Isotherm models
  - Langmuir
  - Anti-Langmuir
  - BET
  - Henry
  - Freundlich
  - Sips
  - Langmuir-Freundlich
  - Redlich-Peterson
  - Toth
  - Unilan
  - O’Brien & Myers
  - Quadratic
  - Temkin
* Fitting raw data to isotherm models

## Terms of use
If you use this software for scientific publications, please cite:<br>
"RUPTURA: Simulation Code for Breakthrough, Ideal Adsorption Solution
Theory Computations, and Fitting of Isotherm Models"<br>
S. Sharma, S. Balestra, R. Baur, U. Agarwal, E. Zuidema, M. Rigutto,
S. Calero, T.J.H. Vlugt, and D. Dubbeldam, 
Molecular Simulation Journal, 49(9), 2023
https://www.tandfonline.com/doi/full/10.1080/08927022.2023.2202757

## Authors
Shrinjay Sharma,        Delft University of Technology, The Netherlands<br>
Youri Ran,              University of Amsterdam, The Netherlands<br>
Salvador R.G. Balestra, Pablo de Olavide University, Spain<br>
Richard Baur,           Shell Global Solutions International B.V., The Netherlands<br>
Umang Agarwal,          Shell Global Solutions International B.V., The Netherlands<br>
Eric Zuidema,           Shell Global Solutions International B.V., The Netherlands<br>
Marcello Rigutto,       Shell Global Solutions International B.V., The Netherlands<br>
Sofia Calero,           Eindhoven University of Technology, The Netherlands<br>
Thijs J.H. Vlugt,       Delft University of Technology, The Netherlands<br>
David Dubbeldam,        University of Amsterdam, The Netherlands<br>

## Compilation
```
cmake . -B build
cmake --build build
```

to clean:<br>
```
rm -rf build
```

to build and host the documentation
```
cmake --build build -- documentation
cd build/html
python -m http.server 8000
```

## Running
```
cd examples/Silicalite-CO2-N2/breakthrough/Langmuir<br>
./run
```

## Input
See the cited article.

## Python Installation
Ruptura can be used of python through `src/ruptura.py`, examples can be found in the examples directory.
The python package can be installed with:

```
pip install ruptura
```
or
```
conda install ruptura
```

