/**
 * Application: GraphiX Library
 * Module: Library
 * File: EdgeCreationMode.cpp
 * Description: Edge creation mode implementation
 * 
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include "Gfx/Shape.h"
#include "Gfx/Circle.h"
#include "Gfx/Line.h"

#include "Control/EdgeCreationMode.h"

namespace GRAPHIX
{
EdgeCreationMode::EdgeCreationMode(std::vector<Shape*>* shapes, std::vector<Shape*>* selected)
  : Mode(shapes, selected)
{
}

EdgeCreationMode::EdgeCreationMode(const EdgeCreationMode& rhs)
  : Mode(rhs.getShapesVector(), rhs.getSelectedVector())
{
}

EdgeCreationMode::~EdgeCreationMode()
{
}

void EdgeCreationMode::handleClick(double x, double y, unsigned hits, unsigned* pickBuffer)
{
  std::vector<Shape*>* selected = getSelectedVector();
  std::vector<Shape*>* shapes = getShapesVector();
  
  selectLogic(hits, pickBuffer);
  
  if(selected != NULL && shapes != NULL) {
    Circle* cl = NULL;
    Circle* cr = NULL;
      
    std::vector<Shape*>::iterator it;
    for(it = selected->begin() ; it != selected->end() ; ++it) {
      if((*it)->getType() == CIRCLE) {
        if(cl == NULL) {
          cl = static_cast<Circle*>(*it);
        } else {
          cr = static_cast<Circle*>(*it);
          break;
        }
      }
    }
    
    if(cl != NULL && cr != NULL) {
      removeHighlight(cl);
      removeHighlight(cr);
      Line* edge = new Line(cl, cr);
      shapes->push_back(edge);
      cl->addEdge(edge);
      cr->addEdge(edge);
    }
  }
}

void EdgeCreationMode::pickLogic()
{
  std::vector<Shape*>* shapes = getShapesVector();
  std::vector<Shape*>::const_iterator it;
  unsigned i = 0;
  for(it = shapes->begin(), i = 0 ; it != shapes->end() ; ++it, ++i) {
    SHAPES type = (*it)->getType();
    if(type == CIRCLE)// || type == LINE)
      (*it)->pick(i);
  }
}

void EdgeCreationMode::selectLogic(unsigned hits, unsigned* pickBuffer)
{
  // Default for now
  Mode::selectLogic(hits, pickBuffer);
}

MODES EdgeCreationMode::getMode() const
{
  return EDGECREATION;
}

}
