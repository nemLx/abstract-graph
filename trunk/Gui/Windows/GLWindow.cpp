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
#include "../Menus/NodeOptionsMenu.h"
#include "graphix.h"

GLWindow::GLWindow(QWidget* parent)
  : QGLWidget(parent), nodeRightClick(new NodeOptionsMenu(this))
{
}

GLWindow::~GLWindow()
{
}

void GLWindow::updateMode(GRAPHIX::MODES mode)
{
  scene.updateMode(mode);
  updateGL();
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
  QPoint pos(evt->pos());
  mapFromGlobal(pos);
  int x = pos.x();
  int y = pos.y();
  
  if(button == Qt::LeftButton) {
    scene.registerClick(x, y);
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

void GLWindow::contextMenuEvent(QContextMenuEvent* evt)
{
  if(evt == NULL)
    return;
  
  QPoint pos(evt->globalPos());
  nodeRightClick->updateMenuItems(scene.checkNodesSelected());
  nodeRightClick->exec(pos);
}

void GLWindow::deleteSelected()
{
  scene.deleteSelected();
  updateGL();
}

