/**
 * Application: AbstractGraph
 * Module: GUI
 * File: main.cpp
 * Description: Main entry point to GUI frontend of Abstract graph
 *              application
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include <QApplication>
#include <QPushButton>

#ifdef WIN32
// WIN32 routines
#else
// NOTE: Just a dummy button right now
int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  QPushButton button("Test Me!");
  button.resize(500, 500);
  button.show();
  return app.exec();
}
#endif

