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

#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QImage>

#include "GLWindow.h"

#include "Menus/NodeOptionsMenu.h"
#include "Menus/MenuDefs.h"

#define FIXED_CANVAS_X 2000
#define FIXED_CANVAS_Y 2000

GLWindow::GLWindow(bool directed, QWidget* parent)
  : QGLWidget(parent), scene(directed), nodeRightClick(new NodeOptionsMenu(this)), locked(false), enableWeights(false), isMoving(false), leftButton(false), gluAlg(scene, this, directed), textPos(INSIDE)
{
  this->setMouseTracking(true);
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

void GLWindow::renderText(int x, int y, const QString& str, const QFont& font, int base)
{
  // Ensure color is black
  glColor3f(0.0, 0.0, 0.0);
  QGLWidget::renderText(x, y, str, font, base);
}

bool GLWindow::isLocked() const
{
  return locked;
}

void GLWindow::lock(bool lock)
{
  locked = lock;
}

bool GLWindow::exportGraph(const QString& name, const QString& type)
{  
  bool result = true;

  QImage image(grabFrameBuffer());

  result = image.save(name, type.toStdString().c_str());

  return result;
}

void GLWindow::showWeights(bool show)
{
  enableWeights = show;
}

int GLWindow::runAlgorithm(ALGORITHMS alg)
{
  scene.resetColors();
  int ret = gluAlg.runAlgorithm(alg);
  updateGL();
  return ret;
}

GRAPHIX::Scene& GLWindow::getScene()
{
  return scene;
}

AlgorithmsGlu& GLWindow::getGlue()
{
  return gluAlg;
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
    GRAPHIX::ACTION act = scene.registerClick(x, y);
    gluAlg.handleAction(act);
    leftButton = true;
    updateGL();
  }
}

void GLWindow::mouseReleaseEvent(QMouseEvent* evt)
{
  Qt::MouseButton button = evt->button();
  
  if(button == Qt::LeftButton && isMoving) {
    isMoving = false;
//    deselectAll();
  }
  leftButton = false;
}

void GLWindow::mouseMoveEvent(QMouseEvent* evt)
{
  // Make sure are coordinates are from the proper perspective
  QPoint pos(evt->pos());
  mapFromGlobal(pos);
  int x = pos.x();
  int y = pos.y();
  
  if(leftButton) {
    int dx = x - lastPos.first;
    int dy = y - lastPos.second;
    
    isMoving = true;
    
    // Move selected nodes
    scene.moveNodes(dx, dy);
    updateGL();
  }
  
  lastPos.first  = x;
  lastPos.second = y;
}

void GLWindow::keyPressEvent(QKeyEvent* evt)
{
  // Not implemented
}

void GLWindow::contextMenuEvent(QContextMenuEvent* evt)
{
  if(evt == NULL)
    return;
  
//  GRAPHIX::MODES currMode = scene.getMode();
  unsigned numSelected  = scene.countSelected();
  unsigned edgeSelected = scene.countSelected(GRAPHIX::LINE);
  bool selected = numSelected > 0;
  
  QPoint pos(evt->globalPos());
  nodeRightClick->updateMenuItems(selected, numSelected, edgeSelected);
  nodeRightClick->exec(pos);
}

void GLWindow::setLabelPosition(TEXTPOSITION pos)
{
  textPos = pos;
  deselectAll();
}

void GLWindow::setDirected(bool directed)
{
  if(scene.isDirected() == directed)
    return;
  scene = GRAPHIX::Scene(directed);
  gluAlg = AlgorithmsGlu(scene, this, directed);
}

void GLWindow::updateLabel()
{
  bool ok = false;
  QString label;
  std::vector<std::string> labels = scene.getSelectedLabels();
  
  if(labels.size() < 1)
    return;
  
  QString existingLabel(labels[0].c_str());
  
  if(labels.size() < 1)
    return;
  
  if(labels.size() == 1)
    label = QInputDialog::getText(this, tr("Add/Edit Label"), tr("Update Label:"),  QLineEdit::Normal, existingLabel, &ok);
  else
    label = QInputDialog::getText(this, tr("Add/Edit Label"), tr("Update Label:"),  QLineEdit::Normal, tr(""), &ok);
  
  if(ok) {
    scene.updateLabel(label.toStdString());
    deselectAll();
  }
}

void GLWindow::updateWeight()
{  
  bool ok = false;
  int weight;
  std::vector<int> weights = scene.getWeights();
  
  if(scene.getSelectedIds(GRAPHIX::LINE).size() < 1)
    return;
  
  if(weights.size() == 1)
    weight = QInputDialog::getInt(this, tr("Add/Edit Weight"), tr("Update Weight:"), weights[0], 0, 10000, 1, &ok);
  else
    weight = QInputDialog::getInt(this, tr("Add/Edit Weight"), tr("Update Weight:"), 0, 0, 10000, 1, &ok);
  
  if(ok && weight > -1) {
    enableWeights = true;
    scene.updateWeight(weight);
    gluAlg.updateEdgeWeight(weight);
    deselectAll();
  }
}

void GLWindow::updateColor()
{
  if(scene.getSelectedIds().size() < 1)
    return;
  
  QColor color = Qt::white;
  bool isValid = showColorDialog(color);
  
  if(isValid) {
    int red = 0;
    int green = 0;
    int blue = 0;
    color.getRgb(&red, &green, &blue);
    
    scene.updateSelectedColor(red, green, blue);
    
    deselectAll();
  }
}

void GLWindow::updateCurves()
{
  QMessageBox msg(QMessageBox::NoIcon, tr("Curve Type"), tr("Select curve type..."), QMessageBox::NoButton, this);
  msg.addButton(QMessageBox::Cancel);
  msg.addButton(tr("None"), QMessageBox::ResetRole);
  msg.addButton(tr("Up"), QMessageBox::AcceptRole);
  msg.addButton(tr("Down"), QMessageBox::YesRole);
  
  int ret = msg.exec();
  
  if(ret == QMessageBox::Cancel)
    return;
  
  switch(ret)
  {
    case 0:
      scene.setCurves();
      break;
    case 1:
      scene.setCurves(GRAPHIX::UP);
      break;
    case 2:
      scene.setCurves(GRAPHIX::DOWN);
      break;
    default:
      break;
  }
  
  deselectAll();
}

void GLWindow::deleteSelected()
{
  gluAlg.removeSelected();
  scene.deleteSelected();
  updateGL();
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
  std::vector<std::pair<float, float> > coords = scene.getCoords();
  std::vector<float> radii = scene.getRadii();
  
  if(labels.size() != coords.size())
    return;
  
  // The magic numbers are from screen position
  // will fix these later
  for(unsigned i = 0 ; i < labels.size() ; ++i) {
    if(labels[i].empty())
      continue;
    
    float x = coords[i].first;
    float y = coords[i].second;
    
    switch(textPos) {
      case LEFT:
        x -= 50;
        break;
      case RIGHT:
        x += 50;
        break;
      case UP:
        y -= 30;
        break;
      case DOWN:
        y += 30;
      case INSIDE:
      default:
        break;
    }
    
    x -= 15; // Center
    y += 5;
    
    renderText(x, y, QString(labels[i].c_str()));
  }
}

void GLWindow::drawWeights()
{
  if(!enableWeights)
    return;
  
  std::vector<int> weights = scene.getWeights();
  std::vector<std::pair<float, float> > coords = scene.getCoords(GRAPHIX::LINE);
  
  if(weights.size() != coords.size())
    return;
  
  for(unsigned i = 0 ; i < weights.size() ; ++i) {
    if(weights[i] < 0)
      continue;
    QString weight(QString::number(weights[i]));
    renderText(coords[i].first, coords[i].second, weight);
  }
}

bool GLWindow::showColorDialog(QColor& color)
{
  color = QColorDialog::getColor(color, this, tr("Select Color"));
  return color.isValid();
}
