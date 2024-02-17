#include "sprite_info.h"

#include <QtCore/QJsonObject>

VertexBuffersData SpriteInfo::getInfo(
    const QJsonDocument &doc,
    const QStringList &spriteNames)
{
    QJsonObject docObject = doc.object();
    QJsonObject metaObject = docObject["meta"].toObject();
    QJsonObject sizeObject = metaObject["size"].toObject();
    float atlasW = sizeObject["w"].toDouble();
    float atlasH = sizeObject["h"].toDouble();

    float vertPositions[spriteNames.length() * 8];
    float texCoords[spriteNames.length() * 8];
    QVector<QVector2D> spriteSizes;
    QJsonObject framesObject = docObject["frames"].toObject();

    for (int i = 0; i < spriteNames.length(); ++i)
    {
        vertPositions[i * 8 + 0] = -0.5f;
        vertPositions[i * 8 + 1] = 0.5f;
        vertPositions[i * 8 + 2] = -0.5f;
        vertPositions[i * 8 + 3] = -0.5f;
        vertPositions[i * 8 + 4] = 0.5f;
        vertPositions[i * 8 + 5] = 0.5f;
        vertPositions[i * 8 + 6] = 0.5f;
        vertPositions[i * 8 + 7] = -0.5f;

        QJsonObject spriteObject = framesObject[spriteNames[i]].toObject();
        QJsonObject frameObject = spriteObject["frame"].toObject();
        float tx = frameObject["x"].toDouble() / atlasW;
        float ty = frameObject["y"].toDouble() / atlasH;
        float tw = frameObject["w"].toDouble() / atlasW;
        float th = frameObject["h"].toDouble() / atlasH;

        texCoords[i * 8 + 0] = tx;
        texCoords[i * 8 + 1] = ty;
        texCoords[i * 8 + 2] = tx;
        texCoords[i * 8 + 3] = ty + th;
        texCoords[i * 8 + 4] = tx + tw;
        texCoords[i * 8 + 5] = ty;
        texCoords[i * 8 + 6] = tx + tw;
        texCoords[i * 8 + 7] = ty + th;

        float spriteW = frameObject["w"].toDouble();
        float spriteH = frameObject["h"].toDouble();
        spriteSizes.push_back(QVector2D(spriteW, spriteH));
    }

    QOpenGLBuffer vertPosBuffer;
    vertPosBuffer.create();
    vertPosBuffer.bind();
    vertPosBuffer.allocate(vertPositions, sizeof(vertPositions));

    QOpenGLBuffer texCoordBuffer;
    texCoordBuffer.create();
    texCoordBuffer.bind();
    texCoordBuffer.allocate(texCoords, sizeof(texCoords));

    VertexBuffersData output;
    output.vertPosBuffer = vertPosBuffer;
    output.texCoordBuffer = texCoordBuffer;
    output.spriteSizes = spriteSizes;

    return output;
}
