/**
 * Application: GraphiX Library
 * Module: Library
 * File: graphix_incl.h
 * Description: Standard includes for the GraphiX library
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id$
 */

#ifndef GRAPHIX_INCL_HEADER_H__
#define GRAPHIX_INCL_HEADER_H__

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
  #ifdef _WIN32
    #include <Windows.h>
  #endif
#include <GL/gl.h>
#include <GL/glu.h>
#endif

// For DLL Exporting on Win32 Systems
#if _WIN32
#ifndef GRAPHIX_PROD
#define GRAPHIX_EXPORT __declspec(dllexport)
#else
#define GRAPHIX_EXPORT __declspec(dllimport)
#endif
#else
#define GRAPHIX_EXPORT
#endif

#endif /* GRAPHIX_INCL_HEADER_H__ */

