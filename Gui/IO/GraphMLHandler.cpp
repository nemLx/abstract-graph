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
#include <cmath>

GraphMLHandler::GraphMLHandler(GRAPHIX::Scene& scene, AlgorithmsGlu& glu)
  : scene(scene), glu(glu), nodePtr(NULL), done(false), nodeId(""), coordKey(""), hasData(true)
{
}

GraphMLHandler::~GraphMLHandler()
{
}

bool GraphMLHandler::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts)
{
  if(done)
    return true;
  
  if(!localName.compare("key"))
    return parseKey(atts);
  else if(!localName.compare("graph"))
    return parseGraphElm(atts);
  else if(!localName.compare("node"))
    return parseNode(atts);
  else if(!localName.compare("edge"))
    return parseEdge(atts);
  else if(!localName.compare("data"))
    return parseData(atts);
  
  return true;
}

bool GraphMLHandler::characters(const QString& ch)
{
  // Assuming only proper data
  if(ch.trimmed().isEmpty())
    return true;
  parseCoords(ch);
  return true;
}

bool GraphMLHandler::parseKey(const QXmlAttributes& atts)
{
  QString id(atts.value("id"));
  QString attrName(atts.value("attr.name"));
  
  if(!attrName.compare("VectorCoordinates"))
    return true;
  
  coordKey = id;
  
  return true;
}

bool GraphMLHandler::endElement(const QString& namespaceURI, const QString& localName, const QString& qName)
{
  // Only read a single graph (if multiple graphs included)
  if(!localName.compare("graph")) {
    done = true;
    setNodeCoords();
  }
  if(!localName.compare("node"))
    nodeId.clear();
  return true;
}

bool GraphMLHandler::parseGraphElm(const QXmlAttributes& atts)
{
  QString edgetype(atts.value("edgedefault"));
  
  if(edgetype.isEmpty())
    return false;
  
  if(!edgetype.compare("directed")) {
    scene.setDirected(true);
  }
  
  return true;
}

bool GraphMLHandler::parseNode(const QXmlAttributes& atts)
{
  // Perhaps use this as label later?
  nodeId = atts.value("id");
  
  if(nodeId.isEmpty())
    return false;
  
  // Add this node appropriately
  int id = glu.addNode();
  scene.addNode();
  scene.setLastId(id);
  
  // Store the node xml id to internal id conversions
  idMap[nodeId] = id;
  
  return true;
}

bool GraphMLHandler::parseEdge(const QXmlAttributes& atts)
{
  QString from(atts.value("source"));
  QString to(atts.value("target"));
  
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

bool GraphMLHandler::parseData(const QXmlAttributes& atts)
{
  // Not the right key
  if(atts.value("key").compare(coordKey))
    return true;
  
  // Key is in the wrong spot
  if(nodeId.isEmpty())
    return false;
  
  int id = idMap[nodeId];
  
  nodePtr = static_cast<GRAPHIX::Circle*>(scene.findShape(id, GRAPHIX::CIRCLE));

  if(nodePtr == NULL)
    return false;
  
  return true;
}

void GraphMLHandler::parseCoords(const QString& line)
{
  if(nodePtr == NULL)
    return;

  AbsoluteCoords coords;
  QStringList split = line.split("[");
  split = split[1].split(",");
  
  QStringList remSep  = split[0].split("`");
  QStringList remSep2 = split[1].split("`");
  QString xStr = remSep[0];
  QString yStr = remSep2[0];
  
  coords.x = xStr.toFloat();
  coords.y = yStr.toFloat();
  
  nodeCoords[nodePtr] = coords;
  
  if(!hasData) {
    hasData = true;
    minX = maxX = coords.x;
    minY = maxY = coords.y;
  } else {
    if(coords.x < minX)
      minX = coords.x;
    else if(coords.x > maxX)
      maxX = coords.x;
    
    if(coords.y < minY)
      minY = coords.y;
    else if(coords.y > maxY)
      maxY = coords.y;
  }
  
  nodePtr = NULL;
}

// Math by Nemo
void GraphMLHandler::setNodeCoords()
{
  std::map<GRAPHIX::Circle*, AbsoluteCoords>::iterator it;
  float scale = .9f;
  
  if (minX < 0)
    maxX += abs(minX);
  else
    maxX -= abs(minX);
  
  if (minY < 0)
    maxY += abs(minY);
  else
    maxY -= abs(minY);
  
  for(it = nodeCoords.begin() ; it != nodeCoords.end() ; it++) {
    if (minX < 0)
      it->second.x += abs(minX);
    else
      it->second.x -= abs(minX);
    
    if (minY < 0)
      it->second.y += abs(minY);
    else
      it->second.y -= abs(minY);
    
    float x = (((2*scale)*it->second.x)/maxX) - scale;
    float y = (((2*scale)*it->second.y)/maxY) - scale;

    
    it->first->setX(x);
    it->first->setY(y);
  }
}

