/**
 * Application: AbstractGraph
 * Module: GUI
 * File: IO/GraphMLWriter.cpp
 * Description: XML writer to GraphML format
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef IO_GRAPHMLWRITER_H__
#define IO_GRAPHMLWRITER_H__

#include <QXmlStreamWriter>

// GraphiX Library
#include "graphix.h"

class QFile;

class GraphMLWriter
{
public:
  /**
   * Constructor
   *
   * @parma name    Output file name
   * @param scene   Reference to scene object
   */
  GraphMLWriter(const QString& name, const GRAPHIX::Scene& scene);
  
  /**
   * Destructor
   */
  virtual ~GraphMLWriter();
  
  /**
   * Write the output file
   *
   * @return  True if write successful, false otherwise
   */
  virtual bool write();
  
private:
  /**
   * Write the nodes to output file
   *
   * @return  True if successful, false otherwise
   */
  virtual bool writeNodes();
  
  /**
   * Write the edges to output file
   *
   * @return  True if successful, false otherwise
   */
  virtual bool writeEdges();
  
  const GRAPHIX::Scene& scene;
  QFile* input;
  QXmlStreamWriter writer;
};

#endif /* IO_GRAPHMLWRITER_H__ */
