/**
 * Application: AbstractGraph
 * Module: GUI
 * File: NodeOptionsMenu.h
 * Description: Interface for the Node/Edge options menu
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef MENUS_NODEOPTIONSMENU_H__
#define MENUS_NODEOPTIONSMENU_H__

#include <QtGui/QMenu>

class GLWindow;

/**
 * NodeOptionsMenu
 *
 * The right-click pop-up menu which provides
 * actions for nodes and edges
 */
class NodeOptionsMenu : public QMenu
{
  Q_OBJECT
public:
  /**
   * Constructor
   *
   * @param parent    Parent widget
   */
  NodeOptionsMenu(GLWindow* parent);
  
  /**
   * Destructor
   */
  virtual ~NodeOptionsMenu();
  
  /**
   * Enable/disable menu items
   *
   * @param selected      Determine whether items are selected or not
   * @param numSelected   The number of items selected
   * @param edgeSelected  Number of edges selected
   */
  virtual void updateMenuItems(bool selected, unsigned numSelected, unsigned edgeSelected);
  
private:
  /**
   * Initialize menu actions
   */
  void init();
  
  QAction* label;
  QAction* weight;
  QAction* del;
  QAction* color;
  QAction* deselect;
  QAction* curve;
};

#endif /* MENUS_NODEOPTIONSMENU_H__ */
