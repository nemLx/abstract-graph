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

protected:
  /**
   * Initialize the OpenGL renderer
   */
  void initalizeGL();
  
  /**
   * Resize OpenGL Render window
   *
   * @param w   New width
   * @param h   New height
   */
  void resizeGL(int w, int h);
  
  /**
   * Paint the GL window
   */
  void paintGL();
  
  /**
   * Handle mouse press events
   */
  void mousePressEvent(QMouseEvent* evt);
  
  /**
   * Handle mouse move events
   */
  void mouseMoveEvent(QMouseEvent* evt);
  
  /**
   * Handle key press events
   */
  void keyPressEvent(QKeyEvent* evt);
};

#endif /* WINDOWS_GLWINDOW_H__ */
