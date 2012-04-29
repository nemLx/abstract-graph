/**
 * Application: GraphiX Library
 * Module: Library
 * File: EditMode.h
 * Description: Edit mode - can move nodes but no node/edge creation
 * 
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include "Control/EditMode.h"

namespace GRAPHIX
{
EditMode::EditMode(std::vector<Shape*>* shapes, std::vector<Shape*>* selected, const Color& highlight)
  : Mode(shapes, selected, highlight)
{
}

EditMode::~EditMode()
{
}

MODES EditMode::getMode() const
{
  return EDIT;
}
}