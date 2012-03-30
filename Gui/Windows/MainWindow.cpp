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

MainWindow::MainWindow(const QString& title)
{
  this->setWindowTitle(title);
  
  initActions();
  initMenus();
}

MainWindow::~MainWindow()
{
  delete actExit;
}

void MainWindow::closeEvent(QCloseEvent* evt)
{
  // Do nothing for now
}

void MainWindow::initActions()
{
  actExit = new QAction(tr("&Close"), this);
  connect(actExit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::initMenus()
{
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addSeparator();
  fileMenu->addAction(actExit);
}

