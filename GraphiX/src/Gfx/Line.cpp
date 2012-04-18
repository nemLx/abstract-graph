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
  : Shape(-1, -1), cl(cl), cr(cr), to(cr), from(cl), width(1.f), directed(false), direction(false), weight(1)
{
  setHighlight(Color(1.0, 0.0, 0.0, 0.0));
  setColor(Color(0.0, 0.0, 0.0, 0.0));
  updateCirclePositions();
}

Line::Line(const Line& rhs)
  : Shape(rhs.getX(), rhs.getY()), cl(rhs.cl), cr(rhs.cr),
  width(rhs.width), directed(rhs.directed), direction(rhs.direction), weight(rhs.weight)
{
  // NOTE: Probably not yet fully functional (i.e. untested)
  setHighlight(rhs.getHighlight());
  setColor(rhs.getColor());
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

Circle* Line::getLeft() const
{
  return cl;
}

Circle* Line::getRight() const
{
  return cr;
}

Circle* Line::getTo() const
{
  return to;
}
  
Circle* Line::getFrom() const
{
  return from;
}

void Line::draw() const
{
  Color highlight(getHighlight());
  Color color(getColor());
  
  if(highlight.r != highlight.g != highlight.b != 0.f)
    color = highlight;
  
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glLineWidth(width);
  glColor3f(color.r/255.0, color.g/255.0, color.b/255.0);
  glBegin(GL_LINES);
    glVertex2f(cl->getX(), cl->getY());
    glVertex2f(cr->getX(), cr->getY());
  glEnd();
}

void Line::drawExtra() const
{
  Color highlight(getHighlight());
  Color color(getColor());
  
  if(highlight.r != highlight.g != highlight.b != 0.f)
    color = highlight;
  
  // Simple intersection calculations to know where/how
  // to draw arrow
  float r = to->getRadius();
  float x = (to == cl) ? to->getX() - r : to->getX() + r;
  float m = (to->getY() - from->getY())/((to->getX() - from->getX()));
  float b = to->getY();
  float y = m*(x - to->getX()) + b; // point-slope form: y = m*(x - x_1) + y_1
  float baseShift = (to == cl) ? -.05f : .05f;
  
  glColor3f(color.r/255.0, color.g/255.0, color.b/255.0);
  glBegin(GL_TRIANGLES);
  
    glVertex2f(x, y);
    glVertex2f(x + baseShift, y + baseShift);
    glVertex2f(x + baseShift, y - baseShift);
  
  printf("Coords: (%f, %f)\n", x, y);
  glEnd();
}

SHAPES Line::getType() const
{
  return LINE;
}

}
