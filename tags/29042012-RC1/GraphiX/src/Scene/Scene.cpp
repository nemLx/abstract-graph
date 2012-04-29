/**
 * Application: GraphiX Library
 * Module: Library
 * File: Scene.cpp
 * Description: Scene implementation
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include "Gfx/Shape.h"
#include "Gfx/Circle.h"
#include "Gfx/Line.h"

#include "Scene/Scene.h"

#include "Control/NodeCreationMode.h"
#include "Control/EdgeCreationMode.h"
#include "Control/EditMode.h"

#include <cmath>

#define GRAPHIX_DEFAULT_PICK_BUFFER_SIZE 16

namespace GRAPHIX
{
Scene::Scene(bool directed)
  : highlight(Color(0.0, 0.0, 255.0, 0.0)), background(Color(255.0, 255.0, 255.0, 0.0)), directed(directed), xFactor(1.0f),
  yFactor(1.0f)
{
  bufferSize = GRAPHIX_DEFAULT_PICK_BUFFER_SIZE;
  pickBuffer = new unsigned[bufferSize];
  
  modes[NODECREATION] = new NodeCreationMode(&shapes, &selected, highlight);
  modes[EDGECREATION] = new EdgeCreationMode(&shapes, &selected, highlight);
  modes[EDIT] = new EditMode(&shapes, &selected, highlight);
  
  // Default in Node Creation Mode for now
  currentMode = modes[NODECREATION];
  
  // Only supporting 2D for now
  glDisable(GL_DEPTH_TEST);

  glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
}

Scene::~Scene()
{
  destroy();
}
  
Scene::Scene(const Scene& rhs)
{
  copy(rhs);
}

Scene& Scene::operator=(const Scene& rhs)
{
  if(this != &rhs) {
    destroy();
    copy(rhs);
  }
  return *this;
}

unsigned* Scene::updateScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(background.r/255.0, background.g/255.0, background.b/255.0, 0.0);
  glLoadIdentity();
  
  std::vector<Shape*>::const_iterator it;
  
  // Slower, but make sure lines are drawn first
  for(it = shapes.begin() ; it != shapes.end() ; ++it) {
    if((*it)->getType() == LINE) {
      (*it)->draw();
      if(directed)
        (*it)->drawExtra();
    }
  }
  
  // Now do it again for everything else
  for(it = shapes.begin() ; it != shapes.end() ; ++it) {
    if((*it)->getType() != LINE)
      (*it)->draw();
  }
  
  return NULL;
}
  
void Scene::addShape(SHAPES shape, int xW, int yW)
{
  double x = 0, y = 0;
  Shape* newShape = NULL;
  
  updateViewport();
  windowToGL(xW, yW, x, y);
  
  if(pickScene(xW, viewport[3]-yW) > 0)
    return;
  
  switch(shape)
  {
    case CIRCLE:
      newShape = new Circle(x, y);
      break;
    default:
      break;
  }
  
  if(newShape != NULL)
    shapes.push_back(newShape);
}

void Scene::addNode()
{
  Circle* circle = NULL;
  Circle* last = static_cast<Circle*>(getLast(CIRCLE));
  float rad = 18.0f;
  float rightBnd = .85f;
  float scale = 2.5f;
  
  if(last == NULL) { // Base case
    circle = new Circle(-.75, .75, rad);
  } else { // Position based on the last one
    float x = last->getX() + (scale*last->getRadius()*.01);
    float y = last->getY();
    
    if(x + rad*.01 >= rightBnd) {
      x = -.75f;
      y = last->getY() - (scale*last->getRadius()*.01);
    }
    
    circle = new Circle(x, y, rad);
  }
  shapes.push_back(circle);
}

void Scene::addEdge(int from, int to)
{
  Circle* l = static_cast<Circle*>(findShape(from, CIRCLE));
  Circle* r = static_cast<Circle*>(findShape(to, CIRCLE));
  
  if(l == NULL || r == NULL)
    return;
  
  Line* edge = new Line(l, r);
  l->addEdge(edge);
  r->addEdge(edge);
  
  shapes.push_back(edge);
}

ACTION Scene::registerClick(int xW, int yW)
{
  updateViewport();
  double x = 0, y = 0;
  
  windowToGL(xW, yW, x, y);
  
  unsigned hits = pickScene(xW, viewport[3]-yW);
  
  ACTION action =  currentMode->handleClick(x, y, hits, pickBuffer);
  
  return action;
}

MODES Scene::getMode() const
{
  return currentMode->getMode();
}

void Scene::moveNodes(int xW, int yW)
{
  updateViewport();
  float dx = (float)xW/(float)viewport[2];
  float dy = (float)yW/(float)viewport[3];
  
  std::vector<Shape*>::iterator it;

  for(it = selected.begin() ; it != selected.end() ; ++it) {
    if((*it)->getType() != LINE) {
      float x = (*it)->getX();
      float y = (*it)->getY();
      float newX = x + dx;
      float newY = y - dy;
      
      if(newX < -1 || newX > 1 || newY < -1 || newY > 1)
        continue;

      (*it)->setX(newX);
      (*it)->setY(newY);
    }
  }
}

void Scene::moveNode(int id, int x, int y)
{
  // Find the node
  Shape* shape = NULL;
  std::vector<Shape*>::iterator it;
  for(it = shapes.begin() ; it != shapes.end() ; ++it) {
    if((*it)->getType() == CIRCLE) {
      if((*it)->getId() == id) {
        shape = *it;
        break;
      }
    }
  }
  
  if(shape != NULL) {
    shape->setX(x);
    shape->setY(y);
  }
}

void Scene::updateMode(MODES mode)
{
  currentMode = modes[mode];
  currentMode->removeAllHighlight();
}

void Scene::updateGLSize(int w, int h)
{
  glViewport(0, 0, w, h);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, w, h, 0, 0, 0);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
               
void Scene::updateViewport()
{
  glGetIntegerv(GL_VIEWPORT, viewport);
}

void Scene::updateLabel(const std::string& label)
{
  std::vector<Shape*>::iterator it;
  
  for(it = selected.begin() ; it != selected.end() ; ++it) {
    if((*it)->getType() != LINE) // Lines have weights only
      (*it)->setLabel(label);
  }
}

void Scene::updateLabel(int id, const std::string& label)
{
  Shape* node = findShape(id, GRAPHIX::CIRCLE);
  
  if(node == NULL)
    return;
  
  std::string currLabel = node->getLabel();
  
  currLabel.append("(");
  currLabel.append(label);
  currLabel.append(")");
  
  node->setLabel(currLabel);
}

void Scene::updateWeight(int weight)
{
  std::vector<Shape*>::iterator it;
  
  for(it = selected.begin() ; it != selected.end() ; ++it) {
    if((*it)->getType() == LINE) {
      Line* line = static_cast<Line*>(*it);
      line->updateWeight(weight);
    }
  }
}

void Scene::updateBackground(unsigned int red, unsigned int green, unsigned int blue)
{
  background.r = red;
  background.g = green;
  background.b = blue;
}

void Scene::updateHighlightColor(unsigned int red, unsigned int green, unsigned int blue)
{
  highlight.r = red;
  highlight.g = green;
  highlight.b = blue;
}

void Scene::updateSelectedColor(unsigned int red, unsigned int green, unsigned int blue)
{
  Color c(red, green, blue, 0);
  
  std::vector<Shape*>::iterator it;
  
  for(it = selected.begin() ; it != selected.end() ; ++it)
    (*it)->setColor(c);
}

void Scene::updateNodeColor(int id, unsigned int r, unsigned int g, unsigned int b)
{
  Shape* node = findShape(id, GRAPHIX::CIRCLE);
  
  if(node == NULL)
    return;
  
  Color c(r, g, b, 0.0);
  
  node->setColor(c);
}

void Scene::setLastId(int id)
{
  if(shapes.empty())
    return;
  
  std::vector<Shape*>::iterator it = shapes.end()-1;
  (*it)->setId(id);
}

bool Scene::checkNodesSelected() const
{
  std::vector<Shape*>::const_iterator it;
  
  for(it = selected.begin() ; it != selected.end() ; ++it)
    if((*it)->getType() == CIRCLE)
      return true;
  
  return false;
}

bool Scene::checkEdgesSelected() const
{
  std::vector<Shape*>::const_iterator it;
  
  for(it = selected.begin() ; it != selected.begin() ; ++it)
    if((*it)->getType() == LINE)
      return true;
  
  return false;
}

unsigned Scene::countSelected(SHAPES type) const
{
  if(type == ANY)
    return selected.size();
  
  unsigned selCount = 0;
  std::vector<Shape*>::const_iterator it;
  
  for(it = selected.begin() ; it != selected.end() ; ++it) {
    if((*it)->getType() == type)
      selCount++;
  }
  
  return selCount;
}

void Scene::setCurves(CURVE type)
{
  std::vector<Shape*>::iterator it;
  
  for(it = selected.begin() ; it != selected.end() ; ++it) {
    if((*it)->getType() == LINE) {
      Line* line = static_cast<Line*>(*it);
      line->setCurve(type);
    }
  }
}

void Scene::selectAll()
{
  currentMode->highlightAll();
}

void Scene::deselectAll()
{
  currentMode->removeAllHighlight();
}

std::vector<std::pair<SHAPES, int> > Scene::deleteSelected()
{
  std::vector<std::pair<SHAPES, int> > ret;
  std::vector<Shape*>::iterator it;
  std::vector<Shape*>::iterator all;
  
  std::map<Line*,Line*> removedEdges;
  
  for(it = selected.begin() ; it != selected.end() ; ++it) {
    // Make sure this is not simply an already removed edge
    if(removedEdges[static_cast<Line*>(*it)] != NULL)
      continue;
    
    const std::map<Line*,Line*>* edgeList = NULL;
    if((*it)->getType() == CIRCLE)
      edgeList = static_cast<Circle*>(*it)->getEdgeMap();
    
    // Update our main list
    if(edgeList != NULL) {
      // Also smart to remove all edges first
      std::map<Line*,Line*>::const_iterator edge;
      for(edge = edgeList->begin() ; edge != edgeList->end() ; ++edge) {
        Line* tmp = edge->second;
        
        ret.push_back(std::pair<SHAPES,int>(tmp->getType(), tmp->getId()));
        
        removeShapeFromList(tmp);
        removedEdges[tmp] = tmp;
        delete tmp;
      }
    }
    
    ret.push_back(std::pair<SHAPES,int>((*it)->getType(), (*it)->getId()));
    
    removeShapeFromList(*it);
    
    delete *it;
  }
  
  selected.clear();
  
  return ret;
}

std::vector<int> Scene::getWeights() const
{
  std::vector<int> ret;
  std::vector<Shape*>::const_iterator it;
  
  for(it = shapes.begin() ; it != shapes.end() ; ++it) {
    if((*it)->getType() == LINE) {
      Line* line = static_cast<Line*>(*it);
      ret.push_back(line->getWeight());
    }
  }
  
  return ret;
}

std::vector<std::string> Scene::getSelectedLabels() const
{
  return getLabels(selected);
}

std::vector<std::string> Scene::getLabels() const
{
  return getLabels(shapes);
}

std::vector<std::pair<float, float> > Scene::getCoords(SHAPES type) const
{
  std::vector<std::pair<float, float> > ret;
  std::vector<Shape*>::const_iterator it;
  
  for(it = shapes.begin() ; it != shapes.end() ; ++it) {
    if((*it)->getType() == type || type == ANY) {
      double glX = (*it)->getX();
      double glY = (*it)->getY();
      double x = 0;
      double y = 0;
      GLToWindow(glX, glY, x, y);
      ret.push_back(std::pair<int, int>(x, y));
    }
  }
  
  return ret;
}

std::vector<float> Scene::getRadii() const
{
  std::vector<float> ret;
  std::vector<Shape*>::const_iterator it;
  
  for(it = shapes.begin() ; it != shapes.end() ; ++it) {
    if((*it)->getType() == CIRCLE) {
      Circle* node = static_cast<Circle*>(*it);
      ret.push_back(node->getRadius());
    }
  }
  
  return ret;
}

std::vector<int> Scene::getSelectedIds(SHAPES type) const
{
  std::vector<int> ret;
  std::vector<Shape*>::const_iterator it;

  for(it = selected.begin() ; it != selected.end() ; ++it) {
    if(type == ANY || (*it)->getType() == type)
      ret.push_back((*it)->getId());
  }
  
  return ret;
}

Shape* Scene::getLast(SHAPES type) const
{
  if(shapes.size() == 0)
    return NULL;
  
  if(type == ANY)
    return *(shapes.end()-1);
  
  std::vector<Shape*>::const_iterator it;
  
  for(it = shapes.end() - 1 ; ; --it) {
    if((*it)->getType() == type)
      return *it;
    if(it == shapes.begin())
      break;
  }
  
  return NULL;
}

Shape* Scene::findShape(int pubId, SHAPES type) const
{
  std::vector<Shape*>::const_iterator it;
  
  for(it = shapes.begin() ; it != shapes.end() ; ++it) {
    if((*it)->getId() == pubId && ((*it)->getType() == type
                                   || type == ANY))
      return *it;
  }
  
  return NULL;
}

std::vector<Shape*> Scene::getShapes(GRAPHIX::SHAPES type) const
{
  if(type == ANY)
    return shapes;
  
  std::vector<Shape*> ret;
  std::vector<Shape*>::const_iterator it;
  
  for(it = shapes.begin() ; it != shapes.end() ; ++it)
    if((*it)->getType() == type)
      ret.push_back(*it);
  
  return ret;
}

unsigned char* Scene::getByteArray() const
{
  unsigned char* arr = new unsigned char[3 * viewport[2] * viewport[3]];
  
  glReadPixels(0, 0, viewport[2], viewport[3], GL_RGB, GL_UNSIGNED_BYTE, arr);
  
  return arr;
}

void Scene::setDirected(bool d)
{
  directed = d;
}

bool Scene::isDirected() const
{
  return directed;
}

void Scene::setScaleFactor(float x, float y)
{
  xFactor = std::abs(x);
  yFactor = std::abs(y);
}

float Scene::getScaleFactor(bool x) const
{
  if(x)
    return xFactor;
  return yFactor;
}

void Scene::resetColors()
{
  Color black(0.0, 0.0, 0.0, 0.0);
  highlight = Color(0.0, 0.0, 255.0, 0.0);
  std::vector<Shape*>::iterator it;
  
  for(it = shapes.begin() ; it != shapes.end() ; ++it)
    (*it)->setColor(black);
}

unsigned Scene::pickScene(float x, float y)
{
  updateViewport();
  glSelectBuffer(bufferSize, pickBuffer);
  
  glRenderMode(GL_SELECT);
  glInitNames();
  glPushName(0);
  
  // Prepare OpenGL for picking
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  
  gluPickMatrix(x, y, 25.0, 25.0, viewport);
  glOrtho(0, viewport[2], viewport[3], 0, 0, 0);
  
  // Perform the picking operation
  glMatrixMode(GL_MODELVIEW);
  
  currentMode->pickLogic();
  
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  
  unsigned hits = glRenderMode(GL_RENDER);
  
  glMatrixMode(GL_MODELVIEW);
  
  return hits;
}

void Scene::removeShapeFromList(Shape* shape)
{
  std::vector<Shape*>::iterator it;
  for(it = shapes.begin() ; it != shapes.end() ; ++it) {
    if(*it == shape) {
      shapes.erase(it);
      return;
    }
  }
}

void Scene::removeAndDelete(Shape* shape)
{
  if(shape == NULL)
    return;
  
  removeShapeFromList(shape);
  
  // For nodes _ALWAYS_ remove edges FIRST
  if(shape->getType() == CIRCLE) {
    const std::map<Line*,Line*>* edgeList = static_cast<Circle*>(shape)->getEdgeMap();
    std::map<Line*,Line*>::const_iterator it;
    for(it = edgeList->begin() ; it != edgeList->end() ; ++it)
      removeAndDelete(it->second);
  }
  
  delete shape;
}
               
void Scene::windowToGL(int winX, int winY, double& x, double& y) const
{
  double model[16], projection[16];
  double z;
  
  glGetDoublev(GL_MODELVIEW_MATRIX, model);
  glGetDoublev(GL_PROJECTION_MATRIX, projection);
  
  gluUnProject(winX, winY, 0, model, projection, viewport, &x, &y, &z);
  
  y *= -1; // Window to OpenGL so invert y
}

void Scene::GLToWindow(double glX, double glY, double& x, double& y) const
{
  double model[16], projection[16];
  double z;
  
  glGetDoublev(GL_MODELVIEW_MATRIX, model);
  glGetDoublev(GL_PROJECTION_MATRIX, projection);
  
  gluProject(glX, glY, 0, model, projection, viewport, &x, &y, &z);
  
  y = viewport[3] - y; // OpenGL to window so invert y
}

std::vector<std::string> Scene::getLabels(const std::vector<Shape*>& vector) const
{
  std::vector<std::string> ret;
  std::vector<Shape*>::const_iterator it;
  
  for(it = vector.begin() ; it != vector.end() ; ++it)
    ret.push_back((*it)->getLabel());
  
  return ret;
}

void Scene::copy(const Scene& rhs)
{
  bufferSize = rhs.bufferSize;
  pickBuffer = new unsigned[bufferSize];
  
  for(unsigned i = 0 ; i < bufferSize ; ++i)
    pickBuffer[i] = rhs.pickBuffer[i];
  
  for(unsigned i = 0 ; i < rhs.shapes.size() ; ++i) {
    Shape* shape = rhs.shapes[i];
    Shape* newShape = NULL;
    switch(shape->getType())
    {
      case CIRCLE:
      {
        Circle* circle = static_cast<Circle*>(shape);
        shapes.push_back((newShape = new Circle(*circle)));
      }
        break;
      default:
        break;
    }
    if(newShape != NULL && newShape->isSelected())
      selected.push_back(newShape);
  }
  
  std::map<MODES, Mode*>::const_iterator it;
  for(it = rhs.modes.begin() ; it != rhs.modes.end() ; ++it) {
    MODES modeType = (*it).first;
    Mode* modePtr  = (*it).second;
    
    switch(modePtr->getMode()) {
      case NODECREATION:
      {
        NodeCreationMode* theMode = static_cast<NodeCreationMode*>(modePtr);
        modes[modeType] = new NodeCreationMode(*theMode);
      }
        break;
      case EDGECREATION:
      {
        EdgeCreationMode* theMode = static_cast<EdgeCreationMode*>(modePtr);
        modes[modeType] = new EdgeCreationMode(*theMode);
      }
        break;
      default:
        break;
    }
  }
}
  
void Scene::destroy()
{
  if(pickBuffer != NULL)
    delete pickBuffer;
  
  while(shapes.size() > 0)
    removeAndDelete(shapes[0]);
  
  std::map<MODES, Mode*>::iterator it;
  for(it = modes.begin() ; it != modes.end() ; ++it)
    delete (*it).second;
  
  shapes.clear();
  selected.clear();
  modes.clear();
}
  
void Scene::resizePickBuffer()
{
  // NOTE: Shrinking not yet implemented
  // but plans to do so if space complexity
  // becomes an issue
  unsigned newSize = bufferSize << 1;
  unsigned* newArr = new unsigned[newSize];
  
  for(unsigned i = 0 ; i < bufferSize ; ++i)
    newArr[i] = pickBuffer[i];
  
  delete pickBuffer;
  
  pickBuffer = newArr;
  bufferSize = newSize;
}
}
