/**
 * Application: AbstractGraph
 * Module: GUI
 * File: IO/XMLReader.h
 * Description: XML Reader interface
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef IO_XMLREADER_H__
#define IO_XMLREADER_H__

#include <QXmlSimpleReader>

// GraphiX Library
#include "graphix.h"

// Glue
#include "Glu/AlgorithmsGlu.h"

class XMLReader : public QXmlSimpleReader
{
public:
  /**
   * Constructor
   *
   * @param input   Input file name
   * @param scene   The scene to update
   * @param glu     The glue between scene and algorithms
   */
  XMLReader(const QString& input, GRAPHIX::Scene& scene, AlgorithmsGlu& glu);
  
  /**
   * Destructor
   */
  virtual ~XMLReader();
  
  /**
   * Parse input
   *
   * @return  True if parsed successfully, false otherwise
   */
  virtual bool parseInput();
  
private:
  QXmlInputSource* input;
  QFile* ioFile;
  GRAPHIX::Scene& scene;
  AlgorithmsGlu& glu;
};

#endif /* IO_XMLREADER_H__ */
