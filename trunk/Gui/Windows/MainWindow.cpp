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

void MainWindow::initActions()
{
  buildFileMenu();
  buildEditMenu();
  buildModesMenu();
  buildAlgMenu();
}

void MainWindow::initMenus()
{
  fileMenu  = menuBar()->addMenu(MAINWINDOW_FILE_MENU);
  editMenu  = menuBar()->addMenu(MAINWINDOW_EDIT_MENU);
  modesMenu = menuBar()->addMenu(MAINWINDOW_MODES_MENU);
  algorithmMenu = menuBar()->addMenu(MAINWINDOW_ALG_MENU);
}

void MainWindow::initContent()
{
  glTabs = new QTabWidget(this);
  glTabs->setTabsClosable(true);
  glTabs->setMovable(true);
  connect(glTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeGLWindow(int)));
  connect(glTabs, SIGNAL(currentChanged(int)), this, SLOT(updateCurrentTab(int)));
  this->setCentralWidget(glTabs);
}

void MainWindow::buildFileMenu()
{
  // File actions
  QAction* actNew = new QAction(MAINWINDOW_FILE_NEW, this);
  actNew->setShortcut(QKeySequence::AddTab);
  
  QAction* actCloseT = new QAction(MAINWINDOW_FILE_CLOSETAB, this);
  actCloseT->setShortcut(QKeySequence::Close);
  actCloseT->setEnabled(false);
  
  QAction* actImport = new QAction(MAINWINDOW_FILE_IMPORT, this);
  actImport->setShortcut(QKeySequence::Open);
  actImport->setEnabled(false); // Currently not implemented
  
  QAction* actExport = new QAction(MAINWINDOW_FILE_EXPORT, this);
  actExport->setShortcut(QKeySequence::Save);
  actExport->setEnabled(false);
  
  QAction* actExit = new QAction(MAINWINDOW_FILE_CLOSE, this);
          
  // Make the items do something
  connect(actNew, SIGNAL(triggered()), this, SLOT(createGLWindow()));
  connect(actCloseT, SIGNAL(triggered()), this, SLOT(closeGLWindow()));
  connect(actExit, SIGNAL(triggered()), qApp, SLOT(quit()));
  
  // Add to menu
  fileMenu->addAction(actNew);
  fileMenu->addAction(actCloseT);
  fileMenu->addSeparator();
  fileMenu->addAction(actImport);
  fileMenu->addAction(actExport);
  fileMenu->addSeparator();
  fileMenu->addAction(actExit);
  
  // Important conditionally enabled/disabled items
  addActionToMap(MAINWINDOW_FILE_CLOSETAB_ID, actCloseT);
  addActionToMap(MAINWINDOW_FILE_EXPORT_ID, actExport);
}

void MainWindow::buildEditMenu()
{
  // Edit actions
  QAction* editAddEdge = new QAction(MAINWINDOW_EDIT_ADDEDGE, this);
  editAddEdge->setEnabled(false);
  
  QAction* editRemove = new QAction(MAINWINDOW_EDIT_REMOVENODE, this);
  editRemove->setEnabled(false);
  
  // Add to menu
  editMenu->addAction(editAddEdge);
  editMenu->addSeparator();
  editMenu->addAction(editRemove);
}

void MainWindow::buildModesMenu()
{
  modesGrp = new QActionGroup(this);
  
  QAction* modeCNode = new QAction(MAINWINDOW_MODES_NODECREATION, this);
  modeCNode->setShortcut(QKeySequence(tr("Ctrl+1")));
  connect(modeCNode, SIGNAL(triggered()), this, SLOT(setNodeCreateMode()));

  QAction* modeCEdge = new QAction(MAINWINDOW_MODES_EDGECREATION, this);
  modeCEdge->setShortcut(QKeySequence(tr("Ctrl+2")));
  connect(modeCEdge, SIGNAL(triggered()), this, SLOT(setEdgeCreateMode()));
  
  QAction* modeView = new QAction(MAINWINDOW_MODES_VIEWONLY, this);
  modeView->setShortcut(QKeySequence(tr("Ctrl+3")));
  connect(modeView, SIGNAL(triggered()), this, SLOT(setViewMode()));
  
  modesMenu->addAction(modeCNode);
  modesMenu->addAction(modeCEdge);
  modesMenu->addAction(modeView);
  
  modesGrp->addAction(modeCNode);
  modesGrp->addAction(modeCEdge);
}

void MainWindow::buildAlgMenu()
{
  // Init action group
  algorithmsGrp = new QActionGroup(this);
  
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
  
  // Actions
  connect(algShort, SIGNAL(triggered()), this, SLOT(runShortestPath()));
  
  // Add to menu
  algorithmMenu->addAction(algShort);
  algorithmMenu->addAction(algMST);
  algorithmMenu->addAction(algMaxM);
  algorithmMenu->addAction(algMinVtx);
  algorithmMenu->addAction(algMaxNet);
  algorithmMenu->addAction(algMinXY);
  algorithmMenu->addSeparator();
  algorithmMenu->addAction(algChromNo);
  algorithmMenu->addAction(algPartite);
  algorithmMenu->addAction(algCycles);
  algorithmMenu->addAction(algEuler);
  algorithmMenu->addAction(algCenter);
  algorithmMenu->addSeparator();
  algorithmMenu->addAction(algPrufer);
  algorithmMenu->addAction(algdeB);
  
  // Add to action group
  algorithmsGrp->addAction(algShort);
  algorithmsGrp->addAction(algMST);
  algorithmsGrp->addAction(algMaxM);
  algorithmsGrp->addAction(algMinVtx);
  algorithmsGrp->addAction(algMaxNet);
  algorithmsGrp->addAction(algMinXY);
  algorithmsGrp->addAction(algChromNo);
  algorithmsGrp->addAction(algPartite);
  algorithmsGrp->addAction(algCycles);
  algorithmsGrp->addAction(algEuler);
  algorithmsGrp->addAction(algCenter);
  algorithmsGrp->addAction(algPrufer);
  algorithmsGrp->addAction(algdeB);
}

/* Internal private helpers (i.e. not directly gui related) */
void MainWindow::addActionToMap(int key, QAction* act)
{
  enableDisableMap[key] = act;
}

QAction* MainWindow::retrieveActionFromMap(int key)
{
  return enableDisableMap[key];
}

void MainWindow::enableAction(int key, bool enable)
{
  QAction* act = retrieveActionFromMap(key);
  if(act != NULL && act->isEnabled() != enable)
    act->setEnabled(enable);
}

void MainWindow::updateMode(GRAPHIX::MODES mode)
{
  for(int i = 0 ; i < glTabs->count() ; ++i) {
    GLWindow* gl = static_cast<GLWindow*>(glTabs->widget(i));
    if(gl != NULL)
      gl->updateMode(mode);
  }
}

/* Signals/Slots */
void MainWindow::createGLWindow()
{
  GLWindow* glWindow = new GLWindow(this);
  int idx = glTabs->addTab(glWindow, "Graph");
  glTabs->setCurrentIndex(idx);
  enableAction(MAINWINDOW_FILE_CLOSETAB_ID, true);
  
  // Set everyone back to node creation mode
  updateMode(GRAPHIX::NODECREATION);
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
  if(idx == -1) {
    enableAction(MAINWINDOW_FILE_CLOSETAB_ID, false);
  } else {
    GLWindow* tab = static_cast<GLWindow*>(glTabs->widget(idx));
    if(tab != NULL) {
      tab->makeCurrent();
      tab->makeOverlayCurrent();
      updateMenus(tab);
    }
  }
}

void MainWindow::setNodeCreateMode()
{
  updateMode(GRAPHIX::NODECREATION);
}

void MainWindow::setEdgeCreateMode()
{
  updateMode(GRAPHIX::EDGECREATION);
}

void MainWindow::setViewMode()
{
  updateMode(GRAPHIX::VIEWONLY);
}

void MainWindow::runShortestPath()
{
  runAlgorithm(SHORTESTPATH);
}

void MainWindow::runAlgorithm(ALGORITHMS alg)
{
  QMessageBox msg(QMessageBox::Warning, tr("Confirm"), MAINWINDOW_ALGDLG_CONFIRM, QMessageBox::Ok|QMessageBox::Cancel, this);
  
  GLWindow* tab = static_cast<GLWindow*>(glTabs->widget(currentTabIdx));
  
  if(tab->isLocked())
    return;
  
  int confirm = msg.exec();
  
  if(confirm != QMessageBox::Ok)
    return;
  
  int result = tab->runAlgorithm(alg);
  
  if(result < 0) { // Error
    notifyError(alg, result);
  }
  
  updateMenus(tab);
}

void MainWindow::notifyError(ALGORITHMS alg, int result)
{
  QMessageBox err(QMessageBox::Critical, tr("Error"), tr(""), QMessageBox::Ok, this);
  
  QString msg;
  
  switch(alg)
  {
    case SHORTESTPATH:
      if(result == -1)
        msg = MAINWINDOW_ERRDLG_SHORTEST_1;
      else
        msg = MAINWINDOW_ERRDLG_SHORTEST_2;
      break;
    case MST:
      break;
    default:
      break;
  }
  
  err.setText(msg);
  err.exec();
}

void MainWindow::updateMenus(GLWindow* tab)
{
  if(tab == NULL)
    return;
  
  bool enabled = !tab->isLocked();
  
  modesGrp->setEnabled(enabled);
  algorithmsGrp->setEnabled(enabled);
}
