/**
 * Application: AbstractGraph
 * Module: GUI
 * File: IO/XMLReader.cpp
 * Description: XML Reader implementation
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include "XMLReader.h"
#include "GraphMLHandler.h"

XMLReader::XMLReader(const QString& name, GRAPHIX::Scene& scene, AlgorithmsGlu& glu)
  : scene(scene), glu(glu)
{
  ioFile = new QFile(name);
  input  = new QXmlInputSource(ioFile);
}

XMLReader::~XMLReader()
{
  if(input != NULL)
    delete input;
  if(ioFile != NULL)
    delete ioFile;
}

bool XMLReader::parseInput()
{
  if(!ioFile->exists())
    return false;
  
  // Currently only one file format supported
  GraphMLHandler handler(scene, glu);
  
  this->setContentHandler(&handler);
  this->setErrorHandler(&handler);
  this->setLexicalHandler(&handler);
  
  return this->parse(input);
}
