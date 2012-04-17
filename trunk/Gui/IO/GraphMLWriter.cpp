/**
 * Application: AbstractGraph
 * Module: GUI
 * File: IO/GraphMLWriter.cpp
 * Description: XML writer to GraphML format
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include "GraphMLWriter.h"

#include <QFile>

GraphMLWriter::GraphMLWriter(const QString& name, const GRAPHIX::Scene& scene)
  : scene(scene)
{
  input = new QFile(name);
  writer.setAutoFormatting(true);
}

GraphMLWriter::~GraphMLWriter()
{
  if(input != NULL)
    delete input;
}

bool GraphMLWriter::write()
{
  if(!input->exists()) {
    // Try to create
    input->open(QIODevice::WriteOnly);
    if(!input->exists())
      return false;
  } else {
    input->open(QIODevice::Truncate | QIODevice::WriteOnly);
  }
  
  bool success = true;
  
  writer.setDevice(input);
  
  writer.writeStartDocument("1.0");
  writer.writeStartElement("graphml");
  writer.writeAttribute("xmlns", "http://graphml.graphdrawing.org/xmlns");
  writer.writeAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
  writer.writeAttribute("xsi:schemaLocation", "http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd");
  
  writer.writeStartElement("graph");
  writer.writeAttribute("id", "G");
  writer.writeAttribute("edgedefault", "undirected"); // TODO: Support directed
  
  success &= writeNodes();
  success &= writeEdges();
  
  writer.writeEndElement();
  writer.writeEndElement();
  writer.writeEndDocument();
  
  return success;
}

bool GraphMLWriter::writeNodes()
{
  std::vector<GRAPHIX::Shape*> shapes = scene.getShapes(GRAPHIX::CIRCLE);
  std::vector<GRAPHIX::Shape*>::iterator it;

  for(it = shapes.begin() ; it != shapes.end() ; ++it) {
    QString id = QString("n%1").arg("%1").arg((*it)->getId());
    
    writer.writeStartElement("node");
    writer.writeAttribute("id", id);
    writer.writeEndElement();
  }

  return !writer.hasError();
}

bool GraphMLWriter::writeEdges()
{
  std::vector<GRAPHIX::Shape*> shapes = scene.getShapes(GRAPHIX::LINE);
  std::vector<GRAPHIX::Shape*>::iterator it;
  
  for(it = shapes.begin() ; it != shapes.end() ; ++it) {
    GRAPHIX::Line* line = static_cast<GRAPHIX::Line*>(*it);
    GRAPHIX::Circle* source = line->getLeft();
    GRAPHIX::Circle* target = line->getRight();
    
    QString sourceId = QString("n%1").arg("%1").arg(source->getId());
    QString targetId = QString("n%1").arg("%1").arg(target->getId());
    
    writer.writeStartElement("edge");
    writer.writeAttribute("source", sourceId);
    writer.writeAttribute("target", targetId);
    writer.writeEndElement();
  }
  
  return !writer.hasError();
}
