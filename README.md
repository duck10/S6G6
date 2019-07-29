s6g6 contains a library of functions for calculating distances between lattices.
In this code base, there are two types of distance calculations: S6 and G6 distances.
G6 was described by Andrews&Bernstein, 1988 and 2014. S6 was described
by Andrews,Bernstein, and Sauter, 2014 (two papers).

In this repository, there is support code for reading unit cell information, doing
Niggli or Selling (Delone/Delaunay) reduction, creating S6 and G6 objects, and
computing the distance between a pair of lattices.

The test code (s6g6_test.cpp) will read a file of unit cells,usually prefixed by
the lattice type (P F I R A B C), followed by the unit cell parameters. The test
program will then calculate all the distances between each pair of input cells.

The module Rcpp_distances.cpp is designed to accept (from R) 13 command line
arguments: DistanceType, lattice type 1, unit cell parameters for cell #1,
lattice type 2, unit cell parameters for cell #2. The Distance type should either "N"
or "S",  "N" for Niggli reduction and distance calculation in G6, "S" for Selling reduction and distance calculation in S6.

A sample input to Rcpp_distances:
S P 10 10 10  90 90 90  F 11 11 11 91 91 91

NOTE: for the test code (only), there are alternate input types available. 
Instead of a lattice type, "S" will indicate that the input is in Selling
parameters (the scalars of Delone reduction), and "G" will indicate that
input is in G6 parameters. All input types can be mixed as they are all
converted to the same form in the programs.

NOTE: the two distance functions (CS6Dist and NCDist) _REQUIRE_ that
the input be reduced using the appropriate method. Inputing unreduced
cells will return invalid results that might appear valid. There is no
internal check that the inputs are reduced.

For running cmake on Windows computers, the paths for includes and binaries
may need to be edited in the 4 *.cmake files in cmake/modules to correspond to 
particular windows installations of R.

Sample input and output for s6g6_test

p 10 10 10  90 90 90
f 10 10 10  90 90 90
i 10 10 10  90 90 90
end

0 10.00000  10.00000  10.00000   1.57080   1.57080   1.57080
1  7.07107   7.07107   7.07107   2.09440   2.09440   1.57080
0  0.00000   0.00000   0.00000 -100.00000 -100.00000 -100.00000
1-25.00000 -25.00000   0.00000 -25.00000 -25.00000  -0.00000
0  1  132.288

0 10.00000  10.00000  10.00000   1.57080   1.57080   1.57080
2  8.66025   8.66025   8.66025   1.91063   1.91063   1.91063
0  0.00000   0.00000   0.00000 -100.00000 -100.00000 -100.00000
2-25.00000 -25.00000 -25.00000 -25.00000 -25.00000 -25.00000
0  2  136.931

1  7.07107   7.07107   7.07107   2.09440   2.09440   1.57080
2  8.66025   8.66025   8.66025   1.91063   1.91063   1.91063
1 -25.00000 -25.00000   0.00000 -25.00000 -25.00000  -0.00000
2 -25.00000 -25.00000 -25.00000 -25.00000 -25.00000 -25.00000
1  2  35.3553


