#include <iostream>

#include <cstring>
#include <fstream>
#include <vector>

using namespace std;


// #include "maxPlanarSubset.h"
#include "maxPlanarSubset.cpp"

#include "sort_tool.h"
// #include "sort_tool.cpp" //如果沒有用makefile, 分開寫記得兩個都要include!


void printVector(const std::vector<int>& vec) {
    for (int value : vec) {
        //cout << value << " ";
    }
        //cout << std::endl;
}

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

    int n2,n;
    ////cout<<"ok1"<< endl;
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    fin>> n2; //裝2n個點
    n=n2/2;

    int a,b;
    // vector<int> data_a, data_b; //紀錄個chord中兩端點

    // int chords[2*n]; //建立pair array, 之後會索引紀錄chord(為chord[i] = 0~2n-1個端點各自chord的另一端) 
    std::vector<int> chords(2*n);  //先給各個vector一個已知的空間, 之後才可以確定chords[a]=b不會出錯

    while (fin >> a >> b){ //讀個line的前兩個element，第一個捨棄到junk中, 把第二個存到data中
        if(a==0 && b==0){//要兩個都用, 不然有可能a=0只是它其中之一的vertics然後就停了
            break;
        }
        // data_b.push_back(a);         
        // data_b.push_back(b); // data[0] will be the first data. 

        ////cout<<"a: "<<a<<" b: "<<b<< endl;
        // chords.emplace_back(a, b);
        chords[a]=b;
        chords[b]=a;
        //cout<<"a="<<a<<"  b="<<b<< endl;
                    // data[1] will be the second data and so on.
    }

    ///////////////Maximum Planner Part////////////////
    MaxPlanarSubset mps(n, chords);
    //cout<<"ok6"<< endl;
    mps.maximumPlanarSubset();
    //cout<<"ok7"<< endl;
    std::vector<std::vector<int>>result = mps.get_maximumPlanarSubset_chord();
    ////cout<<"ok100"<< endl;


    ////////////Sorting the result base on the first element////////////////
    SortTool NTUSortTool;
    NTUSortTool.QuickSort_for2Don1stElement(result);
    //////////// write the output file ///////////
    fout << result.size() <<endl;
    for (int i = 0; i < result.size(); i++){
        ////cout<<"result[i][0] = "<<result[i][0]<<"result[i][1] = "<<result[i][1]<< endl;
        fout << result[i][0] << " " <<result[i][1] << endl;       
    }
    fin.close();
    fout.close();

    return 0;
}


