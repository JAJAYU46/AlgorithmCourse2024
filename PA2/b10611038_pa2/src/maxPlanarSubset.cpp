// #include "maxPlanarSubset.h"
#include <vector>
#include <algorithm>
// #ifndef MAX_PLANAR_SUBSET_H
// #define MAX_PLANAR_SUBSET_H

// #include <vector>
#include <utility>
#include <iostream>
using namespace std;

class MaxPlanarSubset {
public:
    // MaxPlanarSubset(int n, const std::vector<std::pair<int, int>>& chords);
    MaxPlanarSubset(int n, std::vector<int> chords) //c++ class 傳array要這樣const int* chords
    : n(n), chords(chords) {
        //cout<<"ok4"<< endl;
        // M = new int*[2*n];
        // S = new int*[2*n];
        // M = new int *[2*n];
        // S = new int *[2*n];
        // for (int i = 0; i < 2*n; i++) {
        //     M[i] = new int[2*n];

        //     S[i] = new int[2*n]();
        // }
        // for (int k = 0; k < vertice_number; k++)
        // {
        // maxPTable[k] = new int[vertice_number];
        // memset(maxPTable[k], -1, sizeof(int) * vertice_number);
        // maxPTable[k][k] = 0;
        // linkPTable[k] = new int[vertice_number];
        // memset(linkPTable[k], -1, sizeof(int) * vertice_number);
        // }
        // int **maxPTable = new int *[vertice_number];
        // int **linkPTable = new int *[vertice_number];
        //cout<<"ok4.5"<< endl;
    }

    // Memory cleanup - put this at the end of your code
    // ~MaxPlanarSubset(){
    //     for (int i = 0; i < 2*n; i++) {
    //     delete[] M[i];  // Delete each row in maxPTable
    //     delete[] S[i]; // Delete each row in linkPTable
    //     }
    //     delete[] M; // Delete the array of pointers
    //     delete[] S; // Delete the array of pointers

    // }
    
    void maximumPlanarSubset(){
        //bottom up method
        //cout<<"ok7.5"<< endl;
        //<Debug2-0> 不行這樣！!過了initialization 後, 要用assign!
        // int M[2*n-1][2*n-1]={}; // This will initialize all elements to zero（把左下三角形也變成0不然會重複算到)同一條chord //創建一個DP用表格 共2n-1個數
        ////cout<<"ok8"<< endl;
        // int S[2*n-1][2*n-1];//用來紀錄各個M[i,j]是來自case幾，去看他們是從誰來的
        ////cout<<"ok9"<< endl;
        //<Debug2-1> 要用assign!
        M.assign(2 * n, std::vector<int>(2 * n, 0)); //<Debug2-2> 0~2n-1共有2n個數！! std::vector<std::vector<uint16_t>> M;
        // //cout<<"ok9.5"<< endl;
        S.assign(2 * n, std::vector<int>(2 * n, 0));
        // //cout<<"ok10"<< endl;

        // M.assign(2 * n, std::vector<uint16_t>(2 * n)); //<Debug2-2> 0~2n-1共有2n個數！! std::vector<std::vector<uint16_t>> M;
        //cout<<"ok9.5"<< endl;
        // S.assign(2 * n, std::vector<uint16_t>(2 * n));
        //cout<<"ok10"<< endl;
        for(int i=0;i<=2*n-1;i++){
            M[i][i]=0; //initialize 對角線為0    
        }
        ////cout<<"ok11"<< endl;
        for(int l=1;l<=2*n-1;l++){//左右i,j的兩兩間距
            // //cout<<"ok12"<< endl;
            for(int i=0;i<=2*n-1-l;i++){

                
                int j=i+l;
                //cout<<"i="<<i<<"  j="<<j<< endl;
                ////cout<<"ok13  j="<<j<< endl;
                int k=chords[j];//在j上的chord的另一端（its chord pair）
                ////cout<<"ok13  k="<<k<< endl;
                if(k<i || j<k){ //case1 <Debug3> 注意！!不可以這樣用！!if(!(i<=k<=j))
                    ////cout<<"ok13-1.1.1 i,j,k="<<i<<j<<k<< endl;
                    M[i][j]=M[i][j-1];
                    S[i][j]=1; //case1
                    ////cout<<"ok13-1.1.1="<<i<< endl;
                }else if(k==i){ //case2
                    M[i][j]=M[i+1][j-1]+1; //+1就為kj（即ij上)這一條
                    S[i][j]=2;
                    ////cout<<"ok13-1="<<i<< endl;
                }else{//如果k在ij內（k可=j, 但k!=i) //case3
                    // M[i][j]=std::max(M[i][j-1],M[i][k-1]+1+M[k+1][j-1]); //M[i][k-1]+1+M[k+1][j-1] 左半(靠i那半)+kj這條+右半(靠j那半), 
                    // S[i][j]=3;
                    if(M[i][j-1]>=M[i][k-1]+1+M[k+1][j-1]){ //如果兩種方法都一樣, 就選擇走M[i][j-1]這個方法的（阿算出的最終chord 就會不同)
                        M[i][j]=M[i][j-1]; //其實就是case1啦
                        S[i][j]=1;
                    }else{
                        M[i][j]=M[i][k-1]+1+M[k+1][j-1];
                        S[i][j]=4;
                    }
                    ////cout<<"ok13-1="<<i<< endl;
                }
                ////cout<<"ok14"<< endl;
            }
            ////cout<<"ok15"<< endl;
        }
        return;
    }
    
    std::vector<std::vector<int>> get_maximumPlanarSubset_chord(){
       trace_maximumPlanarSubset_chord(0, 2*n-1);
       return maximumPlanarSubset_chord;
    }


    // int computeMPS() {
    // // Initialize and call the DP function
    // return maxPlanarSubset(0, 2 * n - 1);
    // }

private:
    int n;
    std::vector<int> chords;
    std::vector<std::vector<int>> maximumPlanarSubset_chord; //uint16_t
    // std::vector<std::vector<int>> M;
    // std::vector<std::vector<uint16_t>> M;
    // std::vector<std::vector<uint16_t>> S;
    std::vector<std::vector<int>> S;
    std::vector<std::vector<int>> M;
    // int[][] M;
    // int** M;
    // int** S;
    void trace_maximumPlanarSubset_chord(int i,int j){
        ////cout<<"now i = "<<i<<"now j = "<<j<< endl;
        //中止條件： trace回去到了如果j<=i 左下角形含對角線就停止這個subtree, return 0;
        if(j<=i){
            return;
        }

        if(S[i][j]==1){//case1 //ij上面沒線, 來自M[i][j]=M[i][j-1];
            trace_maximumPlanarSubset_chord(i,j-1);
        }else if(S[i][j]==2){//case2 //ij上面有線, 來自M[i][j]=M[i+1][j-1]+1;
            ////cout<<"push i = "<<i<<"push j = "<<j<< endl;
            trace_maximumPlanarSubset_chord(i+1,j-1);
                    
            maximumPlanarSubset_chord.push_back({i,j}); //放在回call後面, 所以出來的chord還是會照原順序
        }else if(S[i][j]==4){//case4 //ij上面有線, 來自M[i][j]=M[i][k-1]+1+M[k+1][j-1];
            int k=chords[j];
            ////cout<<"push i = "<<i<<"push j = "<<j<< endl;
            trace_maximumPlanarSubset_chord(i,k-1);
            trace_maximumPlanarSubset_chord(k+1,j-1);
            maximumPlanarSubset_chord.push_back({k,j}); //<Debug4> 這個case是kj在連線！//放在回call後面, 所以出來的chord還是會照原順序
        }
        return;
    }
    // // int maxPlanarSubset(int i, int j);
    // int maxPlanarSubset(int i, int j) {
    // if (i >= j) return 0;
    // if (dp[i][j] != -1) return dp[i][j];
    
    // // Compute DP logic based on the maximum planar subset
    // // ...
    
    // return dp[i][j];
    // }
};

// // #endif
// MaxPlanarSubset::MaxPlanarSubset(int n, const std::vector<std::pair<int, int>>& chords)
//     : n(n), chords(chords), dp(2 * n, std::vector<int>(2 * n, -1)) {}

// int MaxPlanarSubset::computeMPS() {
//     // Initialize and call the DP function
//     return maxPlanarSubset(0, 2 * n - 1);
// }

// int MaxPlanarSubset::maxPlanarSubset(int i, int j) {
//     if (i >= j) return 0;
//     if (dp[i][j] != -1) return dp[i][j];
    
//     // Compute DP logic based on the maximum planar subset
//     // ...
    
//     return dp[i][j];
// }