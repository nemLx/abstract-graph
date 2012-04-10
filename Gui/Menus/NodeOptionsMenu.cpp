/**
 * Application: AbstractGraph
 * Module: GUI
 * File: NodeOptionsMenu.cpp
 * Description: Implementation for Node/Edge options menu
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include "NodeOptionsMenu.h"
#include "MenuDefs.h"
#include "../Windows/GLWindow.h"

NodeOptionsMenu::NodeOptionsMenu(GLWindow* parent)
  : QMenu(parent)
{
  init();
}

NodeOptionsMenu::~NodeOptionsMenu()
{
}

void NodeOptionsMenu::updateMenuItems(bool selected, unsigned numSelected)
{
  label->setEnabled(numSelected == 1);
  del->setEnabled(selected);
  color->setEnabled(selected);
  outline->setEnabled(selected);
}

void NodeOptionsMenu::init()
{
  label   = new QAction(MENU_GENERAL_LABEL, this);
  del     = new QAction(MENU_GENERAL_DELETE, this);
  color   = new QAction(MENU_NODE_COLOR, this);
  outline = new QAction(MENU_NODE_HIGHLIGHT, this);
  
  connect(label, SIGNAL(triggered()), parent(), SLOT(updateLabel()));
  connect(del, SIGNAL(triggered()), parent(), SLOT(deleteSelected()));
  connect(color, SIGNAL(triggered()), parent(), SLOT(updateColor()));
  connect(outline, SIGNAL(triggered()), parent(), SLOT(updateHighlight()));
  
  this->addAction(label);
  this->addSeparator();
  this->addAction(color);
  this->addAction(outline);
  this->addSeparator();
  this->addAction(del);
}
