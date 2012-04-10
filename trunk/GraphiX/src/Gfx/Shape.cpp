/**
 * Application: GraphiX Library
 * Module: Library
 * File: Shape.cpp
 * Description: Implementation of shape base class
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include "Gfx/Shape.h"

namespace GRAPHIX
{
Shape::Shape(float x, float y)
  : xCoord(x), yCoord(y), selected(false), pubId(-1)
{
  color.r = color.g = color.b = 255.0;
  color.a = 0.0;
}
  
Shape::Shape(float x, float y, Color c)
  : xCoord(x), yCoord(y), color(c), selected(false), pubId(-1)
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

void Shape::setId(int id)
{
  pubId = id;
}

int Shape::getId() const
{
  return pubId;
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

void Shape::setBorder(const Color& color)
{
  border = color;
}

Color Shape::getColor() const
{
  return color;
}

Color Shape::getHighlight() const
{
  if(isSelected())
    return highlight;
  return border;
}

void Shape::setLabel(const std::string& str)
{
  label = str;
}

const std::string& Shape::getLabel() const
{
  return label;
}

void Shape::toggleSelected()
{
  selected = !selected;
}

void Shape::setSelected(bool val)
{
  selected = val;
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

