/**
 * Application: AbstractGraph
 * Module: GUI
 * File: Glu/AlgorithmsGlu.cpp
 * Description: Implementation for Algorithms glue
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include "AlgorithmsGlu.h"

#include "Windows/GLWindow.h"

AlgorithmsGlu::AlgorithmsGlu(GRAPHIX::Scene& scene, GLWindow* parent, bool directed)
  : scene(scene), parent(parent)
{
  if(directed)
    graph = new DiGraph;
  else
    graph = new Graph;
}

AlgorithmsGlu::~AlgorithmsGlu()
{
  if(graph != NULL)
    delete graph;
}

void AlgorithmsGlu::handleAction(GRAPHIX::ACTION action)
{
  // ADDNODE & ADDEDGE
  // are currently the two actions to be handled
  int id = -1;
  switch(action)
  {
    case GRAPHIX::ADDNODE:
      id = addNode();
      scene.setLastId(id);
      break;
    case GRAPHIX::ADDEDGE:
      break;
    default:
      break;
  }
}

int AlgorithmsGlu::addNode()
{
  return graph->addNode();
}

int AlgorithmsGlu::addEdge(int n1, int n2, int weight)
{
  return graph->addEdge(n1, n2, weight);
}

void AlgorithmsGlu::runAlgorithm(AlgorithmsGlu::ALGORITHM glu)
{
  parent->updateMode(GRAPHIX::VIEWONLY);
  parent->lock(true);
  
  // Then update the scene graph to look appropriately
}
