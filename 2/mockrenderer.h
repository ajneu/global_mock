#ifndef MOCK_RENDERER_H
#define MOCK_RENDERER_H

#include "renderer.h"
#include "gmock/gmock.h"

class MockRenderer : public Renderer {
public:
   ~MockRenderer() {
      std::cout << "Destructor of MockRenderer" << std::endl;
   }

   MOCK_CONST_METHOD1(print, void(char c));
};

#endif
