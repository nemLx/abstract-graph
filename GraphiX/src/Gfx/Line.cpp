/**
 * Application: GraphiX Library
 * Module: Library
 * File: Line.cpp
 * Description: Line implementation
 * 
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include "Gfx/Line.h"

namespace GRAPHIX
{
Line::Line(Circle* cl, Circle* cr)
  : Shape(-1, -1), cl(cl), cr(cr), width(.1f)
{
  setHighlight(Color(1.0, 0.0, 0.0, 0.0));
}

Line::Line(const Line& rhs)
  : Shape(rhs.getX(), rhs.getY()), cl(rhs.cl), cr(rhs.cr),
  width(rhs.width)
{
  setHighlight(rhs.getHighlight());
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

void Line::draw() const
{
  Color color(getHighlight());
  
  glEnable(GL_LINE_SMOOTH);
  glLineWidth(width);
  glBegin(GL_LINES);
    glColor3f(color.r/255.0, color.g/255.0, color.b/255.0);
    glVertex2f(cl->getX(), cl->getY());
    glVertex2f(cr->getX(), cr->getY());
  glEnd();
  glDisable(GL_LINE_SMOOTH);
}

SHAPES Line::getType() const
{
  return LINE;
}

}
