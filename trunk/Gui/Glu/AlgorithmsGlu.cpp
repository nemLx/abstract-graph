/**
 * Application: AbstractGraph
 * Module: GUI
 * File: Glu/AlgorithmsGlu.cpp
 * Description: Implementation for Algorithms glue
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include <map>
#include <vector>

#include <QInputDialog>
#include <QMessageBox>

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
    case EXPORTPRUFER:
      result = algorithmExportPrufer();
      break;
    case IMPORTPRUFER:
      result = algorithmImportPrufer();
      break;
    case SCC:
      result = algorithmSCC();
      break;
    default:
      break;
  }

  if(result >= 0 && glu != IMPORTPRUFER) {
    parent->updateMode(GRAPHIX::EDIT);
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
  
  highlightNodes(setX);
  highlightNodes(setY, Color(0.0, 255.0, 0.0, 0.0));
  
  bipartiteArrange(setX, setY);
  
  return (bipartite == 0) ? -1 : 0;
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

int AlgorithmsGlu::algorithmExportPrufer()
{
  std::vector<int> code;
  std::map<int, int> map;
  
  Graph* graph = getUndirected();
  
  if(graph == NULL)
    return -2;
  
  int result = graph->getPruferCode(&code, &map);
  
  if(result != 1)
    return 0;
  
  std::map<int,int>::const_iterator it;
  
  for(it = map.begin() ; it != map.end() ; ++it) {
    QString intToStr("%1");
    intToStr = intToStr.arg("%1").arg(it->second);
    scene.updateLabel(it->first, intToStr.toStdString());
  }
  
  QString pruferCode;
  
  for(unsigned i = 0 ; i < code.size() ; ++i) {
    pruferCode.append("%1");
    pruferCode = pruferCode.arg("%1").arg(code[i]);
  }
  
  QMessageBox msg(QMessageBox::Information, "Prufer Code", pruferCode, QMessageBox::Ok, NULL);
  msg.exec();
  
  return result;
}

int AlgorithmsGlu::algorithmImportPrufer()
{
  QString prufer = QInputDialog::getText(NULL, "Prufer Code", "");
  std::vector<int> code;
  
  if(prufer.isEmpty())
    return -3;
  
  Graph* graph = getUndirected();
  
  if(graph == NULL)
    return -2;
  
  for(int i = 0 ; i < prufer.length() ; ++i) {
    const QChar x = prufer[i];
    code.push_back(x.digitValue());
  }
  
  graph->buildFromPruferCode(&code);
  
  buildSceneFromGraph();
  
  return 1;
}

int AlgorithmsGlu::algorithmSCC()
{
  std::map<int,int> map;
  DiGraph* graph = getDirected();
  
  if(graph == NULL)
    return -2;
  
  int numComps = graph->getSCs(&map);
  
  std::map<int,int>::const_iterator it;
  
  unsigned r = 255.0f;
  unsigned g = 200.0f;
  unsigned b = 150.0f;
  int count = 0;
  for(it = map.begin() ; it != map.end() ; ++it) {
    scene.updateNodeColor(it->second, r, g, b);
    r -= (count % 3) ? count : 0;
    g -= (count % 4) ? count : 0;
    b -= (count % 5) ? count : 0;
    r %= 256;
    g %= 256;
    b %= 256;
  }
  
  printf("%d\n", numComps);
  
  return numComps;
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

void AlgorithmsGlu::bipartiteArrange(const std::vector<int>& setX, const std::vector<int>& setY) const
{
  std::vector<int>::const_iterator it;
  float leftX  = -0.25f;
  float rightX = 0.25f;
  float top = .9f;
  
  unsigned count = 0;
  for(it = setX.begin() ; it != setX.end() ; ++it, count++) {
    GRAPHIX::Circle* node = static_cast<GRAPHIX::Circle*>(scene.findShape(*it));
    
    if(node == NULL)
      return;
    
    node->setX(leftX);
    node->setY(top - (count*node->getRadius()*2.5));
  }
  
  count = 0;
  for(it = setY.begin() ; it != setY.end() ; ++it, count++) {
    GRAPHIX::Circle* node = static_cast<GRAPHIX::Circle*>(scene.findShape(*it));
    
    if(node == NULL)
      return;
    
    node->setX(rightX);
    node->setY(top - (count*node->getRadius()*2.5));
  }
}

void AlgorithmsGlu::buildSceneFromGraph()
{
  if(graph == NULL)
    return;
  
  std::map<int, AbstractNode*>* nodes;
  std::map<int, AbstractEdge*>* edges;
  std::map<int, AbstractNode*>::iterator it;
  std::map<int, AbstractEdge*>::iterator itt;
  
  nodes = graph->getNodes();
  
  for(it = nodes->begin() ; it != nodes->end() ; ++it) {
    scene.addNode();
    scene.setLastId(it->first);
  }
  
  edges = graph->getEdges();
  
  for(itt = edges->begin() ; itt != edges->end() ; ++itt) {
    AbstractEdge* edge = itt->second;
    scene.addEdge(edge->getFrom()->id, edge->getTo()->id);
    scene.setLastId(itt->first);
  }
}
