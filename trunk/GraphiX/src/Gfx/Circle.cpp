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

namespace GRAPHIX
{
Circle::Circle(float x, float y, float rad)
  : Shape(x, y), radius(rad)
{
  setColor(Color(0.0,0.0,0.0,0.0));
  setHighlight(Color(255.0, 255.0, 255.0 ,0.0));
}

Circle::~Circle()
{
  destroy();
}
  
Circle::Circle(const Circle& rhs)
  : Shape(rhs.getX(), rhs.getY()), radius(rhs.radius)
{
}

void Circle::setX(float x)
{
  Shape::setX(x);
  updateEdgePosition();
}

void Circle::setY(float y)
{
  Shape::setY(y);
  updateEdgePosition();
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
  
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glPointSize(radius);
  glBegin(GL_POINTS);
    glColor3f(color.r/255.0, color.g/255.0, color.b/255.0);
    glVertex2f(x, y);
  glEnd();

  float innerRadius = radius - (radius/5);
  glPointSize(innerRadius);
  glBegin(GL_POINTS);
    glColor3f(border.r/255.0, border.g/255.0, border.b/255.0);
    glVertex2f(x, y);
  glEnd();
}
  
SHAPES Circle::getType() const
{
  return CIRCLE;
}


void Circle::setHighlight(const Color& color)
{
  if(isSelected())
    Shape::setHighlight(color);
  else
    Shape::setHighlight(Color(255.0, 255.0, 255.0, 0.0));
}

void Circle::updateEdgePosition()
{
  std::map<Line*,Line*>::iterator it;
  
  for(it = edges.begin() ; it != edges.end() ; ++it)
    if(it->second != NULL)
      (it->second)->updateCirclePositions();
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

