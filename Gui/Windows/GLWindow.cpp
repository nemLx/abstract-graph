/**
 * Application: AbstractGraph
 * Module: GUI
 * File: GLWindow.cpp
 * Description: Implementation for OpenGL window
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include <string>
#include <utility>
#include <vector>

#include <QtGui/QColorDialog>
#include <QtGui/QInputDialog>
#include <QtGui/QMouseEvent>

#include "GLWindow.h"

#include "../Menus/NodeOptionsMenu.h"
#include "../Menus/MenuDefs.h"

#include "graphix.h"

GLWindow::GLWindow(QWidget* parent)
  : QGLWidget(parent), nodeRightClick(new NodeOptionsMenu(this)), locked(false)
{
}

GLWindow::~GLWindow()
{
}

void GLWindow::updateMode(GRAPHIX::MODES mode)
{
  if(locked)
    return;
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
  drawLabels();
  drawWeights();
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
  // Move exactly one node at a time for now
  if(scene.countSelected(GRAPHIX::CIRCLE) != 1 || scene.getMode() == GRAPHIX::VIEWONLY)
    return;
  
  // Make sure are coordinates are from the proper perspective
  QPoint pos(evt->pos());
  mapFromGlobal(pos);
  int x = pos.x();
  int y = pos.y();
  
  // Move selected nodes
  scene.moveNodes(x, y);
  updateGL();
}

void GLWindow::keyPressEvent(QKeyEvent* evt)
{
  // Not implemented
}

void GLWindow::contextMenuEvent(QContextMenuEvent* evt)
{
  if(evt == NULL)
    return;
  
  GRAPHIX::MODES currMode = scene.getMode();
  unsigned numSelected = (currMode == GRAPHIX::VIEWONLY) ? 0 : scene.countSelected();
  bool selected = numSelected > 0 && currMode != GRAPHIX::VIEWONLY;
  
  QPoint pos(evt->globalPos());
  nodeRightClick->updateMenuItems(selected, numSelected);
  nodeRightClick->exec(pos);
}

void GLWindow::deleteSelected()
{
  scene.deleteSelected();
  updateGL();
}

void GLWindow::updateColor()
{
  QColor color = Qt::white;
  bool isValid = showColorDialog(color);

  if(isValid) {
    int red = 0;
    int green = 0;
    int blue = 0;
    color.getRgb(&red, &green, &blue);
    
    scene.updateSelectedColor(red, green, blue);
    
    updateGL();
  }
}

void GLWindow::updateHighlight()
{
  QColor color = Qt::white;
  bool isValid = showColorDialog(color);
  
  if(isValid) {
    int red = 0;
    int green = 0;
    int blue = 0;
    color.getRgb(&red, &green, &blue);

    scene.updateHighlightColor(red, green, blue);

    updateGL();
  }
}

void GLWindow::updateBackground()
{
  QColor color = Qt::white;
  bool isValid = showColorDialog(color);
  
  if(isValid) {
    int red = 0;
    int green = 0;
    int blue = 0;
    color.getRgb(&red, &green, &blue);
    
    scene.updateBackground(red, green, blue);
    
    updateGL();
  }
}

void GLWindow::updateLabel()
{
  bool ok = false;
  QString label;
  std::vector<std::string> labels = scene.getSelectedLabels();
  QString existingLabel(labels[0].c_str());

  if(labels.size() == 1)
    label = QInputDialog::getText(this, tr("Add/Edit Label"), tr("Update Label:"),  QLineEdit::Normal, existingLabel, &ok);
  else
    label = QInputDialog::getText(this, tr("Add/Edit Label"), tr("Update Label:"),  QLineEdit::Normal, tr(""), &ok);
  
  if(ok) {
    scene.updateLabel(label.toStdString());
    updateGL();
  }
}

void GLWindow::updateWeight()
{
  bool ok;
  int weight;
  std::vector<int> weights = scene.getWeights();
  
  if(weights.size() == 1)
    weight = QInputDialog::getInt(this, tr("Add/Edit Weight"), tr("Update Weight (-1 to disable):"), weights[0], -1, 10000, 1, &ok);
  else
    weight = QInputDialog::getInt(this, tr("Add/Edit Weight"), tr("Update Weight (-1 to disable):"), 0, -1, 10000, 1, &ok);
  
  if(ok && weight > -2) {
    scene.updateWeight(weight);
    updateGL();
  }
}

void GLWindow::selectAll()
{
  scene.selectAll();
  updateGL();
}

void GLWindow::deselectAll()
{
  scene.deselectAll();
  updateGL();
}

void GLWindow::drawLabels()
{
  std::vector<std::string> labels = scene.getLabels();
  std::vector<std::pair<int, int> > coords = scene.getCoords();
  
  if(labels.size() != coords.size())
    return;
  
  for(unsigned i = 0 ; i < labels.size() ; ++i) {
    if(labels[i].empty())
      continue;
    renderText(coords[i].first, coords[i].second, QString(labels[i].c_str()));
  }
}

void GLWindow::drawWeights()
{
  std::vector<int> weights = scene.getWeights();
  std::vector<std::pair<int, int> > coords = scene.getCoords(GRAPHIX::LINE);
  
  if(weights.size() != coords.size())
    return;
  
  for(unsigned i = 0 ; i < weights.size() ; ++i) {
    if(weights[i] < 0)
      continue;
    QString weight("Weight: ");
    weight.append(QString::number(weights[i]));
    renderText(coords[i].first, coords[i].second, weight);
  }
}

bool GLWindow::showColorDialog(QColor& color)
{
  color = QColorDialog::getColor(color, this, tr("Select Color"));
  return color.isValid();
}
