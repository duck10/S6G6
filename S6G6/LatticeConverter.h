#ifndef LATTICECONVERTER_H
#define LATTICECONVERERT_H

#include "LRL_Cell.h"

class LatticeConverter {
   enum eOutputType { etext, emaxima };
private:
   eOutputType m_OutputType;

   void TextOutput  (const std::string& label, const std::string& lattice, const LRL_Cell& cell) const;

public:
   LatticeConverter(const eOutputType type = etext);

   void SetOutputMaxima(void);
   void SetOutputText(void);
   static LRL_Cell NiggliReduceCell(const std::string& lattice, const LRL_Cell& cell);
   static LRL_Cell SellingReduceCell(const std::string& lattice, const LRL_Cell& cell);
   static LRL_Cell MakePrimitiveCell(const std::string& lattice, const LRL_Cell& cell);
};
#endif //LATTICECONVERTER_H
