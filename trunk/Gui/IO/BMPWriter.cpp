/**
 * Application: AbstractGraph
 * Module: GUI
 * File: IO/BMPWriter.cpp
 * Description: BMP writer for graphs
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#include "BMPWriter.h"

#include <QFile>

BMPWriter::BMPWriter(const QString& file, const GRAPHIX::Scene& scene)
  : scene(scene), output(file)
{
}

BMPWriter::~BMPWriter()
{
}

bool BMPWriter::write()
{
  char* bytes = scene.getByteArray();
  
  if(bytes == NULL)
    return false;
  
  if(output.exists()) {
    output.open(QIODevice::Truncate | QIODevice::WriteOnly);
  } else {
    output.open(QIODevice::WriteOnly);
    if(!output.exists()) {
      delete bytes;
      return false;
    }
  }
  
  bool result = true;
  
  result &= writeBMPHeader();
  
  delete bytes;
  
  return result;
}

bool BMPWriter::writeBMPHeader()
{
  return true; // Write BMP header
}
