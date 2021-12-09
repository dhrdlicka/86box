#include "qt_hardwarerenderer.hpp"
#include <QApplication>

extern "C" {
#include <86box/86box.h>
}

void HardwareRenderer::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void HardwareRenderer::initializeGL()
{
    initializeOpenGLFunctions();
}

void HardwareRenderer::paintGL() {
    onPaint(this);
}

void HardwareRenderer::setRenderType(RenderType type) {
    QSurfaceFormat format;
    switch (type) {
    case RenderType::OpenGL:
        setTextureFormat(GL_RGB);
        format.setRenderableType(QSurfaceFormat::OpenGL);
        break;
    case RenderType::OpenGLES:
        setTextureFormat((QApplication::platformName().contains("wayland") || QApplication::platformName() == "cocoa") ? GL_RGB : GL_RGBA);
        format.setRenderableType(QSurfaceFormat::OpenGLES);
        break;
    }
    setFormat(format);
}

void HardwareRenderer::onBlit(const QImage& img, int x, int y, int w, int h) {
    image = img;
    source.setRect(x, y, w, h);
    update();
}

void HardwareRenderer::resizeEvent(QResizeEvent *event) {
    onResize(width(), height());
    QOpenGLWidget::resizeEvent(event);
}