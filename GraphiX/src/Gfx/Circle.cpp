/**
 * Application: GraphiX Library
 * Module: Library
 * File: Circle.cpp
 * Description: Circle implementation
 * 
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include <cmath>

#include "graphix_incl.h"
#include "Gfx/Circle.h"

#define DEG2RAD (3.14159/180)

namespace GRAPHIX
{
Circle::Circle(float x, float y, float rad)
  : Shape(x, y), radius(rad)
{
}

Circle::~Circle()
{
}
  
Circle::Circle(const Circle& rhs)
  : Shape(rhs.getX(), rhs.getY()), radius(rhs.radius)
{
}
  
void Circle::setRadius(float rad)
{
  radius = rad;
}

void Circle::draw() const
{
  float x = getX();
  float y = getY();
  Color color(getColor());
  Color border(getHighlight());
  
  // Draw the closed figure
  glBegin(GL_TRIANGLE_FAN);
    glColor3f(color.r/255.0, color.g/255.0, color.b/255.0);
    glVertex2f(x, y);
    for(int i = 0 ; i < 360 ; ++i)
      glVertex2f(x + sin(i*DEG2RAD)*radius, y + cos(i*DEG2RAD)*radius);
  glEnd();
  
  // Outline our figure
  glBegin(GL_LINE_LOOP);
    glColor3f(border.r, border.g, border.b);
    for(int i = 0 ; i < 360 ; ++i)
      glVertex2f(x + sin(i*DEG2RAD)*radius, y + cos(i*DEG2RAD)*radius);
  glEnd();
}
  
SHAPES Circle::getType() const
{
  return CIRCLE;
}
}

