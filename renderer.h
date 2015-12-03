#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
public:
   virtual ~Renderer() {}
   virtual void print(char c) const =0;
};

#endif
