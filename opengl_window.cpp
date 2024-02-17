#include "opengl_window.h"
#include "sprite_info.h"

#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtGui/QVector3D>

OpenGLWindow::OpenGLWindow()
{
    setTitle("OpenGL ES 2.0, Qt6, C++");
    resize(350, 350);
}

OpenGLWindow::~OpenGLWindow()
{
    delete m_sprite;
    delete m_texture;
}

void OpenGLWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.02f, 0.61f, 0.85f, 1.f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_program = new QOpenGLShaderProgram(this);
    m_program->create();
    m_program->addShaderFromSourceFile(QOpenGLShader::ShaderTypeBit::Vertex,
        ":/assets/shaders/texture.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::ShaderTypeBit::Fragment,
        ":/assets/shaders/texture.frag");
    m_program->link();

    m_texture = new QOpenGLTexture(QOpenGLTexture::Target::Target2D);
    m_texture->create();
    m_texture->setData(QImage(":/assets/sprites/texture.png"));
    m_texture->setMinMagFilters(QOpenGLTexture::Filter::Nearest,
        QOpenGLTexture::Filter::Nearest);
    m_texture->setWrapMode(QOpenGLTexture::WrapMode::ClampToEdge);

    QFile file(":/assets/sprites/texture.json");
    file.open(QIODevice::OpenModeFlag::ReadOnly | QIODevice::OpenModeFlag::Text);
    QString content = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());
    QStringList spriteNames;
    spriteNames << "simple_level.png"
                << "enemy_walk_1.png"
                << "mario_dead.png"
                << "coin.png"
                << "mario_run_0.png";
    VertexBuffersData spriteInfo = SpriteInfo::getInfo(doc, spriteNames);

    m_sprite = new Sprite(m_program, spriteNames, spriteInfo, m_texture);

    m_viewMatrix.lookAt(QVector3D(0.f, 0.f, 1.f), QVector3D(0.f, 0.f, 0.f),
        QVector3D(0.f, 1.f, 0.f));
}

void OpenGLWindow::resizeGL(int w, int h)
{
    float aspect = w / (float)h;
    m_projMatrix.setToIdentity();
    if (w > h)
    {
        m_projMatrix.ortho(0.f, 128.f * aspect, 0.f, 128.f, 1.f, -1.f);
    }
    else
    {
        m_projMatrix.ortho(0.f, 128.f, 0.f, 128.f / aspect, 1.f, -1.f);
    }
    m_projViewMatrix = m_projMatrix * m_viewMatrix;
}

void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_sprite->setTextureRect("simple_level.png");
    m_sprite->setPosition(0 + 64, 0 + 64);
    m_sprite->draw(m_projViewMatrix);

    m_sprite->setTextureRect("enemy_walk_1.png");
    m_sprite->setPosition(16 * 1 + 64, -16 * 2 + 8 + 64);
    m_sprite->draw(m_projViewMatrix);

    m_sprite->setTextureRect("mario_dead.png");
    m_sprite->setPosition(0 + 64, 0 + 64);
    m_sprite->draw(m_projViewMatrix);

    m_sprite->setTextureRect("coin.png");
    m_sprite->setPosition(16 * 3 + 8 + 64, 16 * 1 + 8 + 64);
    m_sprite->draw(m_projViewMatrix);

    m_sprite->setTextureRect("mario_run_0.png");
    m_sprite->setPosition(16 * 2 + 8 + 64, 16 * 1 + 8 + 64);
    m_sprite->draw(m_projViewMatrix);
}

void OpenGLWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    m_texture->destroy();
}
