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

#include <QList>
#include <QMainWindow>
#include <QString>

class QAction;
class QMenu;
class QResizeEvent;
class QTabWidget;

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
   */
  void createGLWindow();
  
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
   * Build file menu (private helper)
   */
  void buildFileMenu();
  
  /**
   * Build edit menu (private helper)
   */
  void buildEditMenu();
  
  /**
   * Build algorithm menu (private helper)
   */
  void buildAlgMenu();
  
  int currentTabIdx;
  
  QTabWidget* glTabs;

  QMenu* fileMenu;
  QMenu* editMenu;
  QMenu* algorithmMenu;
  
  QList<QAction*> fileActions;
  QList<QAction*> algorithmActions;
  QList<QAction*> editActions;
};

#endif /* WINDOWS_MAINWINDOW_H__ */

