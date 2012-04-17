/**
 * Application: AbstractGraph
 * Module: GUI
 * File: IO/GraphMLHandler.cpp
 * Description: XML handler for GraphML XML formats
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include "GraphMLHandler.h"

GraphMLHandler::GraphMLHandler(GRAPHIX::Scene& scene, AlgorithmsGlu& glu)
  : scene(scene), glu(glu), done(false)
{
}

GraphMLHandler::~GraphMLHandler()
{
}

bool GraphMLHandler::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts)
{
  if(done)
    return true;
  
  if(!localName.compare("graph"))
    return parseGraphElm(atts);
  else if(!localName.compare("node"))
    return parseNode(atts);
  else if(!localName.compare("edge"))
    return parseEdge(atts);
  
  return true;
}

bool GraphMLHandler::endElement(const QString& namespaceURI, const QString& localName, const QString& qName)
{
  // Only read a single graph (if multiple graphs included)
  if(!localName.compare("graph"))
    done = true;
  return true;
}

bool GraphMLHandler::parseGraphElm(const QXmlAttributes& atts)
{
  QString edgetype = atts.value("edgedefault");
  
  if(edgetype.isEmpty())
    return false;
  
  // TODO: Allow variable graph types (i.e. directed vs. undirected) -- this should be set with edgetype value
  
  return true;
}

bool GraphMLHandler::parseNode(const QXmlAttributes& atts)
{
  // Perhaps use this as label later?
  QString idStr = atts.value("id");
  
  if(idStr.isEmpty())
    return false;
  
  // Add this node appropriately
  int id = glu.addNode();
  scene.addNode();
  scene.setLastId(id);
  
  // Store the node xml id to internal id conversions
  idMap[idStr] = id;
  
  return true;
}

bool GraphMLHandler::parseEdge(const QXmlAttributes& atts)
{
  QString from = atts.value("source");
  QString to   = atts.value("target");
  
  if(from.isEmpty() || to.isEmpty())
    return false;
  
  std::map<QString, int>::iterator fromIt, toIt;
  fromIt = idMap.find(from);
  toIt   = idMap.find(to);
  
  // Make sure id's exist
  if(fromIt == idMap.end() || toIt == idMap.end())
    return false;
  
  int fromId = fromIt->second;
  int toId   = toIt->second;
  
  int edgeId = glu.addEdge(fromId, toId);
  scene.addEdge(fromId, toId);
  scene.setLastId(edgeId);
  
  return true;
}

