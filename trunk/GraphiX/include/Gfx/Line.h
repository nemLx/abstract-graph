/**
 * Application: GraphiX Library
 * Module: Library
 * File: Line.h
 * Description: Line interface
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef GRAPHIX_GFX_LINE_H__
#define GRAPHIX_GFX_LINE_H__

#include "graphix_incl.h"
#include "Shape.h"
#include "Circle.h"

namespace GRAPHIX
{
class GRAPHIX_EXPORT Line : public Shape
{
public:
  /**
   * Constructor
   *
   * @param cl    Circle one
   * @param cr    Circle two
   */
  Line(Circle* cl, Circle* cr);
  
  /**
   * Copy Constructor
   */
  Line(const Line& rhs);
  
  /**
   * Destructor
   */
  virtual ~Line();
  
  /**
   * Update the line width
   */
  virtual void setWidth(float w);
  
  /**
   * Draw a circle
   */
  virtual void draw() const;
  
  /**
   * Return shape type
   */
  virtual SHAPES getType() const;
  
private:
  Circle* cl, *cr;
  float width;
};
}

#endif /* GRAPHIX_GFX_LINE_H__ */

