//
//  Graph.hpp
//  TestRevisionP13
//
//  Created by Laura Walsh on 06/05/2019.
//  Copyright © 2019 Laura Walsh. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>


class Graph
{
public:
    // constructor - create a graph from a file with the given name
    Graph(char* fname);
    // destructor
    ~Graph();
    // return the number of vertices
    int get_num_v() const { return num_v; }
    // return the weight between the given source & dest vertices // weight = 0.0 means no edge
    double get_edge(int source, int dest) const;
private:
    // the graph
int num_v;
bool directed;
double** edges;
};

#endif /* Graph_hpp */
