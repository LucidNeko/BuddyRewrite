#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "systemopengl.h"

#include <memory>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "types.h"

class SpriteRenderer
{
public:
    static const unsigned int MAX_BATCH_SIZE;

public:
    struct SpriteData
    {
    public:
        glm::vec2 position;
        glm::vec2 size;
        glm::vec4 texInfo;
        glm::vec3 color;
        GLfloat   rotation;
    };

public:
    SpriteRenderer();
    ~SpriteRenderer();

    void render(const std::vector<EntityHandle>& entities);
    void flush();

private:
    void _render(EntityHandle entity);

private:
    std::shared_ptr<class ShaderProgram> _shader;
    GLuint _vao;
    GLuint _vbo;
    GLuint _quadVBO;

    std::shared_ptr<class Texture> _activeTexture;

    std::vector<SpriteData> _queuedSprites;
};

#endif // SPRITERENDERER_H
