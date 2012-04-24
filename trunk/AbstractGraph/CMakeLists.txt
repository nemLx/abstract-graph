# CMakeLists.txt
# Main CMakeLists.txt for AbstractGraph Library

if(WIN32)
cmake_minimum_required(VERSION 2.8.6)
ELSE(WIN32)
cmake_minimum_required(VERSION 2.6.2)
ENDIF(WIN32)
project(AbstractGraph)

# Hide things we don't need
if(APPLE)
  mark_as_advanced(CMAKE_OSX_ARCHITECTURES CMAKE_OSX_SYSROOT)
endif(APPLE)

# Basic compiler options
if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "-Wall -O0 -g")
  set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Wall -O2 -g")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "-Wall -O3")
  set(CMAKE_CXX_FLAGS_DEBUG "-Wall -O0 -g")
endif(NOT WIN32)

#Boost
#set(Boost_INCLUDE_DIR /Users/nemo/boost_1_49_0)
#set(Boost_LIBRARY_DIR /Users/nemo/boost_1_49_0/libs)
#include_directories(${Boost_INCLUDE_DIR})
#link_directories(${Boost_LIBRARY_DIR})

# Source Files
set (GRAPH_SRC
        include/incl.h include/AGRAPHLIB.h
		include/Graphs/AbstractGraph.h src/Graphs/AbstractGraph.cpp
		src/Graphs/Graph.cpp include/Graphs/Graph.h
		src/Graphs/DiGraph.cpp include/Graphs/DiGraph.h
		include/Nodes/AbstractNode.h src/Nodes/AbstractNode.cpp
		include/Nodes/Node.h src/Nodes/Node.cpp
		include/Nodes/DiNode.h src/Nodes/DiNode.cpp
		include/Edges/AbstractEdge.h src/Edges/AbstractEdge.cpp
		include/Edges/Edge.h src/Edges/Edge.cpp
		include/Edges/DiEdge.h src/Edges/DiEdge.cpp
		include/Algorithms/Algorithm.h
		include/Algorithms/Dijkstra.h src/Algorithms/Dijkstra.cpp
		include/Algorithms/Prim.h src/Algorithms/Prim.cpp
	    include/Algorithms/Bipartite.h src/Algorithms/Bipartite.cpp
        include/Algorithms/FordFulkerson.h src/Algorithms/FordFulkerson.cpp
        include/Algorithms/HopcroftKarp.h src/Algorithms/HopcroftKarp.cpp
        include/Algorithms/OddCycle.h src/Algorithms/OddCycle.cpp
        include/Algorithms/EulerianPath.h src/Algorithms/EulerianPath.cpp
        include/Algorithms/Bridge.h src/Algorithms/Bridge.cpp
        include/Algorithms/PruferCode.h src/Algorithms/PruferCode.cpp
        include/Algorithms/Gabow.h src/Algorithms/Gabow.cpp
        include/Algorithms/FloydWarshall.h src/Algorithms/FloydWarshall.cpp
        include/Algorithms/GraphicSequence.h src/Algorithms/GraphicSequence.cpp
        )
	

# Main Binary
add_library(${PROJECT_NAME} SHARED ${GRAPH_SRC})

add_executable(${PROJECT_NAME}_test ${GRAPH_SRC} graphTest.cpp)

