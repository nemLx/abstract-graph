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

#include "Gfx/Circle.h"
#include "Gfx/Line.h"

#define DEG2RAD (3.14159/180)

namespace GRAPHIX
{
Circle::Circle(float x, float y, float rad)
  : Shape(x, y), radius(rad)
{
}

Circle::~Circle()
{
  destroy();
}
  
Circle::Circle(const Circle& rhs)
  : Shape(rhs.getX(), rhs.getY()), radius(rhs.radius)
{
}
  
void Circle::setRadius(float rad)
{
  radius = rad;
}

float Circle::getRadius() const
{
  return radius;
}

void Circle::addEdge(Line* edge)
{
  edges[edge] = edge;
}

void Circle::removeEdge(Line* edge)
{
  if(edges[edge] == NULL)
    return;
  edges[edge] = NULL;
}

const std::map<Line*,Line*>* Circle::getEdgeMap() const
{
  return &edges;
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
    for(int i = 0 ; i <= 360 ; ++i)
      glVertex2f(x + sin(i*DEG2RAD)*radius, y + cos(i*DEG2RAD)*radius);
  glEnd();
  
  // Outline our figure
  glBegin(GL_LINE_LOOP);
    glColor3f(border.r/255.0, border.g/255.0, border.b/255.0);
    for(int i = 0 ; i <= 360 ; ++i)
      glVertex2f(x + sin(i*DEG2RAD)*radius, y + cos(i*DEG2RAD)*radius);
  glEnd();
}
  
SHAPES Circle::getType() const
{
  return CIRCLE;
}

void Circle::destroy()
{
  std::map<Line*,Line*>::iterator it;
  for(it = edges.begin() ; it != edges.end() ; ++it) {
    Line* tmp = it->second;
    if(tmp != NULL) {
      edges.erase(it);
      it--;      
      delete tmp;
    }
  }
}

}

