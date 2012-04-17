/**
 * Application: AbstractGraph
 * Module: GUI
 * File: GLWindow.h
 * Description: Interface for OpenGL window implementation
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef WINDOWS_GLWINDOW_H__
#define WINDOWS_GLWINDOW_H__

#include <QtGui/QColor>

#include <QtOpenGL/QGLWidget>

// GraphiX Library
#include "graphix.h"

// Glu
#include "Glu/AlgorithmsGlu.h"

class NodeOptionsMenu;
class QWidget;

class GLWindow : public QGLWidget
{
  Q_OBJECT
public:
  /**
   * Constructor
   *
   * @param parent    The parent widget
   */
  GLWindow(QWidget* parent = NULL);
  
  /**
   * Destructor
   */
  virtual ~GLWindow();
  
  /**
   * Update the mode of all tabs
   */
  virtual void updateMode(GRAPHIX::MODES mode);
  
  /**
   * Render text onto GL window
   *
   * @param x     X coordinate
   * @param y     Y coordinate
   * @param str   String to render
   * @param font  Font to use (Default = QFont())
   * @param base  Default = 2000
   */
  virtual void renderText(int x, int y, const QString& str, const QFont& font = QFont(), int base = 2000);
  
  /**
   * Check if graph locked
   *
   * @return  True if locked, false otherwise
   */
  virtual bool isLocked() const;
  
  /**
   * Set the graph lock
   *
   * @param lock   True to lock graph, false otherwise
   */
  virtual void lock(bool lock);
  
  /**
   * Export graph
   */
  virtual void exportGraph();
  
  /**
   * Run an algorithm on the graph
   *
   * @param alg   The algorithm to be run
   *
   * @return  Result of the algorithm. < 0 on error
   */
  virtual int runAlgorithm(ALGORITHMS alg);
  
  /**
   * Get the scene object
   *
   * @return  A reference to the scene
   */
  virtual GRAPHIX::Scene& getScene();
  
  /**
   * Get the glue object
   *
   * @return  A reference to glue
   */
  virtual AlgorithmsGlu& getGlue();

protected:
  /**
   * Initialize the OpenGL renderer
   */
  virtual void initalizeGL();
  
  /**
   * Resize OpenGL Render window
   *
   * @param w   New width
   * @param h   New height
   */
  virtual void resizeGL(int w, int h);
  
  /**
   * Paint the GL window
   */
  virtual void paintGL();
  
  /**
   * Handle mouse press events
   *
   * @param evt   The event caught
   */
  virtual void mousePressEvent(QMouseEvent* evt);
  
  /**
   * Handle mouse move events
   *
   * @param evt   The event caught
   */
  virtual void mouseMoveEvent(QMouseEvent* evt);
  
  /**
   * Handle key press events
   *
   * @param evt   The event caught
   */
  virtual void keyPressEvent(QKeyEvent* evt);
  
  /**
   * Override the "right-click" operation
   *
   * @param evt   The caught event
   */
  virtual void contextMenuEvent(QContextMenuEvent* evt);
  
public slots:
  /**
   * Update label for selected items
   */
  void updateLabel();
  
  /**
   * Update edge weights
   */
  void updateWeight();
  
  /**
   * Update the color for the selected
   * items
   */
  void updateColor();

protected slots:
  /**
   * Delete the selected items
   */
  void deleteSelected();
  
  /**
   * Update the highlight color
   */
  void updateHighlight();
  
  /**
   * Update the background color
   */
  void updateBackground();
  
  /**
   * Select all
   */
  void selectAll();
  
  /**
   * Deselect all
   */
  void deselectAll();
  
private:
  /**
   * Draw labels
   */
  void drawLabels();
  
  /**
   * Draw weights
   */
  void drawWeights();
  
  /**
   * Display a color dialog
   *
   * @param color   Red, green, blue color values (initial)
   *     this value will be updated with the NEW color
   * @return  True if color is valid, false otherwise.
   */
  bool showColorDialog(QColor& color);
  
  GRAPHIX::Scene scene;
  NodeOptionsMenu* nodeRightClick;
  bool locked;
  bool enableWeights;
  AlgorithmsGlu gluAlg;
};

#endif /* WINDOWS_GLWINDOW_H__ */
