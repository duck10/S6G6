#include <RcppParallel.h>
using namespace RcppParallel;
#include <RcppArmadillo.h>
/* #include <RcppParallel.h>
using namespace RcppParallel; */


#include <vector>

#include "CS6Dist.h"
#include "G6.h"
#include "LatticeConverter.h"
#include "LRL_Cell.h"
#include "NCDist.h"
#include "S6.h"

extern "C" SEXP rcpp_distance( SEXP choice, SEXP lat1_, SEXP a1_, SEXP b1_, SEXP c1_,
   SEXP alpha1_, SEXP beta1_, SEXP gamma1_,
   SEXP lat2_, SEXP a2_, SEXP b2_, SEXP c2_,
   SEXP alpha2_, SEXP beta2_, SEXP gamma2_ ) {
   G6 prim1, prim2;

   const char typeDistance = toupper(Rcpp::as<std::string>( choice )[0]);

   LRL_Cell cell1, cell2;

   std::string lat1 = Rcpp::as<std::string>( lat1_ );
   cell1[0] = Rcpp::as<double>( a1_ );
   cell1[1] = Rcpp::as<double>( b1_ );
   cell1[2] = Rcpp::as<double>( c1_ );
   cell1[3] = Rcpp::as<double>( alpha1_ );
   cell1[4] = Rcpp::as<double>( beta1_ );
   cell1[5] = Rcpp::as<double>( gamma1_ );

   std::string lat2 = Rcpp::as<std::string>( lat2_ );
   cell2[0] = Rcpp::as<double>( a2_ );
   cell2[1] = Rcpp::as<double>( b2_ );
   cell2[2] = Rcpp::as<double>( c2_ );
   cell2[3] = Rcpp::as<double>( alpha2_ );
   cell2[4] = Rcpp::as<double>( beta2_ );
   cell2[5] = Rcpp::as<double>( gamma2_ );

   double answer = -1.0;

   if (typeDistance == 'S') {
      const S6 prim1 = LatticeConverter::SellingReduceCell( lat1, cell1 );
      const S6 prim2 = LatticeConverter::SellingReduceCell( lat2, cell2 );

      answer = 0.1*std::sqrt( CS6Dist( prim1.data( ), prim2.data( ) ) );
   } else if (typeDistance == 'G' || typeDistance == 'N') {
      const G6 prim1 = LatticeConverter::NiggliReduceCell( lat1, cell1 );
      const G6 prim2 = LatticeConverter::NiggliReduceCell( lat2, cell2 );

      answer = 0.1*std::sqrt( NCDist( prim1.data( ), prim2 .data( ) ) );
   }

   return Rcpp::wrap( answer );
}
