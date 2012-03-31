/**
 * Application: AbstractGraph
 * Module: GUI
 * File: Windows/MainWindow.cpp
 * Description: Main window implementation for GUI application
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include <QtGui>

#include "GLWindow.h"
#include "MainWindow.h"
#include "MainDefs.h"

/* Main UI Setup */
MainWindow::MainWindow(const QString& title)
  : currentTabIdx(-1)
{
  this->setWindowTitle(title);
  
  initMenus();
  initActions();
  initContent();
}

MainWindow::~MainWindow()
{
  // Only needed for objects without parents
  // Qt is nice and cleans up for us!
}

void MainWindow::closeEvent(QCloseEvent* evt)
{
  // Do nothing for now
}

void MainWindow::resizeEvent(QResizeEvent* evt)
{
  QWidget::resizeEvent(evt);
  glTabs->setFixedSize(width(), height());
}

void MainWindow::initActions()
{
  buildFileMenu();
  buildEditMenu();
  buildAlgMenu();
}

void MainWindow::initMenus()
{
  fileMenu = menuBar()->addMenu(MAINWINDOW_FILE_MENU);
  editMenu = menuBar()->addMenu(MAINWINDOW_EDIT_MENU);
  algorithmMenu = menuBar()->addMenu(MAINWINDOW_ALG_MENU);
}

void MainWindow::initContent()
{
  glTabs = new QTabWidget(this);
  glTabs->setTabsClosable(true);
  glTabs->setMovable(true);
  connect(glTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeGLWindow(int)));
  connect(glTabs, SIGNAL(currentChanged(int)), this, SLOT(updateCurrentTab(int)));
}

void MainWindow::buildFileMenu()
{
  // File actions
  QAction* actNew = new QAction(MAINWINDOW_FILE_NEW, this);
  actNew->setShortcut(QKeySequence::New);
  
  QAction* actCloseT = new QAction(MAINWINDOW_FILE_CLOSETAB, this);
  actCloseT->setShortcut(QKeySequence::Close);
  //actCloseT->setEnabled(false);
  
  QAction* actImport = new QAction(MAINWINDOW_FILE_IMPORT, this);
  actImport->setShortcut(QKeySequence::Open);
  
  QAction* actExport = new QAction(MAINWINDOW_FILE_EXPORT, this);
  actExport->setShortcut(QKeySequence::Save);
  actExport->setEnabled(false);
  
  QAction* actExit = new QAction(MAINWINDOW_FILE_CLOSE, this);
          
  // Make the items do something
  connect(actNew, SIGNAL(triggered()), this, SLOT(createGLWindow()));
  connect(actCloseT, SIGNAL(triggered()), this, SLOT(closeGLWindow()));
  connect(actExit, SIGNAL(triggered()), qApp, SLOT(quit()));
  
  // Add them in order to the respective list
  fileActions.push_back(actNew);
  fileActions.push_back(actCloseT);
  fileActions.push_back(actImport);
  fileActions.push_back(actExport);
  fileActions.push_back(actExit);
  
  // Add to menu
  fileMenu->addActions(fileActions);
  fileMenu->insertSeparator(actExit);
  fileMenu->insertSeparator(actImport);
}

void MainWindow::buildEditMenu()
{
  // Edit actions
  QAction* editAddEdge = new QAction(MAINWINDOW_EDIT_ADDEDGE, this);
  editAddEdge->setEnabled(false);
  
  QAction* editRemove = new QAction(MAINWINDOW_EDIT_REMOVENODE, this);
  editRemove->setEnabled(false);
  
  // Add to list
  editActions.push_back(editAddEdge);
  editActions.push_back(editRemove);
  
  // Add to menu
  editMenu->addActions(editActions);
  editMenu->insertSeparator(editRemove);
}

void MainWindow::buildAlgMenu()
{
  // Algorithm Actions
  QAction* algShort = new QAction(MAINWINDOW_ALG_SHORTEST, this);
  
  QAction* algMST = new QAction(MAINWINDOW_ALG_MST, this);
  
  QAction* algMaxM = new QAction(MAINWINDOW_ALG_MAXMATCH, this);
  
  QAction* algMinVtx = new QAction(MAINWINDOW_ALG_MINVTXCOV, this);
  
  QAction* algMaxNet = new QAction(MAINWINDOW_ALG_MAXNET, this);
  
  QAction* algMinXY = new QAction(MAINWINDOW_ALG_MINXY, this);
  
  QAction* algChromNo = new QAction(MAINWINDOW_ALG_CHROMNO, this);
  
  QAction* algPartite = new QAction(MAINWINDOW_ALG_PARTITE, this);
  
  QAction* algCycles = new QAction(MAINWINDOW_ALG_CYCLES, this);
  
  QAction* algEuler = new QAction(MAINWINDOW_ALG_EULER, this);
  
  QAction* algCenter = new QAction(MAINWINDOW_ALG_CENTER, this);
  
  QAction* algPrufer = new QAction(MAINWINDOW_ALG_PRUFER, this);
  
  QAction* algdeB = new QAction(MAINWINDOW_ALG_DEBRUIJN, this);
  
  algorithmActions.push_back(algShort);
  algorithmActions.push_back(algMST);
  algorithmActions.push_back(algMaxM);
  algorithmActions.push_back(algMinVtx);
  algorithmActions.push_back(algMaxNet);
  algorithmActions.push_back(algMinXY);
  algorithmActions.push_back(algChromNo);
  algorithmActions.push_back(algPartite);
  algorithmActions.push_back(algCycles);
  algorithmActions.push_back(algEuler);
  algorithmActions.push_back(algCenter);
  algorithmActions.push_back(algPrufer);
  algorithmActions.push_back(algdeB);
  
  // Add to menu
  algorithmMenu->addActions(algorithmActions);
  algorithmMenu->insertSeparator(algChromNo);
  algorithmMenu->insertSeparator(algPrufer);
}

/* Signals/Slots */
void MainWindow::createGLWindow()
{
  GLWindow* glWindow = new GLWindow(this);
  glTabs->addTab(glWindow, "OpenGL Tab");
}

void MainWindow::closeGLWindow()
{
  closeGLWindow(currentTabIdx);
}

void MainWindow::closeGLWindow(int idx)
{
  if(glTabs->count() <= idx) // Paranoia
    return;
  QWidget* widget = glTabs->widget(idx);
  glTabs->removeTab(idx);
  delete widget;
}

void MainWindow::updateCurrentTab(int idx)
{
  currentTabIdx = idx;
}
