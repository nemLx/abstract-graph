/**
 * Application: GraphiX Library
 * Module: Library
 * File: NodeCreationMode.h
 * Description: Interface for Node creation mode controls
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef GRAPHIX_CONTROL_NODECREATIONMODE_H__
#define GRAPHIX_CONTROL_NODECREATIONMODE_H__

#include "graphix_incl.h"
#include "Mode.h"

namespace GRAPHIX
{
class GRAPHIX_EXPORT NodeCreationMode : public Mode
{
public:
  /**
   * Constructor
   *
   * @param shapes    A pointer to a shapes vector
   * @param selected  A pointer to the selected vector
   * @param highlight The color to highlight nodes
   */
  NodeCreationMode(std::vector<Shape*>* shapes, std::vector<Shape*>* selected, const Color& highlight);
  
  /**
   * Copy constructor
   */
  NodeCreationMode(const NodeCreationMode& rhs);
  
  /**
   * Destructor
   */
  virtual ~NodeCreationMode();
  
  /**
   * Handle registered clicks
   *
   * @param x           X coordinate (unit)
   * @param y           Y coordinate (unit)
   * @param hits        Number of hits from picking
   * @param pickBuffer  The pick buffer
   */
  virtual ACTION handleClick(double x, double y, unsigned hits, unsigned* pickBuffer);
  
  /**
   * Determine which objects to draw during picking (pure virtual)
   */
  virtual void pickLogic();
  
  /**
   * Determine what to do if items selected (pure virtual)
   *
   * @param hits        Number of items picked
   * @param pickBuffer  Pointer to the pick buffer
   * @return  The number of items selected
   */
  virtual unsigned selectLogic(unsigned hits, unsigned* pickBuffer);
  
  /**
   * Method to determine the mode type (pure virtual)
   *
   * @return  The mode types (from MODES enum)
   */
  virtual MODES getMode() const;
  
};
}

#endif /* GRAPHIX_CONTROL_NODECREATIONMODE_H__ */
