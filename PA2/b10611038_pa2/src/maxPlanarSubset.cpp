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
    MaxPlanarSubset(int n, std::vector<int> chords) //c++ class 傳array要這樣const int* chords
    : n(n), chords(chords) {
    }
    
    void maximumPlanarSubset(){

        //<Debug2-0> 不行這樣！!過了initialization 後, 要用assign!
        //<Debug2-1> 要用assign!
        M.assign(2 * n, std::vector<int>(2 * n, 0)); //<Debug2-2> 0~2n-1共有2n個數！! std::vector<std::vector<uint16_t>> M;
        S.assign(2 * n, std::vector<int>(2 * n, 0));

        for(int i=0;i<=2*n-1;i++){
            M[i][i]=0; //initialize 對角線為0    
        }

        for(int l=1;l<=2*n-1;l++){//左右i,j的兩兩間距
            for(int i=0;i<=2*n-1-l;i++){

                
                int j=i+l;
                int k=chords[j];//在j上的chord的另一端（its chord pair）
    
                if(k<i || j<k){ //case1 <Debug3> 注意！!不可以這樣用！!if(!(i<=k<=j))
                    M[i][j]=M[i][j-1];
                    S[i][j]=1; //case1
                    ////cout<<"ok13-1.1.1="<<i<< endl;
                }else if(k==i){ //case2
                    M[i][j]=M[i+1][j-1]+1; //+1就為kj（即ij上)這一條
                    S[i][j]=2;
                    ////cout<<"ok13-1="<<i<< endl;
                }else{//如果k在ij內（k可=j, 但k!=i) //case3
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

private:
    int n;
    std::vector<int> chords;
    std::vector<std::vector<int>> maximumPlanarSubset_chord; //uint16_t

    std::vector<std::vector<int>> S;
    std::vector<std::vector<int>> M;

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
};
