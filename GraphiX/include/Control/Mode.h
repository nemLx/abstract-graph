/**
 * Application: GraphiX Library
 * Module: Library
 * File: Mode.h
 * Description: Base class for any given mode
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef GRAPHIX_CONTROL_MODE_H__
#define GRAPHIX_CONTROL_MODE_H__

#include <vector>

#include "graphix_incl.h"

class Shape;

namespace GRAPHIX
{
  
/**
 * The types of modes supported
 */
enum GRAPHIX_EXPORT MODES
{
  NODECREATION,
  EDGECREATION
};
  
/**
 * The mode base class
 */
class GRAPHIX_EXPORT Mode
{
public:
  /**
   * Constructor
   *
   * @param shapes    A pointer to a shapes vector
   * @param selected  A pointer to the selected vector
   * @param highlight The color to highlight nodes
   */
  Mode(std::vector<Shape*>* shapes, std::vector<Shape*>* selected, const Color& highlight);
  
  /**
   * Destructor
   */
  virtual ~Mode();
  
  /**
   * Get the appropriate vector
   *
   * @return  A pointer to the shapes and selected vectors respectively
   */
  std::vector<Shape*>* getShapesVector() const;
  std::vector<Shape*>* getSelectedVector() const;
  
  /**
   * Handle registered clicks
   *
   * @param x           X coordinate (unit)
   * @param y           Y coordinate (unit)
   * @param hits        Number of hits from picking
   * @param pickBuffer  The pick buffer
   */
  virtual void handleClick(double x, double y, unsigned hits, unsigned* pickBuffer);
  
  /**
   * Determine which objects to draw during picking
   * Default picking will pick any object
   */
  virtual void pickLogic();
  
  /**
   * Determine what to do if items selected
   * By default just do highlight/unhighlight
   *
   * @param hits        Number of items picked
   * @param pickBuffer  Pointer to the pick buffer
   * @return  The number of items selected
   */
  virtual unsigned selectLogic(unsigned hits, unsigned* pickBuffer);
  
  /**
   * Highlight all shapes
   */
  virtual void highlightAll();
  
  /**
   * Highlight a particular shape
   *
   * @param shape   Pointer to the shape to be colored
   */
  virtual void highlight(Shape* shape);
  
  /**
   * Unhighlight a particular shape
   *
   * @param shape   Pointer to the shape to be colored
   */
  virtual void removeHighlight(Shape* shape);
  
  /**
   * Remove all highlighting
   */
  virtual void removeAllHighlight();
  
  /**
   * Method to determine the mode type (pure virtual)
   *
   * @return  The mode types (from MODES enum)
   */
  virtual MODES getMode() const = 0;
  
protected:
  /**
   * Get the highlight
   *
   * @return  The highlight reference
   */
  const Color& getHighlight() const;
  
private:
  std::vector<Shape*>* shapes;
  std::vector<Shape*>* selected;
  const Color& highlightColor;
};
}

#endif /* GRAPHIX_CONTROL_MODE_H__ */
