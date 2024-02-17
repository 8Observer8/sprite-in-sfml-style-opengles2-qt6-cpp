#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include <QtGui/QCloseEvent>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLFunctions>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLTexture>
#include <QtOpenGL/QOpenGLWindow>

#include "sprite.h"

class OpenGLWindow : public QOpenGLWindow, private QOpenGLFunctions
{
public:
    OpenGLWindow();
    ~OpenGLWindow();

private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void closeEvent(QCloseEvent *event) override;

private:
    QOpenGLShaderProgram *m_program;
    QOpenGLTexture *m_texture;
    Sprite *m_sprite;
    QMatrix4x4 m_projMatrix;
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_projViewMatrix;
};

#endif // OPENGL_WINDOW_H
