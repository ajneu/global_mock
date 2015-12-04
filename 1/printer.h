#ifndef PRINTER_H
#define PRINTER_H

#include "renderer.h"

class Printer {
public:
   Printer(Renderer &renderer) : renderer_(renderer)
   {   }

   void print(const char c) const {
      renderer_.print(c);
   }

private:
   Renderer &renderer_;
};

#endif
