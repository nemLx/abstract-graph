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

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "graphix_incl.h"
#include "../Gfx/Shape.h"
#include "../Control/Mode.h"

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
   * Add a shape. Method added for flexibility in
   * scene, however, should be unnecessary for standard
   * graph applications.
   *
   * @param shape   SHAPE type
   * @param x       X coordinate (window coord)
   * @param y       Y coordinate (window coord)
   */
  void addShape(SHAPES shape, int x, int y);
  
  /**
   * Register a click with the scene
   *  The current mode should handle accordingly
   *
   * @param x   X coordinate (window coord)
   * @param y   Y coordinate (window coord)
   */
  void registerClick(int x, int y);
  
  /**
   * Update the mode
   *
   * @param mode    The new mode to enter
   */
  void updateMode(GRAPHIX::MODES mode);
  
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
  
  /**
   * Update the selected item(s) labels
   *
   * @param label   The label to set
   */
  void updateLabel(const std::string& label);
  
  /**
   * Update the color of selected items
   *
   * @param red   Red value
   * @param green Green value
   * @param blue  Blue value
   */
  void updateSelectedColor(unsigned red, unsigned green, unsigned blue);
  
  /**
   * Update the highlight of selected items
   *
   * @param red   Red value
   * @param green Green value
   * @param blue  Blue value
   */
  void updateSelectedHighlight(unsigned red, unsigned green, unsigned blue);
  
  /**
   * Add a public ID to last added shape
   *
   * @param id    The public id
   */
  void setLastId(int id);
  
  /**
   * Check if there are any selected nodes
   *
   * @return  True if there are nodes selected, false otherwise
   */
  bool checkNodesSelected() const;
  
  /**
   * Get the number of items selected
   *
   * @return  The number of selected items
   */
  unsigned countSelected() const;
  
  /**
   * Delete selected items
   */
  void deleteSelected();
  
  /**
   * Get a list of labels for currently
   * selected items
   *
   * @return  A vector of labels
   */
  std::vector<std::string> getSelectedLabels() const;
  
  /**
   * Get a list of labels
   *
   * @return  A vector of labels
   */
  std::vector<std::string> getLabels() const;
  
  /**
   * Get a list of ordered coordinates for labels
   * NOTE: Coords are in terms of window
   *
   * @return  A vector of pairs of coordinates
   */
  std::vector<std::pair<int, int> > getCoords() const;

protected:
  /**
   * Pick the scene (make sure nothing was clicked)
   *
   * @param x   X coordinate to check
   * @param y   Y coordinate to check
   */
  virtual unsigned pickScene(float x, float y);
  
  /**
   * Remove an item from the shapes list
   *
   * @param shape   A pointer to the shape
   */
  virtual void removeShapeFromList(Shape* shape);
  
private:
  /**
   * Remove and delete an item from the list
   *
   * @param shape   Pointer to remove/delete
   */
  virtual void removeAndDelete(Shape* shape);
  
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
   * Convert from OpenGL coordinates to window coords
   *
   * @param glX   X (opengl) coordinate
   * @param glY   Y (opengl) coordinate
   * @param x     Converted x
   * @param y     Converted y
   */
  void GLToWindow(double glX, double glY, double& x, double& y) const;
  
  /**
   * Get a list of labels for a particular
   * vector set
   *
   * @param vector  The vector to traverse
   * @return  A list of labels
   */
  std::vector<std::string> getLabels(const std::vector<Shape*>& vector) const;
  
  /**
   * Copy data (private helper)
   */
  void copy(const Scene& rhs);
  
  /**
   * Clean up current structure
   */
  void destroy();
  
  /**
   * Resize pick buffer
   */
  void resizePickBuffer();
  
  std::vector<Shape*> shapes;
  std::vector<Shape*> selected;
  std::map<MODES, Mode*> modes;
  Mode* currentMode;
  int viewport[4];
  unsigned* pickBuffer;
  unsigned bufferSize;
};
}
#endif /* GRAPHIX_SCENE_SCENE_H__ */

