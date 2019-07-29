library("Rcpp")
dyn.load("/home/yaya/lib/libRcpp_distance.so")
.Call("rcpp_distance", "N",  "P", 100, 100, 100, 90, 90, 90, "P", 99, 99, 99, 89, 89, 89)
.Call("rcpp_distance", "S",  "P", 100, 100, 100, 90, 90, 90, "P", 99, 99, 99, 89, 89, 89)

