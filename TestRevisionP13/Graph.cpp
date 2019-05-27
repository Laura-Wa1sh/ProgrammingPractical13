//
//  Graph.cpp
//  TestRevisionP13
//
//  Created by Laura Walsh on 06/05/2019.
//  Copyright © 2019 Laura Walsh. All rights reserved.
//

#include "Graph.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

Graph::Graph(char* fname){
    ifstream fin(fname);
    if(!fin){
        cout << "Can't open file: " << fname << endl;
        return;
    }
    
    fin>>num_v;
    char c;
    fin>>c;
    if(c=='d'){
        directed =true;
    }else{
        directed = false;
    }
    if(directed){
        double **edges = new double*[num_v];
        for(int i = 0; i< num_v; i++){
            edges[i] = new double[num_v];
            for(int j=0; j< num_v; j++){
                edges[i][j] = 0.;
            }
        }
    } else{
        double **edges = new double*[num_v];
        for(int i =0; i< num_v; i++){
            edges[i] = new double[i+1];
            for(int j =0; j<i+1; j++){
                edges[i][j] =0.;
            }
        }
    }
    int source, dest;
    double weight;
    while(fin>>source>>dest>>weight){
        if(!directed && dest> source)
            edges[dest][source] = weight;
        else edges[source][dest] = weight;
    }
    fin.close();
}

Graph::~Graph(){
        for(int i = 0; i<num_v; i++){ delete[] edges[i];
            delete[] edges;
        }
}

double Graph:: get_edge(int source, int dest) const{
    if(!directed && dest> source)
        return edges[dest][source];
    return edges[source][dest];
}
