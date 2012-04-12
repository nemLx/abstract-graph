/**
 * Application: GraphiX Library
 * Module: Library
 * File: ViewMode.cpp
 * Description: View mode - no graph manipulation
 * 
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include "Control/ViewMode.h"

namespace GRAPHIX
{
ViewMode::ViewMode(std::vector<Shape*>* shapes, std::vector<Shape*>* selected, const Color& highlight)
  : Mode(shapes, selected, highlight)
{
}

ViewMode::~ViewMode()
{
}

MODES ViewMode::getMode() const
{
  return VIEWONLY;
}
}