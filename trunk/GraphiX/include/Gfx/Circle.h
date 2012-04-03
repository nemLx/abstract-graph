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

#include "Shape.h"

namespace GRAPHIX
{
class Circle : public Shape
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
   * Draw a circle
   */
  virtual void draw() const;
  
  /**
   * Return shape type
   */
  virtual SHAPES getType() const;
  
private:
  float radius;
};
}

#endif /* GRAPHIX_GFX_CIRCLE_H__ */

