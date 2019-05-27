//
//  main.cpp
//  TestRevisionP13
//
//  Created by Laura Walsh on 06/05/2019.
//  Copyright © 2019 Laura Walsh. All rights reserved.
//

#include <iostream>
#include <set>
#include<stack>
#include <vector>
#include <queue>
#include "Graph.hpp"
using namespace std;
#define FILENAME_LEN 100

//breadth-first search, return backtrack vector
vector<int> breadth_first_search(Graph& graph, int start_vertex){
    //number of vertices of the graph
    int num_v = graph.get_num_v();
    
    //use a queue to store the vertices waiting to visit
    queue<int> queue;
    //mark vertices that have been visited
    bool* visited = new bool[num_v];
    //use a vector for backtracking all items initialised to -1
    vector<int> backtrack(num_v, -1);
    
    for(int i =0; i< num_v; i++)
        visited[i] = false;
    queue.push(start_vertex);
    visited[start_vertex] = true;
    
    while(!queue.empty()){
        //take a vertex "source" out of a queue to visit
        int source = queue.front();
        queue.pop();
        //for each destination vertex adjacent to source
        for(int dest =0; dest<num_v; dest++){
            //dest can't be adjacent to source as there is no edge
            if(graph.get_edge(source, dest) ==0.) continue;
            if(visited[dest]) continue;
            queue.push(dest);
            visited[dest] = true;
            backtrack[dest] = source;
        }
    }
    delete[] visited;
    return backtrack;
}



void dijkstras_algorithm(Graph &graph, int start_vertex, int* backtrack, double* distance){
    int num_v = graph.get_num_v();
    
    //all unprocessed vertices v except start_vertex in a set
    //with corresponding distance and parent from start_vertex to v
    set<int> v_s;
    for(int i =0; i<num_v; i++){
        if(i!= start_vertex) v_s.insert(i);
    }
    distance[start_vertex] =0.;
    for (set<int>::iterator itr = v_s.begin(); itr != v_s.end(); itr++) {
        int v = *itr;
        double w = graph.get_edge(start_vertex, v);
        distance[v] = (w > 0.) ? w : __DBL_MAX__;    // maximum positive double value
        backtrack[v] = start_vertex;
    }
    backtrack[start_vertex] = -1;
    
    // search - for all vertices v in v_s
    while (!v_s.empty()) {
        // find the vertex u in v_s with the smallest distance[u]
        double min_distance = __DBL_MAX__;
        int u = -1;
        for (set<int>::iterator itr = v_s.begin(); itr != v_s.end(); itr++) {
            int v = *itr;
            if (distance[v] < min_distance) {
                min_distance = distance[v];
                u = v;
            }
        }
        if (u < 0) break;
        
        // remove u from set v_s
        v_s.erase(u);
        
        // for all vertices v in v_s that are adjacent to u
        for (set<int>::iterator itr = v_s.begin(); itr != v_s.end(); itr++) {
            int v = *itr;
            if (graph.get_edge(u, v) != 0.0) {
                // distance from start_vertex to v via u
                double d = distance[u] + graph.get_edge(u, v);
                // compared to distance from start_vertex directly to v
                if (d < distance[v]) {
                    distance[v] = d;
                    backtrack[v] = u;
                }
            }
        }
    }
}



int main(){
    cout <<"Please enter a graoh file name: " << endl;
    char* file_name = new char[FILENAME_LEN];
    cin>> file_name;
    
    Graph graph(file_name);
    // test if the created graph is correct
    int source, dest; char yesno;
    do {
        cout << "Test if there is an edge between two vertices. \nSpecify Source Destination: ";
        cin >> source >> dest;
        
        // obtain the weight between the two vertices; weight = 0.0 means no direct edge
        double weight = graph.get_edge(source, dest);
        if (weight == 0.0)
            cout << "No edge" << endl;
        else cout << source << " "
            << dest << " "
            << weight << endl;
        
        cout << "try another? ";
        cin >> yesno;
    } while (yesno == 'y');
    
    delete[] file_name;
    
    return 0;
}
