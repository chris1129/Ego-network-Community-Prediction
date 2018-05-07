# Introduction:
This program constructs the ego-network for every node in the given network, runs decomposition algorithm for each ego-network and layouts the predicted circle based on the hierarchy decomposition.

# How to compile?
1. Put data file under data directory
2. `$make`
3. `$ ./circlePredict Filename Alg`

Alg can be 12 or 23. 12 is kcore,23 is ktruss.

# Output:
A folder named "Prediction" conatining prediction circle for each ego. One line per community.
