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
   *
   * @param directed    Determine whether graph is directed or not
   *                    (default = false = undirected)
   */
  Scene(bool directed = false);
  
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
  virtual void addShape(SHAPES shape, int x, int y);
  
  /**
   * Add a node systematically to the canvas
   */
  virtual void addNode();
  
  /**
   * Add an edge to the canvas
   *
   * @param from    Public id of first end point
   * @param to      Public id of second end point
   */
  virtual void addEdge(int from, int to);
  
  /**
   * Register a click with the scene
   *  The current mode should handle accordingly
   *
   * @param x   X coordinate (window coord)
   * @param y   Y coordinate (window coord)
   *
   * @return  The action which happened after the click
   */
  virtual ACTION registerClick(int x, int y);
  
  /**
   * Get the current mode type
   *
   * @return  The current mode
   */
  virtual MODES getMode() const;
  
  /**
   * Move node to new positions
   *
   * @param x   X coordinate (window coord)
   * @param y   Y coordinate (window coord)
   */
  virtual void moveNodes(int x, int y);
  
  /**
   * Move a particular node
   *
   * @param id    The node's public id
   * @param x     X coordinate (window coord)
   * @param y     Y coordinate (window coord)
   */
  virtual void moveNode(int id, int x, int y);
  
  /**
   * Update the mode
   *
   * @param mode    The new mode to enter
   */
  virtual void updateMode(GRAPHIX::MODES mode);
  
  /**
   * updateGLSize
   *
   * @param w   New width
   * @param h   New height
   */
  virtual void updateGLSize(int w, int h);
  
  /**
   * Updates the viewport information
   */
  virtual void updateViewport();
  
  /**
   * Update the selected item(s) labels
   *
   * @param label   The label to set
   */
  virtual void updateLabel(const std::string& label);
  
  /**
   * Update edge weights
   *
   * @param weight  The new edge weight
   */
  virtual void updateWeight(int weight);
  
  /**
   * Update background color
   *
   * @param red   Red value
   * @param green Green value
   * @param blue  Blue value
   */
  virtual void updateBackground(unsigned red, unsigned green, unsigned blue);
  
  /**
   * Update the highlight color
   *
   * @param red   Red value
   * @param green Green value
   * @param blue  Blue value
   */
  virtual void updateHighlightColor(unsigned red, unsigned green, unsigned blue);
  
  /**
   * Update the color of selected items
   *
   * @param red   Red value
   * @param green Green value
   * @param blue  Blue value
   */
  virtual void updateSelectedColor(unsigned red, unsigned green, unsigned blue);
  
  /**
   * Add a public ID to last added shape
   *
   * @param id    The public id
   */
  virtual void setLastId(int id);
  
  /**
   * Check if there are any selected nodes
   *
   * @return  True if there are nodes selected, false otherwise
   */
  virtual bool checkNodesSelected() const;
  
  /**
   * Check edges selected
   *
   * @return  True if edges are selected, false otherwise
   */
  virtual bool checkEdgesSelected() const;
  
  /**
   * Get the number of items selected
   *
   * @param type  Type of items to check (default = ANY)
   *
   * @return  The number of selected items
   */
  virtual unsigned countSelected(SHAPES type = ANY) const;
  
  /**
   * Set selected curves to type
   *
   * @param curve   Curve type (default = NONE)
   */
  virtual void setCurves(CURVE type = NONE);
  
  /**
   * Select all
   */
  virtual void selectAll();
  
  /**
   * Deselect all
   */
  virtual void deselectAll();
  
  /**
   * Delete selected items
   *
   * @return  A vector containing pairs of shape type and id for all
   *    removed items
   */
  virtual std::vector<std::pair<SHAPES, int> > deleteSelected();
  
  /**
   * Get a list of edge weights
   *
   * @return  A vector of weights
   */
  virtual std::vector<int> getWeights() const;
  
  /**
   * Get a list of labels for currently
   * selected items
   *
   * @return  A vector of labels
   */
  virtual std::vector<std::string> getSelectedLabels() const;
  
  /**
   * Get a list of labels
   *
   * @return  A vector of labels
   */
  virtual std::vector<std::string> getLabels() const;
  
  /**
   * Get a list of ordered coordinates for labels
   * NOTE: Coords are in terms of window
   *
   * @param type  Specify type of item to obtain (default = ANY)
   *
   * @return  A vector of pairs of coordinates
   */
  virtual std::vector<std::pair<int, int> > getCoords(SHAPES type = ANY) const;
  
  /**
   * Get id's for selected items
   *
   * @param type    Type of shape to find (default = ANY)
   *
   * @return A vector of public id's
   */
  virtual std::vector<int> getSelectedIds(SHAPES type = ANY) const;
  
  /**
   * Get the last shape added to the scene
   *
   * @param type    Find the last of a particular type (default = ANY)
   * @return  The last shape (not deleted) added to the scene
   *        (of given type if specified). If no shapes currently
   *        on scene, return NULL.
   */
  virtual Shape* getLast(SHAPES type = ANY) const;
  
  /**
   * Find a shape with the given public id
   *
   * @param pubId   The public id to find
   * @param type    Type of shape (default = ANY)
   * @return  A pointer to the shape with the id. NULL if no
   *      such shape exists
   */
  virtual Shape* findShape(int pubId, SHAPES type = ANY) const;
  
  /**
   * Get a vector of shapes
   *
   * @param type    Shape type to find (default = ANY)
   * @return  A vector of shapes according to type
   */
  virtual std::vector<Shape*> getShapes(SHAPES type = ANY) const;
  
  /**
   * Return pixels as a byte array
   * NOTE: This method allocates new memory which
   *      the _CLIENT_ must free
   *
   * @return  A byte array of pixels
   */
  virtual unsigned char* getByteArray() const;
  
  /**
   * Set a graph to directed
   *
   * @param directed    True if directed, false otherwise
   */
  virtual void setDirected(bool directed);
  
  /**
   * Check if graph is directed
   *
   * @return  Whether graph is directed or not
   */
  virtual bool isDirected() const;

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
  Color highlight;
  Color background;
  bool directed;
};
}
#endif /* GRAPHIX_SCENE_SCENE_H__ */

