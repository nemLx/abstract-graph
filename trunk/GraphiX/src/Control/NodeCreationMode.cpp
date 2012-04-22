/**
 * Application: GraphiX Library
 * Module: Library
 * File: NodeCreationMode.cpp
 * Description: Node creation mode implementation
 * 
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include "Gfx/Shape.h"
#include "Gfx/Circle.h"

#include "Control/NodeCreationMode.h"

#include <climits>

namespace GRAPHIX
{
NodeCreationMode::NodeCreationMode(std::vector<Shape*>* shapes, std::vector<Shape*>* selected, const Color& highlight)
  : Mode(shapes, selected, highlight)
{
}

NodeCreationMode::NodeCreationMode(const NodeCreationMode& rhs)
  : Mode(rhs.getShapesVector(), rhs.getSelectedVector(), rhs.getHighlight())
{
}

NodeCreationMode::~NodeCreationMode()
{
}

ACTION NodeCreationMode::handleClick(double x, double y, unsigned hits, unsigned* pickBuffer)
{
  std::vector<Shape*>* shapes = getShapesVector();
  if(shapes == NULL)
    return UNDEFINED;
  
  ACTION ret = UNDEFINED;
  
  // In node creation mode, so add some circles!
  // (But don't overlap)
  if(hits < 1) {
    double rad = .08f; // Static .08f radius for now
    shapes->push_back(new Circle(x, y, rad));
    ret = ADDNODE;
  }
  
  selectLogic(hits, pickBuffer);
  
  return ret;
}

void NodeCreationMode::pickLogic()
{
  std::vector<Shape*>* shapes = getShapesVector();
  std::vector<Shape*>::const_iterator it;
  unsigned i = 0;
  for(it = shapes->begin(), i = 0 ; it != shapes->end() ; ++it, ++i) {
    // Only pick circles?
    if((*it)->getType() == CIRCLE)
      (*it)->pick(i);
  }
}

unsigned NodeCreationMode::selectLogic(unsigned hits, unsigned* pickBuffer)
{
  if(pickBuffer == NULL || hits == UINT_MAX)
    return 0;
  
  std::vector<Shape*>* shapes = getShapesVector();
  
  // Find selected nodes (only circles)
  for(unsigned i = 0 ; i < hits ; ++i) {
    unsigned char p = (unsigned char)pickBuffer[i * 4 + 3];
    Shape* shape = (*shapes)[p];
    
    if(shape->getType() != CIRCLE)
      continue;
    
    if(shape == NULL)
      continue;
    
    if(shape->isSelected())
      removeHighlight(shape);
    else
      highlight(shape);
  }
  
  if(hits < 1)
    removeAllHighlight();
  
  return hits;
}

MODES NodeCreationMode::getMode() const
{
  return NODECREATION;
}

}
