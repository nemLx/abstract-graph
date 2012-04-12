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

void NodeCreationMode::handleClick(double x, double y, unsigned hits, unsigned* pickBuffer)
{
  std::vector<Shape*>* shapes = getShapesVector();
  if(shapes == NULL)
    return;
  
  // In node creation mode, so add some circles!
  // (But don't overlap)
  if(hits < 1) {
    double rad = .08f; // Static .08f radius for now
    shapes->push_back(new Circle(x, y, rad));
  }
  
  selectLogic(hits, pickBuffer);
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
  // In NODE creation mode, do nothing?? - Temporarily highlighting
  return Mode::selectLogic(hits, pickBuffer);
}

MODES NodeCreationMode::getMode() const
{
  return NODECREATION;
}

}
