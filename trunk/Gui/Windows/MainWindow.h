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

class QMenu;
class QAction;

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
  void closeEvent(QCloseEvent* evt);

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

  QMenu* fileMenu;
  QMenu* editMenu;
  QMenu* algorithmMenu;
  
  QList<QAction*> fileActions;
  QList<QAction*> algorithmActions;
  QList<QAction*> editActions;
};

#endif /* WINDOWS_MAINWINDOW_H__ */

