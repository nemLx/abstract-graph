/**
 * Application: AbstractGraph
 * Module: GUI
 * File: IO/BMPWriter.h
 * Description: BMP writer for graphs
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef IO_BMPWRITER_H__
#define IO_BMPWRITER_H__

#include <QFile>

// GraphiX library
#include "graphix.h"

class QString;

/**
 * Simple BMP writer class
 * with static methods
 */
class BMPWriter
{
public:
  /**
   * Constructor
   *
   * @param file    Output file name
   * @param scene   Scene object to export
   */
  BMPWriter(const QString& file, const GRAPHIX::Scene& scene);
  
  /**
   * Destructor
   */
  virtual ~BMPWriter();
  
  /**
   * Write output
   *
   * @return  True if write successful, false otherwise.
   */
  bool write();
  
private:
  /**
   * Write the BMP header
   *
   * @return  True if successful, false otherwise
   */
  bool writeBMPHeader();
  
  const GRAPHIX::Scene& scene;
  QFile output;
};

#endif /* IO_BMPWRITER_H__ */
