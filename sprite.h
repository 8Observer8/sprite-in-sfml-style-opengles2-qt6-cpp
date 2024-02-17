#ifndef SPRITE_H
#define SPRITE_H

#include <QtCore/QStringList>
#include <QtCore/QVector>
#include <QtGui/QMatrix4x4>
#include <QtGui/QVector2D>
#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLTexture>

#include "sprite_info.h"

class Sprite
{
public:
    Sprite(QOpenGLShaderProgram *program, const QStringList &spriteNames,
        const VertexBuffersData &spriteInfo, QOpenGLTexture *texture);

    void draw(const QMatrix4x4 &projViewMatrix);
    void setPosition(float x, float y);
    void setSize(float w, float h);
    void setTextureRect(const QString &spriteName);

private:
    void bind();

private:
    QOpenGLShaderProgram *m_program;
    QStringList m_spriteNames;
    QOpenGLTexture *m_texture;
    QOpenGLBuffer m_vertPosBuffer;
    QOpenGLBuffer m_texCoordBuffer;
    QVector<QVector2D> m_spriteSizes;
    int m_drawingIndex = 0;
    float m_x = 0.f;
    float m_y = 0.f;
    float m_w;
    float m_h;
    QMatrix4x4 m_modelMatrix;
    QMatrix4x4 m_mvpMatrix;
    int m_aPositionLocation;
    int m_aTexCoordLocation;
    int m_uMvpMatrixLocation;
};

#endif // SPRITE_H
