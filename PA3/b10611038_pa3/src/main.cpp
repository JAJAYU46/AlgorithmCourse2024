// C++ code
#include <iostream>

#include <vector>
#include <iomanip>      // for setw()

using namespace std;


#include <cstring>
#include <fstream>
#include <vector>


#include <map>

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
    
    while (fin >> u >> v>> w){ //讀個line的前兩個element，第一個捨棄到junk中, 把第二個存到data中
        
        // cout << "add edge (u,v) = ("<<u<<", "<<v<<")"<<endl;
        if(graphType=="u"){
            g.AddEdge(u, v, w);
        }else{
            g.AddEdgeDirect(u, v, w);
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

    std::vector<std::vector<int>> result = g.getDeletedEdgeBy_maxSpanTree();
    ////////// write the output file ///////////
    fout << g.deletedTotal_weight <<endl;
    for (int i = 0; i < result.size(); i++){
        ////cout<<"result[i][0] = "<<result[i][0]<<"result[i][1] = "<<result[i][1]<< endl;
        fout << result[i][0] << " " <<result[i][1] << " "<<result[i][2] << endl;       
    }
    
    
    
    
    
    
    
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
