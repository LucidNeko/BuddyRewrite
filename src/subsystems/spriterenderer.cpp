#include "spriterenderer.h"

#include <memory>
#include <cstdlib>

#include <QCoreApplication>
#include <QString>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "components/transform.h"
#include "components/sprite.h"
#include "entity.h"
#include "logging.h"
#include "resources/io/resources.h"
#include "resources/shaderprogram.h"
#include "resources/spritesheet.h"
#include "services.h"
#include "resources/texture.h"

const unsigned int SpriteRenderer::MAX_BATCH_SIZE = 5000;

SpriteRenderer::SpriteRenderer()
    : _shader(),
      _vao(0),
      _vbo(0),
      _quadVBO(0),
      _activeTexture(nullptr)
{
    auto R = Services::get<Resources>();
    R->load<ShaderProgram>("sprite");
    _shader = R->get<ShaderProgram>("sprite");

    glm::mat4 projection = glm::ortho(0.0f, float(640), float(480), 0.0f, -1.0f, 1.0f);

    _shader->bind();

    glUniform1i(_shader->getUniformLocation("spritesheet"), 0);

    glUniformMatrix4fv(_shader->getUniformLocation("projection"),
                       1, GL_FALSE, glm::value_ptr(projection));

    _shader->unbind();

    GLfloat quad[] = {
        // Position // TexCoord
        0.0f, 1.0f, //0.0f, 1.0f,
        0.0f, 0.0f, //0.0f, 0.0f,
        1.0f, 1.0f, //1.0f, 1.0f,
        1.0f, 0.0f, //1.0f, 0.0f
    };

    _queuedSprites.reserve(MAX_BATCH_SIZE);

    //GL_FLUSH_ERROR;

    // Vertex Position Buffer
    glGenBuffers(1, &_quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, MAX_BATCH_SIZE * sizeof(SpriteData), nullptr, GL_DYNAMIC_DRAW);

    // Unbind Buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Setup VAO
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    // Vertex Positions
    glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), reinterpret_cast<void*>(0));
    glVertexAttribDivisor(0, 0);

    // Sprite Data
    const int NUM_ATTRIBUTES = 6;

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    for(int attribute = 1; attribute < NUM_ATTRIBUTES; ++attribute)
    {
        glEnableVertexAttribArray(attribute);
    }

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteData), reinterpret_cast<void*>(0));                    // position
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteData), reinterpret_cast<void*>(sizeof(GLfloat) * 2));  // size
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteData), reinterpret_cast<void*>(sizeof(GLfloat) * 4));  // texInfo
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(SpriteData), reinterpret_cast<void*>(sizeof(GLfloat) * 8));  // color
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(SpriteData), reinterpret_cast<void*>(sizeof(GLfloat) * 11)); // rotation

    for(int attribute = 1; attribute < NUM_ATTRIBUTES; ++attribute)
    {
        glVertexAttribDivisor(attribute, 1);
    }

    // Unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GL_CHECK_ERROR;
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteBuffers(1, &_quadVBO);
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, & _vao);
}

void SpriteRenderer::render(const std::vector<EntityHandle>& entities)
{
    for(EntityHandle entity : entities)
    {
        _render(entity);
    }
}

void SpriteRenderer::_render(EntityHandle entity)
{
    std::shared_ptr<Transform> transform = entity->getComponent<Transform>();
    std::shared_ptr<Sprite> sprite = entity->getComponent<Sprite>();

    if(transform == nullptr) { return; }
    if(sprite == nullptr) { return; }

    if(_activeTexture != sprite->spriteSheet() || _queuedSprites.size() == MAX_BATCH_SIZE)
    {
        flush();
        _activeTexture = sprite->spriteSheet();
    }

    glm::vec2 centerBottom = transform->position() - (sprite->size() * glm::vec2(0.5f, 1));

    SpriteData data = {centerBottom,
                       sprite->size(),
                       sprite->textureCoords(),
                       sprite->color(),
                       GLfloat(transform->rotation())};

//    LOG_INFO("%s, %s, %s, %s, %f", glm::to_string(data.position).c_str(),
//              glm::to_string(data.size).c_str(),
//              glm::to_string(data.texInfo).c_str(),
//              glm::to_string(data.color).c_str(), data.rotation);


    _queuedSprites.push_back(data);
}

void SpriteRenderer::flush()
{
    if(_queuedSprites.empty() || _activeTexture == nullptr) { return; }

//    LOG_INFO("Flush");

    //GL_FLUSH_ERROR;

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, MAX_BATCH_SIZE * sizeof(SpriteData), nullptr, GL_DYNAMIC_DRAW); // Orphan Buffer
    glBufferSubData(GL_ARRAY_BUFFER, 0, _queuedSprites.size() * sizeof(SpriteData), &_queuedSprites[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

//    LOG_INFO("%d %d %d %d", _vao, _vbo, _quadVBO, _queuedSprites.size());

    _shader->bind();

    glActiveTexture(GL_TEXTURE0);
    _activeTexture->bind();

    glBindVertexArray(_vao);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, GLsizei(_queuedSprites.size()));
    glBindVertexArray(0);

    _activeTexture->unbind();

    _shader->unbind();

    _queuedSprites.clear();
    _activeTexture.reset();

    GL_CHECK_ERROR;
}
