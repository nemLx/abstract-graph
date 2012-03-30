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

#include "MainWindow.h"
#include "MainDefs.h"

MainWindow::MainWindow(const QString& title)
{
  this->setWindowTitle(title);
  initMenus();
  initActions();
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

void MainWindow::buildFileMenu()
{
  // File actions
  QAction* actNew = new QAction(MAINWINDOW_FILE_NEW, this);
  actNew->setShortcut(QKeySequence::New);
  
  QAction* actImport = new QAction(MAINWINDOW_FILE_IMPORT, this);
  actImport->setShortcut(QKeySequence::Open);
  
  QAction* actExport = new QAction(MAINWINDOW_FILE_EXPORT, this);
  actExport->setShortcut(QKeySequence::Save);
  actExport->setEnabled(false);
  
  QAction* actExit = new QAction(MAINWINDOW_FILE_CLOSE, this);
  connect(actExit, SIGNAL(triggered()), qApp, SLOT(quit()));
  
  // Add them in order to the respective list
  fileActions.push_back(actNew);
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
