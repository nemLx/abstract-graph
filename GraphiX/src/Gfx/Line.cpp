/**
 * Application: GraphiX Library
 * Module: Library
 * File: Line.cpp
 * Description: Line implementation
 * 
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include <cmath>

#include "Gfx/Line.h"

namespace GRAPHIX
{
Line::Line(Circle* cl, Circle* cr)
  : Shape(-1, -1), cl(cl), cr(cr), width(.1f), directed(false), direction(false), weight(-1)
{
  setHighlight(Color(1.0, 0.0, 0.0, 0.0));
  updateCirclePositions();
}

Line::Line(const Line& rhs)
  : Shape(rhs.getX(), rhs.getY()), cl(rhs.cl), cr(rhs.cr),
  width(rhs.width), directed(rhs.directed), direction(rhs.direction), weight(rhs.weight)
{
  setHighlight(rhs.getHighlight());
  updateCirclePositions();
}

Line::~Line()
{
  // Remove self from end points
  if(cl != NULL)
    cl->removeEdge(this);
  if(cr != NULL)
    cr->removeEdge(this);
}

void Line::setWidth(float w)
{
  width = w;
}

void Line::updateWeight(int wgt)
{
  weight = wgt;
}

int Line::getWeight() const
{
  return weight;
}

void Line::setDirected(bool set)
{
  directed = set;
}

void Line::setDirection(bool right)
{
  direction = right;
}

void Line::updateCirclePositions()
{
  if(cl == NULL || cr == NULL)
    return;
  
  // Make sure our names reflect reality
  if(cl->getX() < cr->getX()) {
    Circle* tmp = cl;
    cl = cr;
    cr = tmp;
  }

  // If circles have moved, make sure we know our midpoint
  float midX = (float)(cl->getX() + cr->getX())/2;
  float midY = (float)(cl->getY() + cr->getY())/2;
  setX(midX);
  setY(midY);
}

void Line::draw() const
{
  Color color(getHighlight());
  
  glLineWidth(width);
  glBegin(GL_LINES);
    glColor3f(color.r/255.0, color.g/255.0, color.b/255.0);
    glVertex2f(cl->getX(), cl->getY());
    glVertex2f(cr->getX(), cr->getY());
  glEnd();
}

SHAPES Line::getType() const
{
  return LINE;
}

}
