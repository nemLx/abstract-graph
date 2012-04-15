/**
 * Application: AbstractGraph
 * Module: GUI
 * File: Glu/AlgorithmsGlu.cpp
 * Description: Implementation for Algorithms glue
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include <vector>

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
  GRAPHIX::Shape* last = NULL;
  GRAPHIX::Line* line = NULL;
  GRAPHIX::Circle* left = NULL, *right = NULL;
  switch(action)
  {
    case GRAPHIX::ADDNODE:
      id = addNode();
      scene.setLastId(id);
      break;
    case GRAPHIX::ADDEDGE:
      last = scene.getLast();
      if(last->getType() == GRAPHIX::LINE) {
        line  = static_cast<GRAPHIX::Line*>(last);
        left  = line->getLeft();
        right = line->getRight();

        id = addEdge(left->getId(), right->getId());

        scene.setLastId(id);
      }
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

void AlgorithmsGlu::updateEdgeWeight(int weight)
{
  std::vector<int> ids = scene.getSelectedIds(GRAPHIX::LINE);
  std::vector<int>::iterator it;
  
  for(it = ids.begin() ; it != ids.end() ; ++it)
    graph->setEdgeValue(*it, weight);
}

void AlgorithmsGlu::removeSelected()
{
  std::vector<int> edgeIds = scene.getSelectedIds(GRAPHIX::LINE);
  std::vector<int> nodeIds = scene.getSelectedIds(GRAPHIX::CIRCLE);
  std::vector<int>::iterator it;
  
  // TODO: Does AbstractGraph library not remove associated
  // edges when a node is removed?
  for(it = edgeIds.begin() ; it != edgeIds.end() ; ++it)
    graph->removeEdge(*it);
  for(it = nodeIds.begin() ; it != nodeIds.end() ; ++it)
    graph->removeNode(*it);
}

int AlgorithmsGlu::runAlgorithm(ALGORITHMS glu)
{  
  int result = 0;
  
  switch(glu)
  {
    case SHORTESTPATH:
      result = algorithmShortestPath();
      break;
    case MST:
      break;
    default:
      break;
  }
  
  if(result >= 0) {
    parent->updateMode(GRAPHIX::VIEWONLY);
    parent->lock(true);
  }
  
  return result;
}

int AlgorithmsGlu::algorithmShortestPath()
{
  std::vector<int> path;
  Color color(0.0, 255.0, 255.0, 0.0);
  
  std::vector<int> selected = scene.getSelectedIds(GRAPHIX::CIRCLE);
  
  if(selected.size() != 2)
    return -2;
  
  int start = selected[0];
  int end   = selected[1];
  int weight = graph->shortestPath(start, end, &path);
  
  std::vector<int>::const_iterator it;
  
  for(it = path.begin() ; it != path.end() ; ++it) {
    GRAPHIX::Shape* shape = scene.findShape(*it, GRAPHIX::LINE);
    GRAPHIX::Line* edge = static_cast<GRAPHIX::Line*>(shape);
    
    if(edge != NULL)
      edge->setColor(color);
  }
  
  scene.deselectAll();
  
  return weight;
}
