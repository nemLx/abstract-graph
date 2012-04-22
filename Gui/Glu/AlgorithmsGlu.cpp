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
  GRAPHIX::Circle* to = NULL, *from = NULL;
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
        to   = line->getTo();
        from = line->getFrom();

        id = addEdge(from->getId(), to->getId());

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
      result = algorithmMST();
      break;
    case MAXMATCH:
      result = algorithmMaxMatch();
      break;
    case MAXNET:
      result = algorithmMaxNet();
      break;
    case BIPARTITESETS:
      result = algorithmBipartite();
      break;
    case ODDCYLCE:
      result = algorithmOddCycle();
      break;
    case EULER:
      result = algorithmEulerCircuit();
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
  Color color(255.0, 0.0, 0.0, 0.0);
  
  std::vector<int> selected = scene.getSelectedIds(GRAPHIX::CIRCLE);
  
  if(selected.size() != 2)
    return -2;
  
  int start = selected[0];
  int end   = selected[1];
  int weight = graph->shortestPath(start, end, &path);
  
  highlightPath(path);
  
  return weight;
}

int AlgorithmsGlu::algorithmMST()
{
  std::vector<int> path;
  
  Graph* ugraph = getUndirected();
  
  // Only works on undirected
  if(ugraph == NULL)
    return -2;
  
  int weight = ugraph->mst(&path);
  
  highlightPath(path);
  
  return weight;
}

int AlgorithmsGlu::algorithmMaxMatch()
{
  std::vector<int> edges;
  
  // Only works on undirected
  Graph* ugraph = getUndirected();
  
  if(ugraph == NULL)
    return -2;
  
  int weight = ugraph->maxMatching(&edges);
  
  highlightPath(edges);
  
  return weight;
}

int AlgorithmsGlu::algorithmMaxNet()
{
  std::vector<int> cutEdges;
  std::vector<std::pair<int,int> > edgeFlow;
  
  DiGraph* dgraph = getDirected();
  
  if(dgraph == NULL)
    return -2;
  
  std::vector<int> selected = scene.getSelectedIds(GRAPHIX::CIRCLE);
  
  if(selected.size() != 2)
    return -3;
  
  int start = selected[0];
  int end   = selected[1];
  int flow = dgraph->maxFlowMinCut(start, end, &edgeFlow, &cutEdges);
  
  highlightNodes(cutEdges);
  
  // Update labels to: flow / capacity
  printf("Flow: %d\n", flow);
  
  return flow;
}

int AlgorithmsGlu::algorithmBipartite()
{
  std::vector<int> setX;
  std::vector<int> setY;
  
  Graph* ugraph = getUndirected();
  
  if(ugraph == NULL)
    return -2;
  
  int bipartite = ugraph->bipartite(&setX, &setY);
  
  // TODO: Modify node structure (i.e. make it looks bipartite)
  highlightNodes(setX);
  highlightNodes(setY, Color(0.0, 255.0, 0.0, 0.0));
  
  return bipartite;
}

int AlgorithmsGlu::algorithmOddCycle()
{
  std::vector<int> cycle;
  
  Graph* ugraph = getUndirected();
  
  if(ugraph == NULL)
    return -2;
  
  int length = ugraph->getOddCycle(&cycle);
  
  highlightPath(cycle);
  
  return length;
}

int AlgorithmsGlu::algorithmEulerCircuit()
{
  std::vector<int> circuit;
  
  Graph* ugraph = getUndirected();
  
  if(ugraph == NULL)
    return -2;
  
  std::vector<int> selected = scene.getSelectedIds(GRAPHIX::CIRCLE);
  
  if(selected.size() > 2 || selected. size() < 1)
    return -3;
  
  int start = selected[0];
  int end   = (selected.size() == 2) ? selected[1] : selected[0];
  int ret = ugraph->eulerianPath(start, end, &circuit);
  
  std::vector<int>::iterator it;
  
  int i = 0;
  for(it = circuit.begin() ; it != circuit.end() ; ++it) {
    GRAPHIX::Line* line = static_cast<GRAPHIX::Line*>(scene.findShape(*it, GRAPHIX::LINE));
    
    if(line == NULL)
      continue;
    
    printf("Edge: %d, i: %d\n", *it, i);
    
    line->updateWeight(i);
    i++;
  }
  
  if(ret != 0)
    parent->showWeights(true);
  return ret;
}

void AlgorithmsGlu::highlightPath(const std::vector<int>& path, Color color)
{
  std::vector<int>::const_iterator it;
  
  for(it = path.begin() ; it != path.end() ; ++it) {
    GRAPHIX::Shape* shape = scene.findShape(*it, GRAPHIX::LINE);
    GRAPHIX::Line* edge = static_cast<GRAPHIX::Line*>(shape);
    
    if(edge != NULL)
      edge->setColor(color);
  }

  scene.deselectAll();
  parent->updateGL();
}

void AlgorithmsGlu::highlightNodes(const std::vector<int>& nodes, Color color)
{
  std::vector<int>::const_iterator it;
  
  for(it = nodes.begin() ; it != nodes.end() ; ++it) {
    GRAPHIX::Shape* shape = scene.findShape(*it, GRAPHIX::CIRCLE);
    GRAPHIX::Circle* node = static_cast<GRAPHIX::Circle*>(shape);
    
    if(node != NULL)
      node->setColor(color);
  }
  
  scene.deselectAll();
  parent->updateGL();
}

Graph* AlgorithmsGlu::getUndirected() const
{
  if(scene.isDirected())
    return NULL;
  return static_cast<Graph*>(graph);
}

DiGraph* AlgorithmsGlu::getDirected() const
{
  if(!scene.isDirected())
    return NULL;
  return static_cast<DiGraph*>(graph);
}
