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

// General stuff
#define MAINWINDOW_GENERAL_OK tr("Ok")
#define MAINWINDOW_GENERAL_CANCEL tr("Cancel")

// Menus
#define MAINWINDOW_FILE_MENU tr("&File")
#define MAINWINDOW_EDIT_MENU tr("&Edit")
#define MAINWINDOW_MODES_MENU tr("&Modes")
#define MAINWINDOW_ALG_MENU  tr("&Algorithms")

// File Menu Actions
#define MAINWINDOW_FILE_IMPORT tr("I&mport")
#define MAINWINDOW_FILE_EXPORT tr("E&xport")
#define MAINWINDOW_FILE_NEW tr("N&ew Tab")
#define MAINWINDOW_FILE_CLOSETAB tr("C&lose Current Tab")
#define MAINWINDOW_FILE_CLOSE tr("C&lose")

// Edit Menu Actions
#define MAINWINDOW_EDIT_REMOVENODE tr("R&emove Node")
#define MAINWINDOW_EDIT_ADDEDGE tr("A&dd Edge")

// Modes Menu Actions
#define MAINWINDOW_MODES_NODECREATION tr("N&ode Creation")
#define MAINWINDOW_MODES_EDGECREATION tr("E&dge Creation")
#define MAINWINDOW_MODES_VIEWONLY tr("V&iew Only")

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

// Toolbar text
#define MAINWINDOW_TLBR_NODECREATE tr("Node Creation Mode")
#define MAINWINDOW_TLBR_EDGECREATE tr("Edge Creation Mode")
#define MAINWINDOW_TLBR_NODELABEL tr("Node Label")
#define MAINWINDOW_TLBR_EDGELABEL tr("Edge Label")
#define MAINWINDOW_TLBR_NODECOLOR tr("Node Color")
#define MAINWINDOW_TLBR_EDGECOLOR tr("Edge Color")
#define MAINWINDOW_TLBR_EDGEWEIGHT tr("Edge Weight")

// IDs for hashing (only for ones which need it)
// File gets 0x1000 block
#define MAINWINDOW_FILE_EXPORT_ID 0x1001
#define MAINWINDOW_FILE_CLOSETAB_ID 0x1002

// Dialog texts
#define MAINWINDOW_ALGDLG_CONFIRM tr("Are you sure you wish to run this algorithm? After you run an algorithm, the graph will become VIEW ONLY")

// Error dialog texts
#define MAINWINDOW_ERRDLG_FAILWRITE tr("Failed to write file: %1")
#define MAINWINDOW_ERRDLG_SHORTEST_1 tr("The operation was cancelled. No path exists between the selected nodes. Please try again.")
#define MAINWINDOW_ERRDLG_SHORTEST_2 tr("The operation was cancelled. Please ensure that you have exactly two nodes selected (i.e. a start and an end) before running this algorithm.")
#define MAINWINDOW_ERRDLG_MAX_MATCH_1 tr("The operation was cancelled. This is not a bipartite graph.")

#endif /* WINDOWS_MAINDEFS_H__ */
