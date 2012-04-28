/**
 * Application: AbstractGraph
 * Module: GUI
 * File: IO/GraphMLHandler.h
 * Description: XML handler for GraphML XML formats
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef IO_GRAPHMLHANDLER_H__
#define IO_GRAPHMLHANDLER_H__

#include <map>
#include <QXmlDefaultHandler>

// GraphiX Library
#include "graphix.h"

// Glue
#include "Glu/AlgorithmsGlu.h"

class GraphMLHandler : public QXmlDefaultHandler
{
public:
  /**
   * Constructor
   *
   * @param scene   The scene to update
   * @param glu     The glue between scene and algorithms
   */
  GraphMLHandler(GRAPHIX::Scene& scene, AlgorithmsGlu& glu);
  
  /**
   * Destructor
   */
  virtual ~GraphMLHandler();
  
  /**
   * Override of startElement
   */
  virtual bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts);
  
  /**
   * Override of endElement
   */
  virtual bool endElement(const QString& namespaceURI, const QString& localName, const QString& qName);
  
  /**
   * Characters
   */
  virtual bool characters(const QString& ch);

protected:
  /**
   * Parse key elements
   *
   * @return atts   Attributes
   * @return  True on success, false otherwise
   */
  virtual bool parseKey(const QXmlAttributes& atts);
  
  /**
   * Parse graph elements
   *
   * @param atts    Attributes
   * @return  True on success, false otherwise
   */
  virtual bool parseGraphElm(const QXmlAttributes& atts);
  
  /**
   * Parse graph nodes
   *
   * @param atts    Attributes
   * @return  True on success, false otherwise
   */
  virtual bool parseNode(const QXmlAttributes& atts);
  
  /**
   * Parse graph edges
   *
   * @param atts    Attributes
   * @return  True on success, false otherwise
   */
  virtual bool parseEdge(const QXmlAttributes& atts);
  
  /**
   * Parse data elements
   *
   * @param atts  Attributes
   * @return  True on success, false otherwise.
   */
  virtual bool parseData(const QXmlAttributes& atts);
  
  /**
   * Parse coordinates
   *
   * @param line   Line to parse
   */
  virtual void parseCoords(const QString& line);
  
  /**
   * Set the node coordinates
   */
  virtual void setNodeCoords();
  
  /**
   * Simple struct to find coordinates
   */
  struct AbsoluteCoords {
    float x;
    float y;
  };
  
private:
  GRAPHIX::Scene& scene;
  AlgorithmsGlu& glu;
  GRAPHIX::Circle* nodePtr;
  bool done;
  QString nodeId;
  QString coordKey;
  std::map<QString, int> idMap;
  std::map<GRAPHIX::Circle*, AbsoluteCoords> nodeCoords;
};

#endif /* IO_GRAPHMLHANDLER_H__ */
