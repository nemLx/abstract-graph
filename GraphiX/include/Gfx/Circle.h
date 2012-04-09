/**
 * Application: GraphiX Library
 * Module: Library
 * File: Circle.h
 * Description: Circle interface
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef GRAPHIX_GFX_CIRCLE_H__
#define GRAPHIX_GFX_CIRCLE_H__

#include <map>

#include "graphix_incl.h"
#include "Shape.h"

namespace GRAPHIX
{

class Line;

class GRAPHIX_EXPORT Circle : public Shape
{
public:
  /**
   * Constructor
   *
   * @param x     X coordinate
   * @param y     Y coordinate
   * @param rad   Circle radius
   */
  Circle(float x, float y, float rad);
  
  /**
   * Copy Constructor
   */
  Circle(const Circle& rhs);

  /**
   * Destructor
   */
  virtual ~Circle();

  /**
   * Update radius
   *
   * @param rad   New radius
   */
  virtual void setRadius(float rad);
  
  /**
   * Add an edge to the edge list
   * NOTE: This method does not update display, but only
   *  the node's internal edge list
   *
   * @param edge    A pointer to the line which is the edge
   */
  virtual void addEdge(Line* edge);
  
  /**
   * Remove an edge from the edge list
   * NOTE: This method does not update display, but only
   *  the node's internal edge list
   *
   * @param edge    A pointer to the line which is to be removed
   */
  virtual void removeEdge(Line* edge);
  
  /**
   * Get the edge map
   *
   * @return  The map of edge list
   */
  virtual const std::map<Line*,Line*>* getEdgeMap() const;
  
  /**
   * Draw a circle
   */
  virtual void draw() const;
  
  /**
   * Return shape type
   */
  virtual SHAPES getType() const;
  
private:
  /**
   * Delete any associated edges with this circle
   * and all general clean up
   */
  void destroy();
  
  float radius;
  std::map<Line*,Line*> edges;
};
}

#endif /* GRAPHIX_GFX_CIRCLE_H__ */

