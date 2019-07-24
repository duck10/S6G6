

#include "LRL_Cell.h"
#include "LRL_ToString.h"
#include "Niggli.h"
#include "S6.h"
#include "Selling.h"

#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include <string>

//StoreResults<std::string, G6> g_store(5);

/*
R5
1 0 0 0 0 0
0 1 0 0 0 0
0 1 1 -s 0 0
0 -2s 0 1 0 0
0 0 0 0 1 -s
0 0 0 0 0 1
*/

/*  class Niggli
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
A class to implement Niggli reduction in the G6 space. Reduce returns a reduced cell
   and the matrix that converts the input cell to the reduced cell.

   Reduced(void)
                 == constructor -- nothing to do here
   static void Reduce( const G6& vi, MatG6& m, G6& vout, const double delta )
                 == returns vout as the reduced cell of vi and m, the conversion matrix
   static bool NearRed( const G6& gvec, const double delta );
                 == determines whether gvec is reduced within delta
   static bool Near2Red( const G6& gvec, const double delta, G6& vout, double& dist )
                 == determines whether gvec is reduced within delta, and returns the reduced cell
                    and how far from reduced
   static void Reporter( const std::string& text, const G6& vin, const G6& vout, const MatG6& m )
                 == prints information about each step in reduction (including standard presentation)

private:
   static void MKnorm( const G6& vi, MatG6& m, G6& vout, const double delta  )
                 == internal function to convert vi to standard presentation - the matrix
                    to implement that change is returned
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

const bool DEBUG_REDUCER( false );
size_t Niggli::m_ReductionCycleCount;

//-----------------------------------------------------------------------------
// Name: g6sign()
// Description: returns the value of the first variable with the sign of the second
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
double g6sign( const double d, const double x )
{
   return(x > 0.0 ? d : -d);
}


//-----------------------------------------------------------------------------
// Name: Niggli()
// Description: constructor
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
Niggli::Niggli( void )
{
}

//-----------------------------------------------------------------------------
// Name: Niggli()
// Description: destructor
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
Niggli::~Niggli( void )
{
}

void Niggli::MKnormWithoutMatrices( const G6& vi, G6& vout, const double delta ) {

   /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   // These are the matrices that can be used to convert a vector to standard
   // presentation. They are used in MKnorm. There are NO OTHER POSSIBILITIES.
   // The numbering is from Andrews and Bernstein, 1988
   //const static MatG6 spnull("1 0 0 0 0 0   0 1 0 0 0 0   0 0 1 0 0 0   0 0 0 1 0 0   0 0 0 0 1 0   0 0 0 0 0 1");

   //const static MatG6 sp1("0 1 0 0 0 0   1 0 0 0 0 0   0 0 1 0 0 0   0 0 0 0 1 0   0 0 0 1 0 0   0 0 0 0 0 1");  //0,1  3,4
   //const static MatG6 sp2("1 0 0 0 0 0   0 0 1 0 0 0   0 1 0 0 0 0   0 0 0 1 0 0   0 0 0 0 0 1   0 0 0 0 1 0");  //1,2  4,5


   //const static MatG6 sp34a("1 0 0 0 0 0   0 1 0 0 0 0   0 0 1 0 0 0   0 0 0 -1 0 0   0 0 0 0 -1 0   0 0 0 0 0  1");  // -3,-4
   //const static MatG6 sp34b("1 0 0 0 0 0   0 1 0 0 0 0   0 0 1 0 0 0   0 0 0 -1 0 0   0 0 0 0  1 0   0 0 0 0 0 -1");  // -3,-5
   //const static MatG6 sp34c("1 0 0 0 0 0   0 1 0 0 0 0   0 0 1 0 0 0   0 0 0  1 0 0   0 0 0 0 -1 0   0 0 0 0 0 -1");  // -4,-5
   /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


   //const static MatG6 R5_Plus(" 1 0 0 0 0 0   0 1 0 0 0 0  0 1 1 -1 0 0   0 -2 0 1 0 0   0 0 0 0 1 -1   0 0 0 0 0 1");
   //const static MatG6 R5_Minus(" 1 0 0 0 0 0   0 1 0 0 0 0  0 1 1 +1 0 0   0 +2 0 1 0 0   0 0 0 0 1 +1   0 0 0 0 0 1");
   //const static MatG6 R6_Plus(" 1 0 0 0 0 0   0 1 0 0 0 0   1 0 1 0 -1 0   0 0 0 1 0 -1   -2 0 0 0 1 0   0 0 0 0 0 1");
   //const static MatG6 R6_Minus(" 1 0 0 0 0 0   0 1 0 0 0 0   1 0 1 0 +1 0   0 0 0 1 0 +1   +2 0 0 0 1 0   0 0 0 0 0 1");
   //const static MatG6 R7_Plus(" 1 0 0 0 0 0   1 1 0 0 0 -1   0 0 1 0 0 0   0 0 0 1 -1 0   0 0 0 0 1 0   -2 0 0 0 0 1");
   //const static MatG6 R7_Minus(" 1 0 0 0 0 0   1 1 0 0 0 +1   0 0 1 0 0 0   0 0 0 1 +1 0   0 0 0 0 1 0   +2 0 0 0 0 1");
   //const static MatG6 R8(" 1 0 0 0 0 0   0 1 0 0 0 0   1 1 1 1 1 1   0 2 0 1 0 1   2 0 0 0 1 1    0 0 0 0 0 1");
   //const static MatG6 R9_Plus(R5_Plus);
   //const static MatG6 R9_Minus(R5_Minus);
   //const static MatG6 R10_Plus(R6_Plus);
   //const static MatG6 R10_Minus(R6_Minus);
   //const static MatG6 R11_Plus(R7_Plus);
   //const static MatG6 R11_Minus(R7_Minus);
   //const static MatG6 R12("1 0 0 0 0 0   0 1 0 0 0 0   1 1 1 1 1 1   0 -2 0 -1 0 -1   -2 0 0 0 -1 -1   0 0 0 0 0 1");
   bool again = true;
   m_ReductionCycleCount = 0;
   G6 vin;

   vin = vi;

   double& g1 = vin[0];
   double& g2 = vin[1];
   double& g3 = vin[2];
   double& g4 = vin[3];
   double& g5 = vin[4];
   double& g6 = vin[5];



   // assure that g1<=g2<=g3
   while (again && (m_ReductionCycleCount < 5))
   {
      ++m_ReductionCycleCount;
      again = false;

      //std::string sptext;
      if ((fabs( vin[0] ) > fabs( vin[1] ) + delta + 1.e-12*(vin[0] + vin[1])) ||
         (fabs( vin[0] - vin[1] ) < 1.e-38 + 1.e-12*fabs( vin[0] + vin[1] )
            && delta<1.0E-12 && fabs( vin[3] )>fabs( vin[4] ) +
            delta + 1.e-12*(fabs( vin[3] ) + fabs( vin[4] ))))
      { // SP1   0,1  3,4
         //mat = sp1;
         std::swap( g1, g2 );
         std::swap( g4, g5 );
         again = true;
         //sptext = "SP1";
         //g_store.Store(sptext, vin);
      } else if ((fabs( vin[1] ) > fabs( vin[2] ) + delta + 1.e-12*(vin[1] + vin[2])) ||
         (fabs( vin[1] - vin[2] ) < 1.e-38 + 1.e-12*fabs( vin[1] + vin[2] )
            && delta<1.0E-12 && fabs( vin[4] )>fabs( vin[5] ) +
            delta + 1.e-12*(fabs( vin[4] ) + fabs( vin[5] ))))
      { // SP2 1,2  4,5
         //mat = sp2;
         std::swap( g2, g3 );
         std::swap( g5, g6 );
         again = true;
         //sptext = "SP2";
         //g_store.Store(sptext, vin);
      }

      //      DEBUG_REPORT_STRING(LRL_ToString( "   MKNORM input  "+sptext+"  ", vi));;
      //      DEBUG_REPORT_STRING(LRL_ToString( "   MKNORM output "+sptext+"  ", vout));;
   }

   // now we assure (within delta) that the vector is +++ or ---

   int bMinusPattern = 0;
   int bZeroPattern = 0;
   if (g4 < delta + 1.0E-13*(g2 + g3)) bMinusPattern |= 4;
   if (g5 < delta + 1.0E-13*(g1 + g3)) bMinusPattern |= 2;
   if (g6 < delta + 1.0E-13*(g1 + g2)) bMinusPattern |= 1;
   if (fabs( g4 ) < delta + 1.0E-13*(g2 + g3)) bZeroPattern |= 4;
   if (fabs( g5 ) < delta + 1.0E-13*(g1 + g3)) bZeroPattern |= 2;
   if (fabs( g6 ) < delta + 1.0E-13*(g1 + g2)) bZeroPattern |= 1;
   //std::string sptext2("Not_All_+++/---_in_MKnorm");

   switch (bMinusPattern)
   {
   case 0:  /*  +++  */
      {
         //mat = spnull;
         //sptext2 = "no_mknorm_action_sp1,sp2-0";
         //g_store.Store(sptext2, vin);
         break;
      }
   case 1:  /* ++- -> --- */
      {
         //mat = sp34a;
         g4 = -g4;
         g5 = -g5;
         //sptext2 = "SP34a-1";
         //g_store.Store(sptext2, vin);
         break;
      }
   case 2:  /* +-+ -> --- */
      {
         //mat = sp34b;
         g4 = -g4;
         g6 = -g6;
         //sptext2 = "SP34b-2";
         //g_store.Store(sptext2, vin);
         break;
      }
   case 3:  /* +-- -> +++, but +0- -> -0- and +-0 -> --0 and +00 -> -00 */
      {
         if ((bZeroPattern & 2) == 2) {
            //mat = sp34a;
            g4 = -g4;
            g5 = -g5;
            //sptext2 = "SP34a-3";
            //g_store.Store(sptext2, vin);
            break;
         } else if ((bZeroPattern & 1) == 1) {
            //mat = sp34b;
            //sptext2 = "SP34b-3";
            g4 = -g4;
            g6 = -g6;
            //g_store.Store(sptext2, vin);
            break;
         } else {
            //mat = sp34c;
            g5 = -g5;
            g6 = -g6;
            //sptext2 = "SP34c-3";
            //g_store.Store(sptext2, vin);
         }
         break;
      }
   case 4:  /* -++ -> --- */
      {
         //mat = sp34c;
         g5 = -g5;
         g6 = -g6;
         //sptext2 = "SP34c-4";
         //g_store.Store(sptext2, vin);
         break;
      }
   case 5:  /* -+- -> +++, but 0+- -> 0-- and -+0 -> --0 and 0+0 -> 0-0 */
      {
         //mat = sp34b;
         //sptext2 = "SP34b-5";
         if ((bZeroPattern & 4) == 4) {
            //mat = sp34a;
            g4 = -g4;
            g5 = -g5;
            //sptext2 = "SP34a-5";
            //g_store.Store(sptext2, vin);
            break;
         } else if ((bZeroPattern & 1) == 1) {
            //mat = sp34c;
            //sptext2 = "SP34c-5a";
            g5 = -g5;
            g6 = -g6;
            //g_store.Store(sptext2, vin);
            break;
         } else {
            //mat = sp34b;
            g4 = -g4;
            g6 = -g6;
            //sptext2 = "SP34b-5";
            //g_store.Store(sptext2, vin);
         }
         break;
      }
   case 6:  /* --+ - > +++, but 0-+ -> 0-- and -0+ - > -0- and 00+ -> 00- */
      {
         if ((bZeroPattern & 4) == 4) {
            //mat = sp34b;
            g4 = -g4;
            g6 = -g6;
            //sptext2 = "SP34b-5";
            ////g_store.Store(sptext2, vin);
            break;
         } else if ((bZeroPattern & 2) == 2) {
            //mat = sp34c;
            g5 = -g5;
            g6 = -g6;
            //sptext2 = "SP34c-5";
            //g_store.Store(sptext2, vin);
            break;
         } else {
            //mat = sp34a;
            g4 = -g4;
            g5 = -g5;
            //sptext2 = "SP34a-6";
            //g_store.Store(sptext2, vin);
         }
         break;
      }
   case 7:
      {
         //mat = spnull;
         //sptext2 = "no-mknorm_action_sp1,sp2-7";
         //g_store.Store(sptext2, vin);
         break;
      }
   }

   //vout = mat * vin;
   vout = vin;
   //   DEBUG_REPORT_STRING(LRL_ToString( "      MKNORM input  "+sptext2+"  ", vi));;
   //   DEBUG_REPORT_STRING(LRL_ToString( "      MKNORM output "+sptext2+"  ", vout));;
   //std::cout << std::flush;
}

//-----------------------------------------------------------------------------
// Name: MKnorm()
// Description: changes a G6 vector to standard presentation (often called
//              normalization in the literature) and returns the standard
//              vector and the matrix that changes the input vector to the
//              standard one
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//void Niggli::MKnorm( const G6& vi, MatG6& m, G6& vout, const double delta  ) {
// 
///*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
///*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
///*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//// These are the matrices that can be used to convert a vector to standard
//// presentation. They are used in MKnorm. There are NO OTHER POSSIBILITIES.
//// The numbering is from Andrews and Bernstein, 1988
//   //const static MatG6 spnull( "1 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0 1" );
//
//   //const static MatG6 sp1( "0 1 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 1" );
//   //const static MatG6 sp2( "1 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 1 0" );
//
//
//   //const static MatG6 sp34a( "1 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0 -1 0 0 0 0 0 0 -1 0 0 0 0 0 0  1" );
//   //const static MatG6 sp34b( "1 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0 -1 0 0 0 0 0 0  1 0 0 0 0 0 0 -1" );
//   //const static MatG6 sp34c( "1 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0  1 0 0 0 0 0 0 -1 0 0 0 0 0 0 -1" );
///*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
///*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
///*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//
//
////const static MatG6 R5_Plus  (" 1 0 0 0 0 0   0 1 0 0 0 0  0 1 1 -1 0 0   0 -2 0 1 0 0   0 0 0 0 1 -1   0 0 0 0 0 1");
////const static MatG6 R5_Minus (" 1 0 0 0 0 0   0 1 0 0 0 0  0 1 1 +1 0 0   0 +2 0 1 0 0   0 0 0 0 1 +1   0 0 0 0 0 1");
////const static MatG6 R6_Plus  (" 1 0 0 0 0 0   0 1 0 0 0 0   1 0 1 0 -1 0   0 0 0 1 0 -1   -2 0 0 0 1 0   0 0 0 0 0 1");
////const static MatG6 R6_Minus (" 1 0 0 0 0 0   0 1 0 0 0 0   1 0 1 0 +1 0   0 0 0 1 0 +1   +2 0 0 0 1 0   0 0 0 0 0 1"); 
////const static MatG6 R7_Plus  (" 1 0 0 0 0 0   1 1 0 0 0 -1   0 0 1 0 0 0   0 0 0 1 -1 0   0 0 0 0 1 0   -2 0 0 0 0 1");
////const static MatG6 R7_Minus (" 1 0 0 0 0 0   1 1 0 0 0 +1   0 0 1 0 0 0   0 0 0 1 +1 0   0 0 0 0 1 0   +2 0 0 0 0 1");
////const static MatG6 R8       (" 1 0 0 0 0 0   0 1 0 0 0 0   1 1 1 1 1 1   0 2 0 1 0 1   2 0 0 0 1 1    0 0 0 0 0 1");
////const static MatG6 R9_Plus(R5_Plus);
////const static MatG6 R9_Minus(R5_Minus);
////const static MatG6 R10_Plus(R6_Plus);
////const static MatG6 R10_Minus(R6_Minus);
////const static MatG6 R11_Plus(R7_Plus);
////const static MatG6 R11_Minus(R7_Minus);
//////const MatG6 R12(R8);
////const static MatG6 R12      ( "1 0 0 0 0 0   0 1 0 0 0 0   1 1 1 1 1 1   0 -2 0 -1 0 -1   -2 0 0 0 -1 -1   0 0 0 0 0 1");
//   bool again = true;
//   m_ReductionCycleCount = 0;
//   MatG6 mat = MatG6::Eye();
//   G6 vin;
//   m = MatG6::Eye();
//
//   vin = vi;
//
//   // assure that g1<=g2<=g3
//   while ( again && (m_ReductionCycleCount < 5) )
//   {
//      ++m_ReductionCycleCount;
//      again = false;
//
//      std::string sptext;
//      if ( (fabs(vin[0]) > fabs(vin[1])+delta+1.e-12*(vin[0]+vin[1])) ||
//           (fabs(vin[0]-vin[1])<1.e-38+1.e-12*fabs(vin[0]+vin[1])
//	    && delta<1.0E-12 && fabs(vin[3])>fabs(vin[4])+
//	    delta+1.e-12*(fabs(vin[3])+fabs(vin[4]))))
//      { // SP1
//         mat    = sp1;
//         again  = true;
//         sptext = "SP1";
//      }
//      else if ( (fabs(vin[1]) > fabs(vin[2])+delta+1.e-12*(vin[1]+vin[2])) ||
//                (fabs(vin[1]-vin[2])<1.e-38+1.e-12*fabs(vin[1]+vin[2])
//                 && delta<1.0E-12 && fabs(vin[4])>fabs(vin[5])+
//                 delta+1.e-12*(fabs(vin[4])+fabs(vin[5]))))
//      { // SP2
//         mat    = sp2;
//         again  = true;
//         sptext = "SP2";
//      }
//
//      if ( again )
//      {
//         // Accumulate the total transformation from the input vector into vout and
//         // the total transformation itself into matrix m.
//         const MatG6 mtemp = mat*m;
//         m = mtemp;
//         vout = mat*vin;
//         Reporter( sptext, vin, vout, mat );
//         vin = vout;
//      }
////      DEBUG_REPORT_STRING(LRL_ToString( "   MKNORM input  "+sptext+"  ", vi));;
////      DEBUG_REPORT_STRING(LRL_ToString( "   MKNORM output "+sptext+"  ", vout));;
//   }
//
//   // now we assure (within delta) that the vector is +++ or ---
//
//   int bMinusPattern = 0;
//   int bZeroPattern = 0;
//   if( vin[3] < delta+1.0E-13*(vin[1]+vin[2]) ) bMinusPattern |= 4;
//   if( vin[4] < delta+1.0E-13*(vin[0]+vin[2]) ) bMinusPattern |= 2;
//   if( vin[5] < delta+1.0E-13*(vin[0]+vin[1]) ) bMinusPattern |= 1;
//   if( fabs(vin[3]) < delta+1.0E-13*(vin[1]+vin[2]) ) bZeroPattern |= 4;
//   if( fabs(vin[4]) < delta+1.0E-13*(vin[0]+vin[2]) ) bZeroPattern |= 2;
//   if( fabs(vin[5]) < delta+1.0E-13*(vin[0]+vin[1]) ) bZeroPattern |= 1;
//   std::string sptext2( "Not_All_++ + / -- - _in_MKnorm" );
//
//   switch( bMinusPattern )
//   {
//   case 0:  /*  +++  */
//      {
//         mat = spnull;
//         sptext2 = "no_mknorm_action_sp1,sp2-0";
//         break;
//      }
//   case 1:  /* ++- -> --- */
//      {
//         mat = sp34a;
//         sptext2 = "SP34a-1";
//         break;
//      }
//   case 2:  /* +-+ -> --- */
//      {
//         mat = sp34b;
//         sptext2 = "SP34b-2";
//         break;
//      }
//   case 3:  /* +-- -> +++, but +0- -> -0- and +-0 -> --0 and +00 -> -00 */
//      {
//         mat = sp34c;
//         sptext2 = "SP34c-3";
//         if ((bZeroPattern&2) == 2 ) {
//            mat = sp34a;
//            sptext2 = "SP34a-3";
//            break;
//         }
//         if ((bZeroPattern&1) == 1 ) {
//            mat = sp34b;
//            sptext2 = "SP34b-3";
//            break;
//         }
//         break;
//      }
//   case 4:  /* -++ -> --- */
//      {
//         mat = sp34c;
//         sptext2 = "SP34c-4";
//         break;
//      }
//   case 5:  /* -+- -> +++, but 0+- -> 0-- and -+0 -> --0 and 0+0 -> 0-0 */
//      {
//         mat = sp34b;
//         sptext2 = "SP34b-5";
//         if ((bZeroPattern&4) == 4 ) {
//            mat = sp34a;
//            sptext2 = "SP34a-5";
//            break;
//         }
//         if ((bZeroPattern&1) == 1 ) {
//            mat = sp34c;
//            sptext2 = "SP34c-5";
//            break;
//         }
//         break;
//      }
//   case 6:  /* --+ - > +++, but 0-+ -> 0-- and -0+ - > -0- and 00+ -> 00- */
//      {
//         mat = sp34a;
//         sptext2 = "SP34a-6";
//         if ((bZeroPattern&4) == 4 ) {
//            mat = sp34b;
//            sptext2 = "SP34b-5";
//            break;
//         }
//         if ((bZeroPattern&2) == 2 ) {
//            mat = sp34c;
//            sptext2 = "SP34c-5";
//            break;
//         }
//         break;
//      }
//   case 7:
//      {
//         mat = spnull;
//         sptext2 = "no_mknorm_action_sp1,sp2-7";
//         break;
//      }
//   }
//
//   // Accumulate the total transformation from the input vector into vout and
//   // the total transformation itself into matrix m.
//   const MatG6 mtemp = mat*m;
//   m = mtemp;
//   vout = mat*vin;
////   DEBUG_REPORT_STRING(LRL_ToString( "      MKNORM input  "+sptext2+"  ", vi));;
////   DEBUG_REPORT_STRING(LRL_ToString( "      MKNORM output "+sptext2+"  ", vout));;
//   std::cout << std::flush;
//   Reporter( sptext2, vin, vout, mat );
//}  // end MKnorm

bool Niggli::Reduce( const G6& vi, G6& vout ) {
   return ReduceWithoutMatrices( vi, vout, 0.0 );
}

//bool Niggli::Reduce(const G6& vi, G6& vout, const bool sellingFirst) {
//   if ( IsNiggli(vi) ) {
//      vout = vi;
//      return true;
//   }
//   S6 s6out;
//   bool b = true;
//   if (sellingFirst) {
//      b = Selling::Reduce(S6(vi), s6out);
//      vout = G6(s6out);
//   }
//   else {
//      vout = vi;
//   }
//
//   if (!b) {
//      MatG6 m;
//      const bool bniggli = Niggli::Reduce(vi, m, vout, 0.0);
//      return bniggli;
//   }
//   else if (IsNiggli(vout)) {
//      return true;
//   }
//   else {
//      MatG6 m;
//      return Niggli::Reduce(vout, m, vout, 0.0);
//   }
//}

bool Niggli::ReduceWithoutMatrices( const G6& vi, G6& vout, const double delta )
{

   if (Niggli::IsNiggli( vi )) {
      vout = vi;
      return true;
   }

   /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   // These are the matrices that can be used to convert a vector to standard
   // presentation. They are used in MKnorm. There are NO OTHER POSSIBILITIES.
   // The numbering is from Andrews and Bernstein, 1988
   //const static MatG6 spnull("1 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0 1");

   //const static MatG6 sp1("0 1 0 0 0 0   1 0 0 0 0 0   0 0 1 0 0 0   0 0 0 0 1 0   0 0 0 1 0 0   0 0 0 0 0 1");
   //const static MatG6 sp2("1 0 0 0 0 0   0 0 1 0 0 0   0 1 0 0 0 0   0 0 0 1 0 0   0 0 0 0 0 1   0 0 0 0 1 0");


   //const static MatG6 sp34a("1 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0 -1 0 0 0 0 0 0 -1 0 0 0 0 0 0  1");
   //const static MatG6 sp34b("1 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0 -1 0 0 0 0 0 0  1 0 0 0 0 0 0 -1");
   //const static MatG6 sp34c("1 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0  1 0 0 0 0 0 0 -1 0 0 0 0 0 0 -1");
   /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
   /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


   //const static MatG6 R5_Plus(" 1 0 0 0 0 0   0 1 0 0 0 0  0 1 1 -1 0 0   0 -2 0 1 0 0   0 0 0 0 1 -1   0 0 0 0 0 1");
   //const static MatG6 R5_Minus(" 1 0 0 0 0 0   0 1 0 0 0 0  0 1 1 +1 0 0   0 +2 0 1 0 0   0 0 0 0 1 +1   0 0 0 0 0 1");
   //const static MatG6 R6_Plus(" 1 0 0 0 0 0   0 1 0 0 0 0   1 0 1 0 -1 0   0 0 0 1 0 -1   -2 0 0 0 1 0   0 0 0 0 0 1");
   //const static MatG6 R6_Minus(" 1 0 0 0 0 0   0 1 0 0 0 0   1 0 1 0 +1 0   0 0 0 1 0 +1   +2 0 0 0 1 0   0 0 0 0 0 1");
   //const static MatG6 R7_Plus(" 1 0 0 0 0 0   1 1 0 0 0 -1   0 0 1 0 0 0   0 0 0 1 -1 0   0 0 0 0 1 0   -2 0 0 0 0 1");
   //const static MatG6 R7_Minus(" 1 0 0 0 0 0   1 1 0 0 0 +1   0 0 1 0 0 0   0 0 0 1 +1 0   0 0 0 0 1 0   +2 0 0 0 0 1");
   //const static MatG6 R8(" 1 0 0 0 0 0   0 1 0 0 0 0   1 1 1 1 1 1   0 2 0 1 0 1   2 0 0 0 1 1    0 0 0 0 0 1");
   //const static MatG6 R9_Plus(R5_Plus);
   //const static MatG6 R9_Minus(R5_Minus);
   //const static MatG6 R10_Plus(R6_Plus);
   //const static MatG6 R10_Minus(R6_Minus);
   //const static MatG6 R11_Plus(R7_Plus);
   //const static MatG6 R11_Minus(R7_Minus);
   //const MatG6 R12(R8);
   //const static MatG6 R12("1 0 0 0 0 0   0 1 0 0 0 0   1 1 1 1 1 1   0 -2 0 -1 0 -1   -2 0 0 0 -1 -1   0 0 0 0 0 1");
   G6 vin;
   m_ReductionCycleCount = 0;
   bool again = true;
   const bool debug = true;

   const int maxCycle = 260;

   vin = vi;
   G6 voutPrev( vin );

   /* Mapping from Fortran indices:

   1  2  3  4  5  6
   0  6 12 18 24 30

   7  8  9 10 11 12
   1  7 13 19 25 31

   13 14 15 16 17 18
   2  8 14 20 26 32

   19 20 21 22 23 24
   3  9 15 21 27 33

   25 26 27 28 29 30
   4 10 16 22 28 34

   31 32 33 34 35 36
   5 11 17 23 29 35

   */

   // Try some number of times to reduce the input vector and accumulate
   // the changing vector and total transformation matrix
   // The limit on the number of cycles is because (whether because of
   // floating point rounding or algorithm issues) there might be a
   // case of an infinite loop. The designations R5-R12 are from

   double& g1 = vout[0];
   double& g2 = vout[1];
   double& g3 = vout[2];
   double& g4 = vout[3];
   double& g5 = vout[4];
   double& g6 = vout[5];

   // Andrews and Bernstein, 1988
   while (again && m_ReductionCycleCount < maxCycle)
   {
      MKnormWithoutMatrices( vin, vout, delta );
      vin = vout;

      if (fabs( g4 ) > fabs( g2 ) + delta)
      { // R5
         again = true;
         if (g4 <= 0.0) {
            g3 = g2 + g3 + g4;  // R5_Minus & R9_Minus
            g4 = 2 * g2 + g4;
            g5 = g5 + g6;
         } else {
            g3 = g2 + g3 - g4;  // R5_Plus & R9_Plus
            g4 = -2 * g2 + g4;
            g5 = g5 - g6;
         }
      } else if (fabs( g5 ) > fabs( g1 ) + delta)
      { // R6
         again = true;
         if (g5 <= 0.0) {
            g3 = g1 + g3 + g5;  // R6_Minus & R10_Minus
            g4 = g4 + g6;
            g5 = 2 * g1 + g5;
         } else {
            g3 = g1 + g3 - g5;  // R6_Plus & R10_Plus
            g4 = g4 - g6;
            g5 = -2 * g1 + g5;
         }
      } else if (fabs( g6 ) > fabs( g1 ) + delta)
      { // R7
         again = true;
         if (g6 <= 0.0) {
            g2 = g1 + g2 + g6;  // R7_Minus & R11_Minus
            g4 = g4 + g5;
            g6 = 2 * g1 + g6;
         } else {
            g2 = g1 + g2 - g6;  // R7_Plus && R11_Plus
            g4 = g4 - g5;
            g6 = -2 * g1 + g6;
         }
      } else if (g4 + g5 + g6 + fabs( g1 ) + fabs( g2 ) + delta < 0.0)
      { //R8
         again = true;
         g3 = g1 + g2 + g3 + g4 + g5 + g6;  //  R8
         g4 = 2 * g2 + g4 + g6;
         g5 = 2 * g1 + g5 + g6;
      } else if ((fabs( g4 - g2 ) <= delta && 2.0*g5 - delta < g6) ||
         (fabs( g4 + g2 ) <= delta && g6 < 0.0))
      { // R9  There is an error in the paper says "2g5<g5" should be "2g5<g6"
         again = true;
         if (g4 <= 0.0) {
            g3 = g2 + g3 + g4;  // R5_Minus & R9_Minus
            g4 = 2 * g2 + g4;
            g5 = g5 + g6;
         } else {
            g3 = g2 + g3 - g4;  // R5_Plus & R9_Plus
            g4 = -2 * g2 + g4;
            g5 = g5 - g6;
         }
      } else if ((fabs( g5 - g1 ) <= delta && 2.0*g4 - delta < g6) ||
         (fabs( g5 + g1 ) <= delta && g6 < 0.0))
      { //R10 (LAST=15 in ITERATE)
         again = true;
         if (g5 <= 0.0) {
            g3 = g1 + g3 + g5;  // R6_Minus & R10_Minus
            g4 = g4 + g6;
            g5 = 2 * g1 + g5;
         } else {
            g3 = g1 + g3 - g5;  // R6_Plus & R10_Plus
            g4 = g4 - g6;
            g5 = -2 * g1 + g5;
         }
      } else if ((fabs( g6 - g1 ) <= delta && 2.0*g4 - delta < g5) ||
         (fabs( g6 + g1 ) <= delta && g5 < 0.0)) // paper says g6<0, but it seems wrong
      { // R11
         again = true;
         if (g6 <= 0.0) {
            g2 = g1 + g2 + g6;  // R7_Minus & R11_Minus
            g4 = g4 + g5;
            g6 = 2 * g1 + g6;
         } else {
            g2 = g1 + g2 - g6;  // R7_Plus && R11_Plus
            g4 = g4 - g5;
            g6 = -2 * g1 + g6;
         }
      } else if (fabs( g4 + g5 + g6 + fabs( g1 ) + fabs( g2 ) ) <= delta && (2.0*(fabs( g1 ) + g5) + g6 > delta))
      { //R12 
         again = true;
         g3 = g1 + g2 + g3 + g4 + g5 + g6;  //  R12
         g4 = -2 * g2 - g4 - g6;
         g5 = -2 * g1 - g5 - g6;
      } else
      {
         again = false;
         vout = vin;
      }

      // probably don't need to do this group of code when again==false !!!!!!!!!!!!!!
      MKnormWithoutMatrices( vout, vin, delta );
      for (size_t i = 3; i < 6; ++i)
         if (std::fabs( vin[i] ) < 1.0E-10) vin[i] = 0.0;

      if (m_ReductionCycleCount == 0) voutPrev = vin;

      ++m_ReductionCycleCount;
   }
   return true;
}

bool Niggli::IsNiggli(const G6& v) {
   const double& g1 = v[0];
   const double& g2 = v[1];
   const double& g3 = v[2];
   const double& g4 = v[3];
   const double& g5 = v[4];
   const double& g6 = v[5];


   const double delta = 10E-6;

   if (g1 <= 0.0) return false;
   if (g2 <= 0.0) return false;
   if (g3 <= 0.0) return false;

   if (g1 > g2) return false;
   if (g2 > g3) return false;

   if (abs(g4) > g2) return false;
   if (abs(g5) > g1) return false;
   if (abs(g6) > g1) return false;
   int nneg = 0;
   for (size_t i = 3; i < 6; ++i) if (v[i] <= 0.0) ++nneg;
   if (nneg != 0 && nneg != 3) return false;

   if (g4 == g2 && g6 > 2.0*g5) return false;
   if (g5 == g1 && g6 > 2.0*g4) return false;
   if (g6 == g1 && g5 > 2.0*g4) return false;


   if (abs(g2 - g3) < delta && abs(g5) > abs(g6)) return false;
   if (abs(g3) > g1 + g2 + g3 + g4 + g5 + g6) return false;

   if (g4 == g2 && g6 != 0) return false;
   if (g5 == g1 && g6 != 0) return false;
   if (g6 == g1 && g5 != 0) return false;

   if (g3 == (g1 + g2 + g3 + g4 + g5 + g6) && 2.0*(g1 + g5) > 0.0) return false;

   return true;
}
