/**
 * Application: GraphiX Library
 * Module: Library
 * File: Mode.cpp
 * Description: Base Mode implementation
 * 
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include <climits>

#include "Gfx/Shape.h"
#include "Control/Mode.h"

namespace GRAPHIX
{
Mode::Mode(std::vector<Shape*>* shapes, std::vector<Shape*>* selected, const Color& highlight)
  : shapes(shapes), selected(selected), highlightColor(highlight)
{
}

Mode::~Mode()
{
}

std::vector<Shape*>* Mode::getShapesVector() const
{
  return shapes;
}

std::vector<Shape*>* Mode::getSelectedVector() const
{
  return selected;
}

void Mode::handleClick(double x, double y, unsigned hits, unsigned* pickBuffer)
{
  if(hits < 1) {
    removeAllHighlight();
    return;
  }
  
  selectLogic(hits, pickBuffer);
}

void Mode::pickLogic()
{
  if(shapes == NULL)
    return;
  
  std::vector<Shape*>::const_iterator it;
  unsigned i = 0;
  for(it = shapes->begin(), i = 0 ; it != shapes->end() ; ++it, ++i) {
    // Pick everything by default
    (*it)->pick(i);
  }
}

unsigned Mode::selectLogic(unsigned hits, unsigned* pickBuffer)
{
  if(pickBuffer == NULL || shapes == NULL || selected == NULL || hits == UINT_MAX)
    return 0;
  
  // Find selected nodes
  for(unsigned i = 0 ; i < hits ; ++i) {
    unsigned char p = (unsigned char)pickBuffer[i * 4 + 3];
    Shape* shape = (*shapes)[p];
    
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

void Mode::highlightAll()
{
  removeAllHighlight();
  
  std::vector<Shape*>::iterator it;
  
  for(it = shapes->begin() ; it != shapes->end() ; ++it)
    highlight(*it);
}

void Mode::highlight(Shape* shape)
{
  if(shape == NULL || shape->isSelected())
    return;  
  shape->setHighlight(highlightColor);
  shape->toggleSelected();
  selected->push_back(shape);
}

void Mode::removeAllHighlight()
{
  if(selected == NULL)
    return;
  
  std::vector<Shape*>::iterator it;

  while(selected->size() > 0)
    removeHighlight((*selected)[0]);
}

void Mode::removeHighlight(Shape* shape)
{
  if(shape == NULL || !shape->isSelected() || selected == NULL)
    return;
  
  std::vector<Shape*>::iterator it;
  Color highlight(0.f, 0.f, 0.f, 0.f);
  
  for(it = selected->begin() ; it != selected->end() ; ++it) {
    if(*it == shape) {
      shape->setHighlight(highlight);
      if(shape->isSelected())
        shape->toggleSelected();
      selected->erase(it);
      break;
    }
  }
}

const Color& Mode::getHighlight() const
{
  return highlightColor;
}

}