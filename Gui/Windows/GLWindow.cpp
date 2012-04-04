/**
 * Application: AbstractGraph
 * Module: GUI
 * File: GLWindow.cpp
 * Description: Implementation for OpenGL window
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include <QtGui/QMouseEvent>

#include "GLWindow.h"
#include "graphix.h"

GLWindow::GLWindow(QWidget* parent)
  : QGLWidget(parent)
{
}

GLWindow::~GLWindow()
{
}

void GLWindow::initalizeGL()
{
  makeCurrent();
}

void GLWindow::resizeGL(int w, int h)
{
  scene.updateGLSize(w, h);
}

void GLWindow::paintGL()
{
  scene.updateScene();
}

void GLWindow::mousePressEvent(QMouseEvent* evt)
{
  Qt::MouseButton button = evt->button();
  
  // Make sure are coordinates are from the proper perspective
  QPoint pos(evt->x(), evt->y());
  mapFromGlobal(pos);
  int x = pos.x();
  int y = pos.y();
  
  if(button == Qt::LeftButton) {
    // Basically just adding circles now
    scene.addShape(GRAPHIX::CIRCLE, x, y);
    updateGL();
  }
}

void GLWindow::mouseMoveEvent(QMouseEvent* evt)
{
  // Not implemented
}

void GLWindow::keyPressEvent(QKeyEvent* evt)
{
  // Not implemented
}

