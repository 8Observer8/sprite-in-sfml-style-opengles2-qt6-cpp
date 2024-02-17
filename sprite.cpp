#include "sprite.h"

Sprite::Sprite(QOpenGLShaderProgram *program, const QStringList &spriteNames,
    const VertexBuffersData &spriteInfo, QOpenGLTexture *texture)
    : m_program(program)
    , m_spriteNames(spriteNames)
    , m_texture(texture)
{
    m_vertPosBuffer = spriteInfo.vertPosBuffer;
    m_texCoordBuffer = spriteInfo.texCoordBuffer;
    m_spriteSizes = spriteInfo.spriteSizes;
    m_w = m_spriteSizes[0].x();
    m_h = m_spriteSizes[0].y();

    m_program->bind();
    m_aPositionLocation = m_program->attributeLocation("aPosition");
    m_aTexCoordLocation = m_program->attributeLocation("aTexCoord");
    m_uMvpMatrixLocation = m_program->uniformLocation("uMvpMatrix");
}

void Sprite::setPosition(float x, float y)
{
    m_x = x;
    m_y = y;
}

void Sprite::setSize(float w, float h)
{
    m_w = w;
    m_h = h;
}

void Sprite::setTextureRect(const QString &spriteName)
{
    int index = m_spriteNames.indexOf(spriteName);
    m_w = m_spriteSizes[index].x();
    m_h = m_spriteSizes[index].y();
    m_drawingIndex = index * 4;
}

void Sprite::bind()
{
    m_program->bind();
    m_texture->bind();

    m_vertPosBuffer.bind();
    m_program->setAttributeBuffer(m_aPositionLocation, GL_FLOAT, 0, 2);
    m_program->enableAttributeArray(m_aPositionLocation);

    m_texCoordBuffer.bind();
    m_program->setAttributeBuffer(m_aTexCoordLocation, GL_FLOAT, 0, 2);
    m_program->enableAttributeArray(m_aTexCoordLocation);
}

void Sprite::draw(const QMatrix4x4 &projViewMatrix)
{
    bind();
    m_modelMatrix.setToIdentity();
    m_modelMatrix.translate(m_x, m_y);
    m_modelMatrix.scale(m_w, m_h, 1.f);
    m_mvpMatrix = projViewMatrix * m_modelMatrix;
    m_program->setUniformValue(m_uMvpMatrixLocation, m_mvpMatrix);
    glDrawArrays(GL_TRIANGLE_STRIP, m_drawingIndex, 4);
}
