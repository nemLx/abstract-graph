/**
 * Application: GraphiX Library
 * Module: Library
 * File: Shape.cpp
 * Description: Implementation of shape base class
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include "graphix_incl.h"
#include "Gfx/Shape.h"

namespace GRAPHIX
{
Shape::Shape(float x, float y)
  : xCoord(x), yCoord(y), selected(false)
{
  color.r = color.g = color.b = 255.0;
  color.a = 0.0;
}
  
Shape::Shape(float x, float y, Color c)
  : xCoord(x), yCoord(y), color(c), selected(false)
{
}

Shape::~Shape()
{
}

void Shape::setX(float val)
{
  xCoord = val;
}

void Shape::setY(float val)
{
  yCoord = val;
}

float Shape::getX() const
{
  return xCoord;
}

float Shape::getY() const
{
  return yCoord;
}
  
void Shape::setColor(const Color &c)
{
  color = c;
}

void Shape::setColor(float r, float g, float b, float a)
{
  color.r = r;
  color.g = g;
  color.b = b;
  color.a = a;
}

void Shape::setHighlight(const Color& h)
{
  highlight = h;
}

Color Shape::getColor() const
{
  return color;
}

Color Shape::getHighlight() const
{
  return highlight;
}

void Shape::toggleSelected()
{
  selected = !selected;
}

bool Shape::isSelected() const
{
  return selected;
}

void Shape::pick(unsigned idx) const
{
  glLoadName(idx);
  draw();
}
}

