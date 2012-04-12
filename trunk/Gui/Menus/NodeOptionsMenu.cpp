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
  weight->setEnabled(selected);
  del->setEnabled(selected);
  color->setEnabled(selected);
  deselect->setEnabled(selected);
}

void NodeOptionsMenu::init()
{
  label    = new QAction(MENU_GENERAL_LABEL, this);
  weight   = new QAction(MENU_GENERAL_WEIGHT, this);
  del      = new QAction(MENU_GENERAL_DELETE, this);
  color    = new QAction(MENU_NODE_COLOR, this);
  deselect = new QAction(MENU_GENERAL_DESELECT, this);
  
  // Non-Conditional actions
  // (i.e. not class members/always enabled)
  QAction* highlight  = new QAction(MENU_NODE_HIGHLIGHT, this);
  QAction* background = new QAction(MENU_NODE_BACKGROUND, this);
  QAction* selectall  = new QAction(MENU_GENERAL_SELECTALL, this);
  
  connect(label, SIGNAL(triggered()), parent(), SLOT(updateLabel()));
  connect(weight, SIGNAL(triggered()), parent(), SLOT(updateWeight()));
  connect(del, SIGNAL(triggered()), parent(), SLOT(deleteSelected()));
  connect(color, SIGNAL(triggered()), parent(), SLOT(updateColor()));
  connect(highlight, SIGNAL(triggered()), parent(), SLOT(updateHighlight()));
  connect(background, SIGNAL(triggered()), parent(), SLOT(updateBackground()));
  connect(selectall, SIGNAL(triggered()), parent(), SLOT(selectAll()));
  connect(deselect, SIGNAL(triggered()), parent(), SLOT(deselectAll()));
  
  this->addAction(label);
  this->addAction(weight);
  this->addSeparator();
  this->addAction(color);
  this->addAction(highlight);
  this->addAction(background);
  this->addSeparator();
  this->addAction(selectall);
  this->addAction(deselect);
  this->addSeparator();
  this->addAction(del);
}
