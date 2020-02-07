#ifndef LINE_H
#define LINE_H
#include "stdafx.h"
#include <memory>
#include <glm/glm.hpp>

class Shader;
class Vector;
class Line {
private:
        std::unique_ptr<Vector> m_Vector;
        std::unique_ptr<Shader> m_Shader;
        GLuint VAO;
public:
    void Draw();
    Line(std::unique_ptr<Vector> v);
    Line() = delete;
    ~Line() = default;
};
#endif
