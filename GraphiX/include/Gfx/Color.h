/**
 * Application: GraphiX Library
 * Module: Library
 * File: Color.h
 * Description: Simple color struct definition
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef GRAPHIX_GFX_COLOR_H__
#define GRAPHIX_GFX_COLOR_H__

struct Color
{
  /**
   * Constructor
   */
  Color()
    : r(0.f), g(0.f), b(0.f), a(0.f)
  {
  }
  
  /**
   * Copy Constructor
   */
  Color(const Color& rhs)
    : r(rhs.r), g(rhs.g), b(rhs.b), a(rhs.a)
  {
  }
  
  /**
   * Supplemental constructor
   */
  Color(float r, float g, float b, float a)
    : r(r), g(g), b(b), a(a)
  {
  }
  
  float r, g, b, a;
};

#endif /* GRAPHIX_GFX_COLOR_H__ */
