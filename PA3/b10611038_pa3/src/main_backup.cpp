#include <iostream>

#include <cstring>
#include <fstream>
#include <vector>

using namespace std;


// #include "maxPlanarSubset.h"
// #include "maxPlanarSubset.cpp"

// #include "sort_tool.h"
// #include "sort_tool.cpp" //如果沒有用makefile, 分開寫記得兩個都要include!

/*
1. think minimum spanning tree, 但是cost不是要minimum總和的edge, cost 是要maximum tree cost 所以所有edge weight - tree cost = 要remove的edge weight 會最少. 
2. 因為MST會是v-1個edge, V個edge就會有cycle
3. MST法只能用在undirect graph, 因為directgraph的no cycle, 不一定就是MST因為edge 有direction
4. Dense Graph --> 用 Prim's Algorithms
*/

// Undirect graph Construction Class
#include <iostream>
#include <vector>
using namespace std;
#include <iostream>
#include <list>
#include <map>
using namespace std;


// [Reference] adjaceny list graph construction: https://www.geeksforgeeks.org/implementation-of-graph-in-cpp/
class Graph {
private: 
    map<int, list<pair<int, int>> > adjList; // Adjacency list to store the graph
    int n, m; //number of vertics, edge

    // Union-Find data members
    // map<int, int> parent;  // Stores the parent of each vertex
    // map<int, int> rank;    // Stores the rank (size) of each set
public:

    // Function to add an edge between vertices u and v of
    // the graph

    Graph (int n, int m){
        n=n;
        m=m;
    }
    void add_edge(int u, int v, int weight)
    {
        // Add edge from u to v
        adjList[u].push_back({v,weight});
        // Add edge from v to u because the graph is
        // undirected
        adjList[v].push_back({u,weight});

        
        // // disjoint set
        // if (parent.find(u) == parent.end()) {
        //     parent[u] = u;
        //     rank[u] = 0;
        // }
        // if (parent.find(v) == parent.end()) {
        //     parent[v] = v;
        //     rank[v] = 0;
        // }
    }

    void add_edge_direct(int u, int v, int weight)
    {
        // Add edge from u to v
        adjList[u].push_back({v,weight});
        // Add edge from v to u because the graph is
        // undirected
        // adjList[v].push_back(u);

        //disjoint set
        // if (parent.find(u) == parent.end()) {
        //     parent[u] = u;
        //     rank[u] = 0;
        // }
    }

    // Function to print the adjacency list representation
    // of the graph
    void print()
    {
        cout << "Adjacency list for the Graph: " << endl;
        // Iterate over each vertex
        for (auto i : adjList) {
            // Print the vertex
            cout << i.first << " -> ";
            // Iterate over the connected vertices
            for (auto j : i.second) {
                // Print the connected vertex
                cout << "(" << j.first << ", " << j.second << ") ";
            }
            cout << endl;
        }
    }



   
    // Prim's MST Algorithm
    void prim_mst(int start) {
        for(int u=0; u<n; u++){  //跑過所有vertics
            //找出被連接到的edge的最min的edege
            extract_min()


        }
    }
    

    // // disjoint set
    // // Union-Find: Find the representative of the set containing u
    // int find(int u)
    // {
    //     if (parent[u] != u) {
    //         parent[u] = find(parent[u]);  // Path compression
    //     }
    //     return parent[u];
    // }

    // // Union-Find: Union of two sets containing u and v
    // void union_sets(int u, int v)
    // {
    //     int root_u = find(u);
    //     int root_v = find(v);

    //     if (root_u != root_v) {
    //         // Union by rank: attach the smaller tree under the root of the larger tree
    //         if (rank[root_u] > rank[root_v]) {
    //             parent[root_v] = root_u;
    //         } else if (rank[root_u] < rank[root_v]) {
    //             parent[root_u] = root_v;
    //         } else {
    //             parent[root_v] = root_u;
    //             rank[root_u]++; // Increment rank if both trees have the same rank
    //         }
    //     }
    // }

    // // Function to check if two vertices are in the same connected component
    // bool are_connected(int u, int v)
    // {
    //     return find(u) == find(v);
    // }



};

// class PrimMST {
// private:     
//     // map<int, list<int> > adjList; // Adjacency list to store the graph
//     // map<int, list<pair<int, int>>> adjList;
//     map<int, list<int> > adjList; // Adjacency list to store the graph
//     // Priority queue for edges (min-heap based on weight)
//     map<int, int> key; // Min weight to connect each node
//         map<int, int> parent; // Parent of each node in the MST
//         map<int, bool> inMST; // Tracks if a node is included in MST

//         // Priority queue for edges (min-heap based on weight)
//         priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

//     int n,m;
// public:
//     // Function to add an edge between vertices u and v of
//     // the graph
//     PrimMST(Graph &G, int n, int m) {
//         adjList = G.adjList;
//         n=n;
//         m=m;

//     }

//     // MST_prim(){
//     //     for (int u=){

//     //     }

//     // }

//     void add_edge_direct(int u, int v)
//     {
//         // Add edge from u to v
//         adjList[u].push_back(v);
//         // Add edge from v to u because the graph is
//         // undirected
//         // adjList[v].push_back(u);
//     }

//     // Function to print the adjacency list representation
//     // of the graph
//     void print()
//     {
//         cout << "Adjacency list for the Graph: " << endl;
//         // Iterate over each vertex
//         for (auto i : adjList) {
//             // Print the vertex
//             cout << i.first << " -> ";
//             // Iterate over the connected vertices
//             for (auto j : i.second) {
//                 // Print the connected vertex
//                 cout << j << " ";
//             }
//             cout << endl;
//         }
//     }
// };






int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return 1;
    }

    ////cout<<"lala"<< endl;
    //////////// read the input file /////////////
    //This creates an fstream object and then opens the file in output mode.
    //ofstream: ofstream is specifically designed for output (writing) only. It simplifies the interface if you only need to write to the file, as it doesn’t support reading operations.
    //fstream: fstream is a more general file stream class that supports both input (ios::in) and output (ios::out) operations.

    string graphType;
    int n, m;
    ////cout<<"ok1"<< endl;
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    fin>> graphType; //input file 1st行: graphType
    fin>> n; //input file 2nd行: number of vertixs
    fin>> m; //input file 3rd行: edge number


    int u,v,w;
    // vector<int> data_a, data_b; //紀錄個chord中兩端點

    // int chords[2*n]; //建立pair array, 之後會索引紀錄chord(為chord[i] = 0~2n-1個端點各自chord的另一端) 
    // std::vector<int> chords(2*n);  //先給各個vector一個已知的空間, 之後才可以確定chords[a]=b不會出錯

    Graph g; 
    cout << "(n,m) = ("<<n<<", "<<m<<")"<<endl;

    while (fin >> u >> v>> w){ //讀個line的前兩個element，第一個捨棄到junk中, 把第二個存到data中
        
        // cout << "add edge (u,v) = ("<<u<<", "<<v<<")"<<endl;
        if(graphType=="u"){
            g.add_edge(u, v, w);
        }else{
            g.add_edge_direct(u, v, w);
        }

    }
    g.print();

    // ///////////////Maximum Planner Part////////////////
    // MaxPlanarSubset mps(n, chords);
    // //cout<<"ok6"<< endl;
    // mps.maximumPlanarSubset();
    // //cout<<"ok7"<< endl;
    // std::vector<std::vector<int>>result = mps.get_maximumPlanarSubset_chord();
    // ////cout<<"ok100"<< endl;


    // ////////////Sorting the result base on the first element////////////////
    // SortTool NTUSortTool;
    // NTUSortTool.QuickSort_for2Don1stElement(result);
    // //////////// write the output file ///////////
    // fout << result.size() <<endl;
    // for (int i = 0; i < result.size(); i++){
    //     ////cout<<"result[i][0] = "<<result[i][0]<<"result[i][1] = "<<result[i][1]<< endl;
    //     fout << result[i][0] << " " <<result[i][1] << endl;       
    // }



    fin.close();
    fout.close();
    // // Number of vertices
    // // int n = 4;
    // // Create a graph with 4 vertices
    // Graph g;

    // // Adding the specified edges in the graph
    // g.add_edge(1, 0);
    // g.add_edge(2, 0);
    // g.add_edge(1, 2);

    // // Print the adjacency matrix representation of the
    // // graph
    // g.print();
    return 0;
}


