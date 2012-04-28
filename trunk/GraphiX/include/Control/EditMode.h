/**
 * Application: GraphiX Library
 * Module: Library
 * File: EditMode.cpp
 * Description: Edit mode - can move nodes but no node/edge creation
 * 
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef GRAPHIX_CONTROL_EDITMODE_H__
#define GRAPHIX_CONTROL_EDITMODE_H__

#include "graphix_incl.h"
#include "Mode.h"

namespace GRAPHIX
{
class GRAPHIX_EXPORT EditMode : public Mode
{
public:
  /**
   * Constructor
   *
   * @param shapes    A pointer to a shapes vector
   * @param selected  A pointer to the selected vector
   * @param highlight The color to highlight nodes
   */
  EditMode(std::vector<Shape*>* shapes, std::vector<Shape*>* selected, const Color& highlight);
  
  /**
   * Destructor
   */
  virtual ~EditMode();
  
  /**
   * Method to determine the mode type
   *
   * @return  The mode types (from MODES enum)
   */
  virtual MODES getMode() const;
  
private:
};
}

#endif /* GRAPHIX_CONTROL_EDITMODE_H__ */

