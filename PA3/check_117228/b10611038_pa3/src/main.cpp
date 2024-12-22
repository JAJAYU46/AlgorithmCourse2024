// C++ code
#include <iostream>
using namespace std;

#include <vector>
#include <iomanip>      // for setw()




#include <cstring>
#include <fstream>
#include <vector>

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_set>


#include <map>


#include <climits>


const int Max_Weight = 1000;    // 初始化key[]時需要infinity, 以Max_Weight代替
const int Min_Weight = -100;    // 初始化key[]時需要infinity, 以Max_Weight代替





// 改成maximum spanning tree(每次都選擇最長邊收錄）

// [Reference] Initial Code Source -- MST implementation by adjacency matrix: http://alrightchiu.github.io/SecondRound/minimum-spanning-treeprims-algorithm.html 
// ============================================================================================================
class GraphMST{
    private:
        int num_vertex;
        std::vector<std::vector<int>> AdjMatrix;
        std::vector<std::vector<bool>> AdjMatrix_isMST;


        std::vector<std::vector<int>> result; //uint16_t
        
    public:
        // std::vector<std::vector<int>> AdjMatrix;
        // std::vector<std::vector<bool>> AdjMatrix_isMST;
        int totalWeight=0;
        int deletedTotal_weight=0;
        GraphMST():num_vertex(0){};
        GraphMST(int n):num_vertex(n){
            AdjMatrix.resize(num_vertex);
            AdjMatrix_isMST.resize(num_vertex);
            for (int i = 0; i < num_vertex; i++) {
                AdjMatrix[i].resize(num_vertex, 0);
                AdjMatrix_isMST[i].resize(num_vertex, false); //<Debug> Initialize the matrix into false
            }
        }
        void AddEdge(int from, int to, int weight);
        void AddEdgeDirect(int from, int to, int weight);

        void PrimMST(int Start = 0);        // 可以指定起點Start, 若沒有指定, 則從vertex(0)作為MST的root
        void PrimMST_maxSpanTree(int Start = 0);
        friend int MinKeyExtract(int *key, bool *visited, int size);
        friend int MaxKeyExtract(int *key, bool *visited, int size);

        std::vector<std::vector<int>> getDeletedEdgeBy_maxSpanTree();

        std::vector<std::vector<int>> maximumPlanarSubset_chord; //for output

};

// change to maximum spanning tree
int MaxKeyExtract(int *key, bool *visited, int size){

    int max = Min_Weight, max_idx = 0;
    for (int i = 0; i < size; i++) {
        if (visited[i]==false && key[i]>max) {
            max = key[i];
            max_idx = i;
        }
    }
    return max_idx;
}


int MinKeyExtract(int *key, bool *visited, int size){

    int min = Max_Weight, min_idx = 0;
    for (int i = 0; i < size; i++) {
        if (visited[i]==false && key[i]<min) {
            min = key[i];
            min_idx = i;
        }
    }
    return min_idx;
}
void GraphMST::PrimMST(int Start){

    int key[num_vertex], predecessor[num_vertex];
    bool visited[num_vertex];
    // int totalWeight=0;

    for (int i = 0; i < num_vertex; i++) {
        key[i] = Max_Weight;
        predecessor[i] = -1;
        visited[i] = false;     // false表示vertex還沒有被visited
    }

    key[Start] = 0;
    for (int i = 0; i < num_vertex; i++) { //從u1開始長tree
        int u = MinKeyExtract(key, visited, num_vertex); //被指到的是u 即習慣的v
        int u1=predecessor[u];
        totalWeight=totalWeight+AdjMatrix[u][u1]; //(i-1)指到u
        
        if(u1>=0){ //<Debug> 就是防前一個點是-1 不然會出現double free or corruption (out) Aborted (core dumped)

            AdjMatrix_isMST[u][u1]=true; //被收錄的edge就變成true
        }
        cout<<"now picked edge: (v1, v2) = (" << u  << ", "<< predecessor[u] <<") weight: "<<AdjMatrix[u][predecessor[u]]<<"   total weight: "<< totalWeight<< endl;
        visited[u] = true;
        for (int i = 0; i < num_vertex; i++) { //找遍每個點, 看
            if ( visited[i]==false && AdjMatrix[u][i]!=0 && AdjMatrix[u][i]<key[i]) {
                predecessor[i] = u;
                key[i] = AdjMatrix[u][i];
                
                std::cout << std::setw(3) << "Now: (v1, v2) = (" << u  << ", "<< i <<")\n";
                cout<<"key[i]: "<< key[i]<< endl;
            }
        }
    }
    // print MST, 與MST演算法主體無關
    std::cout << std::setw(3) << "v1" << " - " << std::setw(3) << "v2"<< " : weight\n";
    int i = (Start+1)%num_vertex;   // 若從4開始, i依序為5,6,0,1,2,3
    while (i != Start) {
        std::cout << std::setw(3) << predecessor[i] << " - " << std::setw(3) << i
                << " : " << std::setw(4) << AdjMatrix[predecessor[i]][i] <<"\n";
        i = (++i)%num_vertex;       // 到了6之後, 6+1 = 7, error:bad_access, 透過mod把7喬回0
    }

    cout<< "The total weight is: "<<totalWeight<<endl;
    cout<< "ok99"<<endl;
}
void GraphMST::AddEdge(int from, int to, int weight){
    AdjMatrix[from][to] = weight;
    AdjMatrix[to][from] = weight;
}

void GraphMST::AddEdgeDirect(int from, int to, int weight){
    AdjMatrix[from][to] = weight;
}


void GraphMST::PrimMST_maxSpanTree(int Start){
    // cout<<"ok1"<<endl;
    int key[num_vertex], predecessor[num_vertex];
    bool visited[num_vertex];

    // int totalWeight=0;
    for (int i = 0; i < num_vertex; i++) {
        // cout<<"ok2-"<<i<<endl;
        key[i] = Min_Weight;
        predecessor[i] = -1;
        visited[i] = false;     // false表示vertex還沒有被visited
    }
    // cout<<"ok3"<<endl;

    key[Start] = 0;
    for (int i = 0; i < num_vertex; i++) {
        int u = MaxKeyExtract(key, visited, num_vertex); //這裡就會是
        // totalWeight=totalWeight+AdjMatrix[u][predecessor[u]];///////////////////////////////////////////////////////// //(i-1)指到u
        int u1=predecessor[u];
        totalWeight=totalWeight+AdjMatrix[u][u1]; //(i-1)指到u
        
        if(u1>=0){ //<Debug> 就是防前一個點是-1 不然會出現double free or corruption (out) Aborted (core dumped)

            AdjMatrix_isMST[u][u1]=true; //被收錄的edge就變成true
            AdjMatrix_isMST[u1][u]=true;
        }
        
        
        cout<<"now picked edge: (v1, v2) = (" << u  << ", "<< u1 <<") weight: "<<AdjMatrix[u][u1]<<"   total weight: "<< totalWeight<< endl;
        // AdjMatrix_isMST[u][predecessor[u]]=true; //被收錄的edge就變成true
        visited[u] = true;
        for (int i = 0; i < num_vertex; i++) {
            // cout<<"ok3.1"<<endl;
            if ( visited[i]==false && AdjMatrix[u][i]!=0 && AdjMatrix[u][i]>key[i]) {
                // cout<<"ok3.2"<<endl;
                predecessor[i] = u;
                key[i] = AdjMatrix[u][i];
                std::cout << std::setw(3) << "Now: (v1, v2) = (" << u  << ", "<< i <<")\n";
                cout<<"key[i]: "<< key[i]<< endl;

                
            }
        }
    }
    // cout<<"ok4"<<endl;
    // print MST, 與MST演算法主體無關
    std::cout << std::setw(3) << "v1" << " - " << std::setw(3) << "v2"<< " : weight\n";
    // cout<<"ok4"<<endl;
    int i = (Start+1)%num_vertex;   // 若從4開始, i依序為5,6,0,1,2,3
    while (i != Start) {
        std::cout << std::setw(3) << predecessor[i] << " - " << std::setw(3) << i
                << " : " << std::setw(4) << AdjMatrix[predecessor[i]][i] <<"\n";
        i = (++i)%num_vertex;       // 到了6之後, 6+1 = 7, error:bad_access, 透過mod把7喬回0
    }

    
}

// =========================================================================================

std::vector<std::vector<int>> GraphMST::getDeletedEdgeBy_maxSpanTree(){
    // cout<<"ok1"<<endl;
    deletedTotal_weight = 0;
    cout<< "ok100.1"<<endl;
    PrimMST_maxSpanTree(2); //start from 2
    for(int i=0; i<num_vertex; i++){
        cout<< "ok100.1-1"<<endl;
       for(int j=i; j<num_vertex; j++){ //右上三角形就好, 因為是undirect graph
            cout<< "ok100.1-2"<<endl;
            cout<< "now i: "<<i<<"now j: "<<j<<endl;
            int w = AdjMatrix[i][j]; // 用來確定weight
            if(AdjMatrix_isMST[i][j]==false && AdjMatrix[i][j]!=0){
                result.push_back({i, j, w});
                // std::vector<std::vector<int>> AdjMatrix;
                // std::vector<std::vector<bool>> AdjMatrix_isMST;
                deletedTotal_weight = deletedTotal_weight+  w;
            }
            cout<< "ok100.1-3"<<endl;
        }
    }
    cout<< "ok100.2"<<endl;
    return result;
}



// Generated By AI ==================================================
// Helper function to detect cycles using DFS
bool hasCycleDFS(int node, vector<vector<int>> &adj, vector<int> &visited) {
    if (visited[node] == 1) return true; // Cycle detected
    if (visited[node] == 2) return false; // Already processed

    visited[node] = 1; // Mark node as visiting
    for (int neighbor : adj[node]) {
        if (hasCycleDFS(neighbor, adj, visited)) return true;
    }
    visited[node] = 2; // Mark node as processed
    return false;
}

// Check if the graph is acyclic
bool isAcyclic(int n, vector<vector<int>> &adj) {
    vector<int> visited(n, 0); // 0: unvisited, 1: visiting, 2: processed
    for (int i = 0; i < n; i++) {
        cout<<"ok300"<<endl;
        if (!visited[i] && hasCycleDFS(i, adj, visited)) {

            return false; // Cycle found
        }
    }
    cout<<"ok400"<<endl;
    return true;
}

















// struct Edge {
//     int u, v, w;
// };

// bool compare(const Edge& a, const Edge& b) {
//     return a.w < b.w; // Sort edges by weight
// }

// // int find(int x, std::vector<int>& parent) {
// //     if (x != parent[x]) parent[x] = find(parent[x], parent);
// //     return parent[x];
// // }

// // void unionSet(int x, int y, std::vector<int>& parent, std::vector<int>& rank) {
// //     int rootX = find(x, parent), rootY = find(y, parent);
// //     if (rootX != rootY) {
// //         if (rank[rootX] > rank[rootY]) {
// //             parent[rootY] = rootX;
// //         } else if (rank[rootX] < rank[rootY]) {
// //             parent[rootX] = rootY;
// //         } else {
// //             parent[rootY] = rootX;
// //             rank[rootX]++;
// //         }
// //     }
// // }



// Union-Find data structure to detect cycles in the graph
// class UnionFind {
// private:
//     std::vector<int> parent, rank;

// public:
//     UnionFind(int size) {
//         parent.resize(size);
//         rank.resize(size, 0);
//         for (int i = 0; i < size; i++) {
//             parent[i] = i; // Each node is its own parent initially
//         }
//     }

//     // Find the root of a node (with path compression)
//     int find(int node) {
//         if (parent[node] != node) {
//             parent[node] = find(parent[node]); // Path compression
//         }
//         return parent[node];
//     }

//     // Union two nodes (with rank optimization)
//     bool unionSets(int node1, int node2) {
//         int root1 = find(node1);
//         int root2 = find(node2);

//         if (root1 == root2) {
//             return false; // Cycle detected
//         }

//         // Attach smaller rank tree under the larger rank tree
//         if (rank[root1] > rank[root2]) {
//             parent[root2] = root1;
//         } else if (rank[root1] < rank[root2]) {
//             parent[root1] = root2;
//         } else {
//             parent[root2] = root1;
//             rank[root1]++;
//         }

//         return true; // Union successful, no cycle formed
//     }
// };

// // Function to check if adding an edge forms a cycle
// bool formsCycle(UnionFind &uf, int u, int v) {
//     return !uf.unionSets(u, v); // Returns true if a cycle is formed
// }

// void solveDirectedGraph(int n, std::vector<Edge>& edges) {
//     std::vector<int> inDegree(n, 0), outDegree(n, 0);
//     std::vector<std::vector<int>> adjList(n);
//     std::vector<bool> removed(edges.size(), false);

//     // Build adjacency list and compute degrees
//     for (int i = 0; i < edges.size(); i++) {
//         adjList[edges[i].u].push_back(i); // Store edge index
//         inDegree[edges[i].v]++;
//         outDegree[edges[i].u]++;
//     }

//     // Greedily remove edges forming cycles
//     int totalWeight = 0;
//     for (int i = 0; i < edges.size(); i++) {
//         if (!removed[i] && formsCycle(edges[i], adjList)) { // Check cycle
//             removed[i] = true;
//             totalWeight += edges[i].w;
//         }
//     }

//     std::cout << totalWeight << std::endl;
//     for (int i = 0; i < edges.size(); i++) {
//         if (removed[i]) {
//             std::cout << edges[i].u << " " << edges[i].v << " " << edges[i].w << std::endl;
//         }
//     }
// }

// ============================================================
// Function to detect all cycles and return edges in those cycles
vector<tuple<int, int, int>> detectCycles(int n, const vector<vector<int>> &adj, const vector<tuple<int, int, int>> &edges) {
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    vector<tuple<int, int, int>> cycleEdges;

    function<bool(int)> dfs = [&](int node) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                parent[neighbor] = node;
                if (dfs(neighbor)) return true;
                cout<< "ok401.1"<<endl;
            } else if (neighbor != parent[node]) {
                // Found a cycle, collect its edges
                int current = node;
                int b=true;
                while (current != neighbor) {
                    int par = parent[current];
                    for (const auto &[u, v, w] : edges) {
                        if ((u == par && v == current) || (u == current && v == par)) {
                            cycleEdges.emplace_back(u, v, w);
                            cout<< "ok401.4"<<endl;
                            b=false;
                            break;
                        }

                    }
                    if(b==false){
                        break;
                    }
                    current = par;
                }
                // Add the edge closing the cycle
                for (const auto &[u, v, w] : edges) {
                    if ((u == neighbor && v == node) || (u == node && v == neighbor)) {
                        cycleEdges.emplace_back(u, v, w);
                        break;
                    }
                    cout<< "ok401.2"<<endl;
                }

                return true;
            }
            cout<< "ok401.3"<<endl;
        }
        return false;
    };

    // Check for cycles starting from each unvisited node
    for (int i = 0; i < n; ++i) {
        if (!visited[i] && dfs(i)) break;
    }
    return cycleEdges;
}

void printGraph(const vector<vector<int>>& adj) {
    for (int i = 0; i < adj.size(); ++i) {
        cout << i << ": ";
        for (const int& neighbor : adj[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}



// Function to perform DFS and detect cycles in the directed graph
bool dfs(int v, const unordered_map<int, vector<pair<int, int>>>& adj, unordered_map<int, bool>& visited, unordered_map<int, bool>& recStack, vector<pair<int, int>>& cycleEdges, int parent) {
    visited[v] = true;
    recStack[v] = true;
    cout<<"ok602.3.0"<<endl;
    // Traverse all neighbors of the current node

    // Check if the current node has any neighbors in the adjacency list
    auto it = adj.find(v);
    if (it == adj.end()) {
        return false;  // No neighbors, so no cycle can be detected from this node
    }
    for (const auto& neighbor :  it->second) {//adj.at(v)) {
        cout<<"ok602.3.1"<<endl;
        int u = neighbor.first;  // neighbor node
        int w = neighbor.second; // weight of the edge

        // If the neighbor is not visited, recurse
        if (!visited[u]) {
            cout<<"ok602.3.1.0"<<endl;
            if (dfs(u, adj, visited, recStack, cycleEdges, v)) {
                cout<<"ok602.3.1.1"<<endl;
                cycleEdges.push_back({v, u}); // Record the edge causing the cycle
                return true;
            }
            cout<<"ok602.3.2"<<endl;
        }
        // If the neighbor is in the recursion stack, we have found a cycle
        else if (recStack[u]) {
            cout<<"ok602.3.3"<<endl;
            cycleEdges.push_back({v, u}); // Record the edge causing the cycle
            return true;
        }
        cout<<"ok602.3.2"<<endl;
    }

    // Backtrack, remove the node from recursion stack
    recStack[v] = false;
    return false;
}

// Function to detect cycles in the graph and return the edges that form the cycle
vector<pair<int, int>> findCycles(const unordered_map<int, vector<pair<int, int>>>& adj, int n) {
    unordered_map<int, bool> visited;
    unordered_map<int, bool> recStack;
    vector<pair<int, int>> cycleEdges;

    // Perform DFS for all nodes to detect cycles
    cout<<"ok602.1"<<endl;
    for (int i = 1; i <= n; ++i) {
        cout<<"ok602.2"<<endl;
        cout<<n<<endl;
        if (!visited[i]) {
            cout<<"ok602.3"<<endl;
            if (dfs(i, adj, visited, recStack, cycleEdges, -1)) {
                cout<<"ok602.4"<<endl;
                break;
            }
        }
    }

    return cycleEdges;
}

// Function to remove an edge with the minimum weight from the cycle
pair<int, int> removeEdgeFromCycle(const vector<pair<int, int>>& cycleEdges, const unordered_map<int, unordered_map<int, int>>& edgeWeights) {
    int minWeight = INT_MAX;
    pair<int, int> edgeToRemove;

    for (const auto& edge : cycleEdges) {
        int u = edge.first;
        int v = edge.second;
        int weight = edgeWeights.at(u).at(v);

        if (weight < minWeight) {
            minWeight = weight;
            edgeToRemove = edge;
        }
    }

    return edgeToRemove;
}

// Function to break the cycles in the directed graph
vector<pair<int, int>> breakCycles(unordered_map<int, vector<pair<int, int>>>& adj, unordered_map<int, unordered_map<int, int>>& edgeWeights, int n) {
    vector<pair<int, int>> removedEdges;

    while (true) {
        // Find cycles in the graph
        cout<<"ok602"<<endl;
        vector<pair<int, int>> cycleEdges = findCycles(adj, n);
        cout<<"ok603"<<endl;

        if (cycleEdges.empty()) {
            break; // No cycles left, graph is acyclic
        }

        // Find the edge with the minimum weight to remove
        pair<int, int> edgeToRemove = removeEdgeFromCycle(cycleEdges, edgeWeights);

        int u = edgeToRemove.first;
        int v = edgeToRemove.second;

        cout << "Removing edge: (" << u << ", " << v << ")" << endl;

        // Remove the edge from the graph
        adj[u].erase(remove_if(adj[u].begin(), adj[u].end(), [v](const pair<int, int>& e) { return e.first == v; }), adj[u].end());
        cout<<"ok600"<<endl;
        edgeWeights[u].erase(v);
        cout<<"ok601"<<endl;

        // Store the removed edge
        removedEdges.push_back({u, v});
    }

    return removedEdges;
}



int main(int argc, char *argv[]){



    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return 1;
    }

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

    
    cout << "(n,m) = ("<<n<<", "<<m<<")"<<endl;
    GraphMST g(n);
    // GraphMST g(7);

    vector<tuple<int, int, int>> edges; // (u, v, weight)
    vector<vector<int>> adj(n);        // Adjacency list for the graph/////////////
    int totalWeight = 0;
    vector<tuple<int, int, int>> removedEdges;


    // unordered_map<int, vector<pair<int, int>>> adj;
    // unordered_map<int, unordered_map<int, int>> edgeWeights;



    while (fin >> u >> v>> w){ //讀個line的前兩個element，第一個捨棄到junk中, 把第二個存到data中
        
        // cout << "add edge (u,v) = ("<<u<<", "<<v<<")"<<endl;
        if(graphType=="u"){
            g.AddEdge(u, v, w);
        }else{
            // g.AddEdgeDirect(u, v, w);
            
            edges.emplace_back(u, v, w);
            adj[u].push_back(v);
            // adj[u].push_back({v, w});
            // edgeWeights[u][v] = w;

            


        }

    }






    
    
    
    
    // g.AddEdge(0, 1, 5);g.AddEdge(0, 5, 3);
    // g.AddEdge(1, 0, 5);g.AddEdge(1, 2, 10);g.AddEdge(1, 4, 1);g.AddEdge(1, 6, 4);
    // g.AddEdge(2, 1, 10);g.AddEdge(2, 3, 5);g.AddEdge(2, 6, 8);
    // g.AddEdge(3, 2, 5);g.AddEdge(3, 4, 7);g.AddEdge(3, 6, 9);
    // g.AddEdge(4, 1, 1);g.AddEdge(4, 3, 7);g.AddEdge(4, 5, 6);g.AddEdge(4, 6, 2);
    // g.AddEdge(5, 0, 3);g.AddEdge(5, 4, 6);
    // g.AddEdge(6, 1, 4);g.AddEdge(6, 2, 8);g.AddEdge(6, 3, 9);g.AddEdge(6, 4, 2);

    
    // g.PrimMST_maxSpanTree(2);
    

    // g.PrimMST(2);
    cout<< "ok100"<<endl;
    if(graphType=="u"){
        std::vector<std::vector<int>> result = g.getDeletedEdgeBy_maxSpanTree();

            ////////// write the output file ///////////
        fout << g.deletedTotal_weight <<endl;
        for (int i = 0; i < result.size(); i++){
            ////cout<<"result[i][0] = "<<result[i][0]<<"result[i][1] = "<<result[i][1]<< endl;
            fout << result[i][0] << " " <<result[i][1] << " "<<result[i][2] << endl;       
        }
    }else{
        


        // Sort edges by weight in descending order
        sort(edges.begin(), edges.end(), [](const auto &a, const auto &b) {
            return get<2>(b) > get<2>(a); // ascending order of weight
        });
        // Break cycles by removing edges
        // vector<pair<int, int>> removedEdges = breakCycles(adj, edgeWeights, n);


        // // Print the sorted edges
        // cout << "Sorted edges (u, v, weight):" << endl;
        // for (const auto &[u, v, w] : edges) {
        //     cout << u << " " << v << " " << w << endl;
        // }

        bool a=true;
        while (a) {
            // Detect all cycles and collect their edges
            cout<< "ok401"<<endl;
            vector<tuple<int, int, int>> cycleEdges = detectCycles(n, adj, edges);
            // cout<< "ok200"<<endl;
            if (cycleEdges.empty()) break;

            // Find the edge with the minimum weight in the detected cycles
            auto minEdge = *min_element(cycleEdges.begin(), cycleEdges.end(), [](const auto &a, const auto &b) {
                return get<2>(a) < get<2>(b);
            });

            // Remove the minimum weight edge
            int u = get<0>(minEdge);
            int v = get<1>(minEdge);
            int w = get<2>(minEdge);
            

            cout<< "remove("<<u<<", "<<v<<", "<<w<<")"<<endl;
            
            adj[u].erase(remove(adj[u].begin(), adj[u].end(), v), adj[u].end());
            // Update the edges vector: remove the edge (u, v, w)
            edges.erase(remove(edges.begin(), edges.end(), make_tuple(u, v, w)), edges.end());

            // printGraph(adj);
            removedEdges.emplace_back(u, v, w);
            totalWeight += w;

            if(!isAcyclic(n, adj)){
                a=true;
                cout<< "ok400"<<endl;
            }else{
                a=false;
                cout<< "ok500"<<endl;
            }
        }
        cout<< "ok501"<<endl;
        // while (!isAcyclic(n, adj)) { //如果還是是cycle的話, 就erase cycle上weight 最大的edge
        //     //DO This Part

        // }

        // for (const auto &[u, v, w] : edges) {
        // // Temporarily remove the edge (u, v)
        // adj[u].erase(remove(adj[u].begin(), adj[u].end(), v), adj[u].end());

        // if (!isAcyclic(n, adj)) {
        //     // If the graph is still cyclic, keep the edge removed
        //     removedEdges.emplace_back(u, v, w);
        //     totalWeight += w;
        // } else {
        //     // Restore the edge since removing it is not necessary
        //     adj[u].push_back(v);

        // }
        // Output the total weight of removed edges
        fout << totalWeight << endl;
        for (const auto &[u, v, w] : removedEdges) {
            fout << u << " " << v << " " << w << endl;
        }

        // Output the removed edges
        // cout << "Removed edges:" << endl;
        // for (const auto& edge : removedEdges) {
        //     cout << "(" << edge.first << ", " << edge.second << ")" << endl;
        // }

    }


    // }

    
    
    
    
    
    
    
    // g6.AddEdge(0, 1, 5);g6.AddEdge(0, 5, 3);
    // g6.AddEdge(1, 0, 5);g6.AddEdge(1, 2, 10);g6.AddEdge(1, 4, 1);g6.AddEdge(1, 6, 4);
    // g6.AddEdge(2, 1, 10);g6.AddEdge(2, 3, 5);g6.AddEdge(2, 6, 8);
    // g6.AddEdge(3, 2, 5);g6.AddEdge(3, 4, 7);g6.AddEdge(3, 6, 9);
    // g6.AddEdge(4, 1, 1);g6.AddEdge(4, 3, 7);g6.AddEdge(4, 5, 6);g6.AddEdge(4, 6, 2);
    // g6.AddEdge(5, 0, 3);g6.AddEdge(5, 4, 6);
    // g6.AddEdge(6, 1, 4);g6.AddEdge(6, 2, 8);g6.AddEdge(6, 3, 9);g6.AddEdge(6, 4, 2);

    // std::cout << "MST found by Prim:\n";
    // // g6.PrimMST(2);
    // g6.PrimMST_maxSpanTree(2);


    fin.close();
    fout.close();
    return 0;
}
