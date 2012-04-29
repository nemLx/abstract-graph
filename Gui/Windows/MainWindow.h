/**
 * Application: AbstractGraph
 * Module: GUI
 * File: Windows/MainWindow.h
 * Description: Main window interface for GUI application
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef WINDOWS_MAINWINDOW_H__
#define WINDOWS_MAINWINDOW_H__

#include <QHash>
#include <QMainWindow>
#include <QString>

#include "GLWindow.h"

// GraphiX Library
#include "graphix.h"

// Glue
#include "Glu/Algorithms.h"

class QAction;
class QActionGroup;
class QMenu;
class QResizeEvent;
class QTabWidget;
class QToolBar;

/**
 * MainWindow
 * The main application window
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  /**
   * Constructor
   *
   * @param title   The title of the main window
   */
  MainWindow(const QString& title);
  
  /**
   * Destructor
   */
  virtual ~MainWindow();

protected:
  /**
   * Close event handler
   *
   * @param evt   The event to be handled
   */
  virtual void closeEvent(QCloseEvent* evt);
  
protected slots:
  /**
   * Create a new OpenGL tab
   *
   * @param ask     Determine whether to ask if directed graph or not
   *                (default = true)
   * @param directed Determine whether graph is directed or not.
   *                  (default = false)
   */
  void createGLWindow(bool ask = true, bool directed = false);
  
  /**
   * Close OpenGL tab based off of current index
   */
  void closeGLWindow();
  
  /**
   * Close an OpenGL tab
   *
   * @param idx   The index of the tab to be closed
   */
  void closeGLWindow(int idx);
  
  /**
   * Update the current tab
   *
   * @param idx   The index of the current tab
   */
  void updateCurrentTab(int idx);
  
  /**
   * Import graph
   */
  void importGraph();
  
  /**
   * Export a graph
   */
  void exportGraph();
  
  /**
   * Set GL mode to node creation
   */
  void setNodeCreateMode();
  
  /**
   * Set GL mode to edge creation
   */
  void setEdgeCreateMode();
  
  /**
   * Set to edit mode
   */
  void setEditMode();
  
  /**
   * Set node label
   */
  void setNodeLabel();
  
  /**
   * Set edge weight
   */
  void setEdgeWeight();
  
  /**
   * Set color of selected
   */
  void setColor();
  
  /**
   * Set labels left
   */
  void labelLeft();
  
  /**
   * Set labels right
   */
  void labelRight();
  
  /**
   * Set labels up
   */
  void labelUp();
  
  /**
   * Set labels down
   */
  void labelDown();
  
  /**
   * Set labels in
   */
  void labelIn();
  
  /**
   * Run Shortest Path Algorithm
   */
  void runShortestPath();
  
  /**
   * Run Minimum spanning tree
   */
  void runMST();
  
  /**
   * Run max matching
   */
  void runMaxMatch();
  
  /**
   * Run bipartite sets
   */
  void runBipartite();
  
  /**
   * Run max network
   */
  void runMaxNet();
  
  /**
   * Odd Cycle
   */
  void runOdd();
  
  /**
   * Run Euler
   */
  void runEuler();
  
  /**
   * Get prufer code
   */
  void runPrufer();
  
  /**
   * Import prufer code
   */
  void importPrufer();
  
  /**
   * Run SCC
   */
  void runSCC();
  
  /**
   * Import graphic sequence
   */
  void importGraphicSeq();
  
  /**
   * Run all pairs
   */
  void runAllPairs();
  
private:
  /**
   * Initialize action items (private helper)
   */
  void initActions();
  
  /**
   * Initialize menu items (private helper)
   */
  void initMenus();
  
  /**
   * Initialize content [i.e. tab widget] (private helper)
   */
  void initContent();
  
  /**
   * Initialize toolbar (private helper)
   */
  void initToolBar();
  
  /**
   * Build file menu (private helper)
   */
  void buildFileMenu();
  
  /**
   * Build edit menu (private helper)
   */
  void buildEditMenu();
  
  /**
   * Build modes menu (private helper)
   */
  void buildModesMenu();
  
  /**
   * Build algorithm menu (private helper)
   */
  void buildAlgMenu();
  
  /**
   * Add an action to the enableDisableMap (private helper)
   *
   * @param key   The key to store the action
   * @param act   The action to be stored
   */
  void addActionToMap(int key, QAction* act);
  
  /**
   * Retrieve an element from enableDisableMap
   *
   * @param key   The key to retrieve the action
   * @return  A pointer to the action
   */
  QAction* retrieveActionFromMap(int key);
  
  /**
   * Update whether item is enabled or disabled
   *
   * @param key     Key of the element to be enabled/disabled
   * @param enable  If true, then enable the item. Otherwise, disable
   */
  void enableAction(int key, bool enable);
  
  /**
   * Update the GL mode for all tabs
   *
   * @param mode   The graph mode
   */
  void updateMode(GRAPHIX::MODES mode);
  
  /**
   * Run a specified algorithm
   *
   * @param alg   The algorithm to run
   */
  void runAlgorithm(ALGORITHMS alg);
  
  /**
   * Notify the user an error has occurred
   *
   * @param alg     The algorithm on which the error occurred
   * @param result  The result code from the error
   */
  void notifyError(ALGORITHMS alg, int result);
  
  /**
   * Update the conditional window options for a particular
   * tab
   *
   * @param tab   The current tab
   */
  void updateMenus(GLWindow* tab);
  
  /**
   * Update label position
   *
   * @param pos   Position
   */
  void updateLabelPosition(TEXTPOSITION pos);
  
  /** Private members **/
  int currentTabIdx;
  
  QToolBar* toolBar;

  QTabWidget* glTabs;

  QMenu* fileMenu;
  QMenu* editMenu;
  QMenu* modesMenu;
  QMenu* algorithmMenu;
  
  QHash<int, QAction*> enableDisableMap;
  
  QActionGroup* modesGrp;
  QActionGroup* algorithmsGrp;
  QActionGroup* editGrp;
};

#endif /* WINDOWS_MAINWINDOW_H__ */

