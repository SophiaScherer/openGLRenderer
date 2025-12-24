#ifndef SHAPEDRAWER_H
#define SHAPEDRAWER_H

namespace gr {

  class GraphicsRenderer;
  class ShaderManager;

  class ShapeDrawer {
  public:
    explicit ShapeDrawer(GraphicsRenderer* renderer);
    ~ShapeDrawer() = default;

    void rectangle(float x,
               float y,
               float width,
               float height) const;

    void triangle(float x1,
                  float y1,
                  float x2,
                  float y2,
                  float x3,
                  float y3) const;

    void ellipse(float cx,
                  float cy,
                  float width,
                  float height) const;

  private:
    GraphicsRenderer* m_renderer;

    void setShadersForRendering(ShaderManager* shader);
  };

}

#endif //SHAPEDRAWER_H
