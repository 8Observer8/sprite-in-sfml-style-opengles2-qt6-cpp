#ifndef SPRITE_INFO_H
#define SPRITE_INFO_H

#include <QtCore/QJsonDocument>
#include <QtCore/QVector>
#include <QtGui/QVector2D>
#include <QtOpenGL/QOpenGLBuffer>

struct VertexBuffersData
{
    QOpenGLBuffer vertPosBuffer;
    QOpenGLBuffer texCoordBuffer;
    QVector<QVector2D> spriteSizes;
};

class SpriteInfo
{
public:
    static VertexBuffersData getInfo(
        const QJsonDocument &doc,
        const QStringList &spriteNames);
};

#endif // SPRITE_INFO_H
