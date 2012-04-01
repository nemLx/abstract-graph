/**
 * Application: AbstractGraph
 * Module: GUI
 * File: GLWindow.cpp
 * Description: Implementation for OpenGL window
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include "GLWindow.h"

GLWindow::GLWindow(QWidget* parent)
  : QGLWidget(parent)
{
}

GLWindow::~GLWindow()
{
  // Not implemented
}

void GLWindow::initalizeGL()
{
  // Some default code
  // Will eventually be moved out
  // to the library
  makeCurrent();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_COLOR_MATERIAL);
  glEnable(GL_BLEND);
  glEnable(GL_POLYGON_SMOOTH);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
}

void GLWindow::resizeGL(int w, int h)
{
  // Not implemented
}

void GLWindow::paintGL()
{
  // Just turn the background gray - nothing fancy for now
  makeCurrent();
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(139.0/255.0, 137.0/255.0, 137.0/255.0, 0.0);
}

void GLWindow::mousePressEvent(QMouseEvent* evt)
{
  // Not implemented
}

void GLWindow::mouseMoveEvent(QMouseEvent* evt)
{
  // Not implemented
}

void GLWindow::keyPressEvent(QKeyEvent* evt)
{
  // Not implemented
}

