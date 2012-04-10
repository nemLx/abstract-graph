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

#include <QtOpenGL/QGLWidget>
#include "graphix.h"

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

protected slots:
  /**
   * Delete the selected items
   */
  void deleteSelected();
  
  /**
   * Update label for selected items
   */
  void updateLabel();
  
private:
  /**
   * Draw labels
   */
  void drawLabels();
  
  GRAPHIX::Scene scene;
  NodeOptionsMenu* nodeRightClick;
};

#endif /* WINDOWS_GLWINDOW_H__ */
