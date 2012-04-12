/**
 * Application: GraphiX Library
 * Module: Library
 * File: ViewMode.h
 * Description: Interface for locking the graph, no manipulation
 *  can occur
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef GRAPHIX_CONTROL_VIEWMODE_H__
#define GRAPHIX_CONTROL_VIEWMODE_H__

#include "graphix_incl.h"
#include "Mode.h"

namespace GRAPHIX
{
class GRAPHIX_EXPORT ViewMode : public Mode
{
public:
  /**
   * Constructor
   *
   * @param shapes    A pointer to a shapes vector
   * @param selected  A pointer to the selected vector
   * @param highlight The color to highlight nodes
   */
  ViewMode(std::vector<Shape*>* shapes, std::vector<Shape*>* selected, const Color& highlight);
  
  /**
   * Destructor
   */
  virtual ~ViewMode();
  
  /**
   * Method to determine the mode type
   *
   * @return  The mode types (from MODES enum)
   */
  virtual MODES getMode() const;
};
}

#endif /* GRAPHIX_CONTROL_VIEWMODE_H__ */
