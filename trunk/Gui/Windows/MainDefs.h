/**
 * Application: AbstractGraph
 * Module: GUI
 * File: MainDefs.h
 * Description: Main Application window definitions
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef WINDOWS_MAINDEFS_H__
#define WINDOWS_MAINDEFS_H__

// NOTE: To use this file, make sure <QString> is
// included _BEFORE_ this is included

// Menus
#define MAINWINDOW_FILE_MENU tr("&File")
#define MAINWINDOW_EDIT_MENU tr("&Edit")
#define MAINWINDOW_ALG_MENU  tr("&Algorithms")

// File Menu Actions
#define MAINWINDOW_FILE_IMPORT tr("I&mport")
#define MAINWINDOW_FILE_EXPORT tr("E&xport")
#define MAINWINDOW_FILE_NEW tr("N&ew Tab")
#define MAINWINDOW_FILE_CLOSETAB tr("C&lose Current Tab")
#define MAINWINDOW_FILE_CLOSE tr("C&lose")

// Algorithm Menu Actions
#define MAINWINDOW_ALG_SHORTEST tr("S&hortest Path")
#define MAINWINDOW_ALG_MST tr("M&inimum Spanning Tree")
#define MAINWINDOW_ALG_MAXMATCH tr("M&aximum Matching")
#define MAINWINDOW_ALG_MINVTXCOV tr("M&inimum Vertex Cover")
#define MAINWINDOW_ALG_MAXNET tr("M&aximum Network Flow")
#define MAINWINDOW_ALG_MINXY tr("M&inimum X-Y Cut")
#define MAINWINDOW_ALG_CHROMNO tr("Chromatic Number")
#define MAINWINDOW_ALG_PARTITE tr("Partite Sets")
#define MAINWINDOW_ALG_CYCLES tr("O&dd Cycle Detection")
#define MAINWINDOW_ALG_EULER tr("E&uler Paths/Circuits")
#define MAINWINDOW_ALG_CENTER tr("Center of Graph")
#define MAINWINDOW_ALG_PRUFER tr("Prufer Code (Trees)")
#define MAINWINDOW_ALG_DEBRUIJN tr("de Bruijn Cycles")

// Edit Menu Actions
#define MAINWINDOW_EDIT_REMOVENODE tr("R&emove Node")
#define MAINWINDOW_EDIT_ADDEDGE tr("A&dd Edge")

#endif /* WINDOWS_MAINDEFS_H__ */
