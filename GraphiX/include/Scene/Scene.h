/**
 * Application: GraphiX Library
 * Module: Library
 * File: Scene.h
 * Description: The basic graph scene
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef GRAPHIX_SCENE_SCENE_H__
#define GRAPHIX_SCENE_SCENE_H__

#include <vector>

#include "graphix_incl.h"
#include "../Gfx/Shape.h"

namespace GRAPHIX
{
/**
 * Scene class which manages the canvas
 *
 * NOTE: Assumes already running within a valid
 *    rendering context
 */
class GRAPHIX_EXPORT Scene
{
public:
  /**
   * Constructor
   *
   * NOTE: Plan to support 2D and 3D in the future
   * but for now only supporting 2D scenes
   */
  Scene();
  
  /**
   * Copy constructor
   */
  Scene(const Scene& rhs);
  
  /**
   * Assignment operator
   */
  Scene& operator=(const Scene& rhs);

  /**
   * Destructor
   */
  virtual ~Scene();

  /**
   * Redraw the scene
   *
   * @return  A pointer to the array of selected objects. NULL if nothing selected
   */
  virtual unsigned* updateScene();
  
  /**
   * Add a shape
   *
   * @param shape   SHAPE type
   * @param x       X coordinate (window coord)
   * @param y       Y coordinate (window coord)
   */
  void addShape(SHAPES shape, int x, int y);
  
  /**
   * updateGLSize
   *
   * @param w   New width
   * @param h   New height
   */
  void updateGLSize(int w, int h);
  
  /**
   * Updates the viewport information
   */
  void updateViewport();

protected:
  /**
   * Pick the scene (make sure nothing was clicked)
   *
   * @param x   X coordinate to check
   * @param y   Y coordinate to check
   */
  virtual unsigned pickScene(float x, float y);
  
private:
  /**
   * Convert from window coordinates to OpenGL coords
   *
   * @param winX  X (window) coordinate
   * @param winY  Y (window) coordinate
   * @param x     Converted x
   * @param y     Converted y
   */
  void windowToGL(int winX, int winY, double& x, double& y) const;
  
  /**
   * Handle hits (picking related)
   *
   * @param hits    Number of items "picked"
   */
  void hitLogic(unsigned hits);
  
  /**
   * Highlight selected nodes/edges
   *
   * @param shape   Pointer to the shape to highlight
   */
  void highlightSelected(Shape* shape);
  
  /**
   * Remove the highlighting
   */
  void removeHighlight();
  
  /**
   * Remove highlighting on a particular node
   *
   * @param shape   The selected shape
   */
  void removeHighlight(Shape* shape);
  
  /**
   * Copy data (private helper)
   */
  void copy(const Scene& rhs);
  
  /**
   * Clean up current structure
   */
  void destroy();
  
  /**
   * Get an element from the picked buffer
   *
   * @param idx   The index of the element
   * @return  A pointer to the requested element. Otherwise NULL.
   */
  unsigned char* getBufferElement(unsigned idx) const;
  
  /**
   * Resize pick buffer
   */
  void resizePickBuffer();
  
  std::vector<Shape*> shapes;
  std::vector<Shape*> selected;
  int viewport[4];
  unsigned* pickBuffer;
  unsigned bufferSize;
};
}
#endif /* GRAPHIX_SCENE_SCENE_H__ */

