// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
//  Modify     [2024/9/2 Meng-Chen Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

#include <random>//for random QS

#include <chrono>
#include <thread>//for sleep test
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int n = data.size(); // Get the size of the input vector
    
    for(int j=2-1; j<n; j++){
        int key=data[j];
        int i=j-1; //和前一個去比
        while(i>=0 && data[i]>key){ //如果現在j指到的那個比現在i指到的那個小的話, 就要往左邊走(即i那位往右邊shift)
            data[i+1]=data[i];//往右邊shift
            i=i-1;//再繼續往前和key筆
        }
        data[i+1]=key;
    }

}

/*
for previous done
void insertion_sort(char A[], int n){
    // int n = sizeof(A) / sizeof(A[0]);
    for(int j=2-1; j<n; j++){
        char key=A[j];
        int i=j-1; //和前一個去比
        while(i>=0 && A[i]>key){ //如果現在j指到的那個比現在i指到的那個小的話, 就要往左邊走(即i那位往右邊shift)
            A[i+1]=A[i];//往右邊shift
            i=i-1;//再繼續往前和key筆
        }
        A[i+1]=key;
    }
}
*/

// Quick sort method
void SortTool::QuickSort(vector<int>& data,int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
    // //std::cout <<" low2: "<<0<< " high2: "<<data.size()- 1<<endl;

}

// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
    //不中止條件：當剩下大於等於一個東東
    //std::cout <<" low3: "<<low<< " high3: "<<high<<endl;
    // sleep_for(milliseconds(1000));
    //sleep_until(system_clock::now() + seconds(1));
    // //std::cout << "loop1"<<endl;
    if ( ( high - low ) >= 1 ) // if not base case如果high - low = 1表示他們相差一個, 表示這段還有兩個東東所以繼續做
    {   
        //std::cout <<" low: "<<low<< " high: "<<high<<endl;
        int q=0;
        if (flag==0){//Normal partition: 拿highest index of the lower side 去做新的標兵（就是小堆的最大的那個)
            // //std::cout << "partition: ("<<low<<", "<<high<<")"<<endl;
            q=Partition(data, low, high); //把low high這段丟進去sort完之後回傳某個東東當標兵的他的最後位置return j, 之後拿它當左右半的切切位置在繼續切切
            //std::cout << "q = "<<q<<endl;
            //std::cout << "QuickSortSubVector: ("<<low<<", "<<q<<")"<<endl;
            QuickSortSubVector(data, low, q, 0); //上次標兵的最終位置拿去切切的左半
            //std::cout << "QuickSortSubVector: ("<<q+1<<", "<<high<<")"<<endl;
            QuickSortSubVector(data, q+1, high, 0);
            
        }else if (flag==1){//Normal partition: 拿highest index of the lower side 去做新的標兵（就是小堆的最大的那個)
            // //std::cout << "partition: ("<<low<<", "<<high<<")"<<endl;
            q=RandomizedPartition(data, low, high); //把low high這段丟進去sort完之後回傳某個東東當標兵的他的最後位置return j, 之後拿它當左右半的切切位置在繼續切切
            //std::cout << "q = "<<q<<endl;
            //std::cout << "QuickSortSubVector: ("<<low<<", "<<q<<")"<<endl;
            QuickSortSubVector(data, low, q, 1); //上次標兵的最終位置拿去切切的左半
            //std::cout << "QuickSortSubVector: ("<<q+1<<", "<<high<<")"<<endl;
            QuickSortSubVector(data, q+1, high, 1);
            
        }
    }
    //如果切切到這段只剩一個了, 那就是這段的data都已經被標兵處理過了, 已經好了

}

int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    //get random number in a range in c++
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(low, high); // define the range
    int randomIndex= distr(gen);
    int x=data[randomIndex]; //把"index"最小（最左邊的)那人作為標兵 大家都和它的數值比
    // int i=low-1; //i 從最左的(low 即p)左邊一格開始向右走
    // int j=high+1; //j 從最右的(high 即q)右邊一格開始向左走 (p m q)
    int i=low; //因為index問題, while 訪問data[i]的時候會址不到成data[-1]所以從i=0當下那個開始走走
    int j=high; 

    while(true){ //一直走然後swap直到i>=j
        //std::cout << "loop6";
        while(data[j]>x){//表示放對的, j指標繼續向左走走 //j要放前面
            j--;
            //std::cout << "loop4";
        }
        
        while(data[i]<x){ //當i指到的人值小於標兵值, 表示比標兵值小沒放錯,所以i就繼續向右走
            i++; //一直走直到data[i]>=x 停下來  如果標兵士最大的數會出問題, 這樣就會i一直加加加 加到超出那個陣列長  
            //std::cout << "loop5";
        }
        if(i<j){//如果i還在j的左邊就exchange他們指到的東東
            //<Debug1> 當有equal key, 左邊i看到左equal key停下,j看到右equal key停下時, i 就還是小於j但是因為都停下了所以一直卡在這個loop中 
            //std::cout << "in haha";

            int temp=data[i];
            data[i]=data[j];
            data[j]=temp;
            i++;  //<Debug1> swap完要加, 不然當左右都=x時, 就卡在這個loop了
            j--; //<Debug1> 所以你swap完要強迫推進一下, 要先跑去下一個, 表示現在這個處理完了才可以繼續detect之後


        }else{//如果他們停在同一個位置上, 或是已經錯位了, 表示已經掃完全部以這個標兵的左右半大小擺完了(小.. 標兵 ..大)了, 就可以return 這個標兵的最終位置（在"i", 因為當初=是被排在右半才算正確的）
            return j; //整個以某為標兵的做完之後, 會回傳這個標兵值"最後"應該在的index位置, 然後去當下次切切的切點位置

        }

    }


}
int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int x=data[low]; //把"index"最小（最左邊的)那人作為標兵 大家都和它的數值比
    // int i=low-1; //i 從最左的(low 即p)左邊一格開始向右走
    // int j=high+1; //j 從最右的(high 即q)右邊一格開始向左走 (p m q)
    int i=low; //因為index問題, while 訪問data[i]的時候會址不到成data[-1]所以從i=0當下那個開始走走
    int j=high; 
    while(true){ //一直走然後swap直到i>=j
        //std::cout << "loop6";
        while(data[j]>x){//表示放對的, j指標繼續向左走走 //j要放前面
            j--;
            //std::cout << "loop4";
        }
        
        while(data[i]<x){ //當i指到的人值小於標兵值, 表示比標兵值小沒放錯,所以i就繼續向右走
            i++; //一直走直到data[i]>=x 停下來  如果標兵士最大的數會出問題, 這樣就會i一直加加加 加到超出那個陣列長  
            //std::cout << "loop5";
        }
        if(i<j){//如果i還在j的左邊就exchange他們指到的東東
            //<Debug1> 當有equal key, 左邊i看到左equal key停下,j看到右equal key停下時, i 就還是小於j但是因為都停下了所以一直卡在這個loop中 
            //std::cout << "in haha";

            int temp=data[i];
            data[i]=data[j];
            data[j]=temp;
            i++;  //<Debug1> swap完要加, 不然當左右都=x時, 就卡在這個loop了
            j--; //<Debug1> 所以你swap完要強迫推進一下, 要先跑去下一個, 表示現在這個處理完了才可以繼續detect之後


        }else{//如果他們停在同一個位置上, 或是已經錯位了, 表示已經掃完全部以這個標兵的左右半大小擺完了(小.. 標兵 ..大)了, 就可以return 這個標兵的最終位置（在"i", 因為當初=是被排在右半才算正確的）
            return j; //整個以某為標兵的做完之後, 會回傳這個標兵值"最後"應該在的index位置, 然後去當下次切切的切點位置

        }

    }
}

void SortTool::QuickSort_for2Don1stElement(std::vector<std::vector<int>>& data){
    QuickSortSubVector_for2Don1stElement(data, 0, data.size() - 1);
    // //std::cout <<" low2: "<<0<< " high2: "<<data.size()- 1<<endl;

}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector_for2Don1stElement(std::vector<std::vector<int>>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
    //不中止條件：當剩下大於等於一個東東
    //std::cout <<" low3: "<<low<< " high3: "<<high<<endl;
    // sleep_for(milliseconds(1000));
    //sleep_until(system_clock::now() + seconds(1));
    // //std::cout << "loop1"<<endl;
    if ( ( high - low ) >= 1 ) // if not base case如果high - low = 1表示他們相差一個, 表示這段還有兩個東東所以繼續做
    {   
        //std::cout <<" low: "<<low<< " high: "<<high<<endl;
        int q=0;
        // if (flag==0){//Normal partition: 拿highest index of the lower side 去做新的標兵（就是小堆的最大的那個)
        //     // //std::cout << "partition: ("<<low<<", "<<high<<")"<<endl;
        //     q=Partition(data, low, high); //把low high這段丟進去sort完之後回傳某個東東當標兵的他的最後位置return j, 之後拿它當左右半的切切位置在繼續切切
        //     //std::cout << "q = "<<q<<endl;
        //     //std::cout << "QuickSortSubVector: ("<<low<<", "<<q<<")"<<endl;
        //     QuickSortSubVector_for2Don1stElement(data, low, q, 0); //上次標兵的最終位置拿去切切的左半
        //     //std::cout << "QuickSortSubVector: ("<<q+1<<", "<<high<<")"<<endl;
        //     QuickSortSubVector_for2Don1stElement(data, q+1, high, 0);
            
        // }else if (flag==1){//Normal partition: 拿highest index of the lower side 去做新的標兵（就是小堆的最大的那個)
        //     // //std::cout << "partition: ("<<low<<", "<<high<<")"<<endl;
        //     q=RandomizedPartition_for2Don1stElement(data, low, high); //把low high這段丟進去sort完之後回傳某個東東當標兵的他的最後位置return j, 之後拿它當左右半的切切位置在繼續切切
        //     //std::cout << "q = "<<q<<endl;
        //     //std::cout << "QuickSortSubVector: ("<<low<<", "<<q<<")"<<endl;
        //     QuickSortSubVector_for2Don1stElement(data, low, q, 1); //上次標兵的最終位置拿去切切的左半
        //     //std::cout << "QuickSortSubVector: ("<<q+1<<", "<<high<<")"<<endl;
        //     QuickSortSubVector_for2Don1stElement(data, q+1, high, 1);
            
        // }

        //就用randomizedpartition就好了
        q=RandomizedPartition_for2Don1stElement(data, low, high); //把low high這段丟進去sort完之後回傳某個東東當標兵的他的最後位置return j, 之後拿它當左右半的切切位置在繼續切切
        //std::cout << "q = "<<q<<endl;
        //std::cout << "QuickSortSubVector: ("<<low<<", "<<q<<")"<<endl;
        QuickSortSubVector_for2Don1stElement(data, low, q); //上次標兵的最終位置拿去切切的左半
        //std::cout << "QuickSortSubVector: ("<<q+1<<", "<<high<<")"<<endl;
        QuickSortSubVector_for2Don1stElement(data, q+1, high);
    }
    //如果切切到這段只剩一個了, 那就是這段的data都已經被標兵處理過了, 已經好了

}
int SortTool::RandomizedPartition_for2Don1stElement(std::vector<std::vector<int>>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    //get random number in a range in c++
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(low, high); // define the range
    int randomIndex= distr(gen);
    int x=data[randomIndex][0]; //把"index"最小（最左邊的)那人作為標兵 大家都和它的數值比
    // int i=low-1; //i 從最左的(low 即p)左邊一格開始向右走
    // int j=high+1; //j 從最右的(high 即q)右邊一格開始向左走 (p m q)
    int i=low; //因為index問題, while 訪問data[i]的時候會址不到成data[-1]所以從i=0當下那個開始走走
    int j=high; 

    while(true){ //一直走然後swap直到i>=j
        //std::cout << "loop6";
        while(data[j][0]>x){//表示放對的, j指標繼續向左走走 //j要放前面
            j--;
            //std::cout << "loop4";
        }
        
        while(data[i][0]<x){ //當i指到的人值小於標兵值, 表示比標兵值小沒放錯,所以i就繼續向右走
            i++; //一直走直到data[i]>=x 停下來  如果標兵士最大的數會出問題, 這樣就會i一直加加加 加到超出那個陣列長  
            //std::cout << "loop5";
        }
        if(i<j){//如果i還在j的左邊就exchange他們指到的東東
            //<Debug1> 當有equal key, 左邊i看到左equal key停下,j看到右equal key停下時, i 就還是小於j但是因為都停下了所以一直卡在這個loop中 
            //std::cout << "in haha";
            //for 2D交換就要兩個都交換了
            int temp0=data[i][0];
            int temp1=data[i][1];
            data[i][0]=data[j][0];
            data[i][1]=data[j][1];
            data[j][0]=temp0;
            data[j][1]=temp1;
            i++;  //<Debug1> swap完要加, 不然當左右都=x時, 就卡在這個loop了
            j--; //<Debug1> 所以你swap完要強迫推進一下, 要先跑去下一個, 表示現在這個處理完了才可以繼續detect之後


        }else{//如果他們停在同一個位置上, 或是已經錯位了, 表示已經掃完全部以這個標兵的左右半大小擺完了(小.. 標兵 ..大)了, 就可以return 這個標兵的最終位置（在"i", 因為當初=是被排在右半才算正確的）
            return j; //整個以某為標兵的做完之後, 會回傳這個標兵值"最後"應該在的index位置, 然後去當下次切切的切點位置

        }

    }


}


// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    //[from PA0]
    // cout << "low: "<<low<<endl; 
    // cout << "high: "<<high<<endl;       
    // cout << "the vector iskkkkkkkkkkk: "<<endl;                                          
    // displaySubVector( low, high );    
                                        
    // test base case; size of vector equals 1
    if ( ( high - low ) >= 1 ) // if not base case
    {
        int middle1;  // calculate middle of vector
        int middle2;  // calculate next element over
        

        middle1 = (high+low)/2;
        middle2 = (high+low)/2+1;
        
        // for (int num : data) {
        //   //std::cout << num << " ";
        // }
        // debug output of split step 
        #ifdef _DEBUG_ON_	  
        cout << "split:   "<<endl;                                          
        displaySubVector( low, high );                                 
        cout << endl << "         "<<endl;                                  
        displaySubVector( low, middle1 );                              
        cout << endl << "         "<<endl;                                  
        displaySubVector( middle2, high );                             
        cout << endl << endl;                                         
        #endif


        // cout << "the left half is: "<<endl;                                          
        // displaySubVector( low, middle1 );    
        // cout << "the left half is: "<<endl;                                          
        // displaySubVector( middle2, high );    
        /*TODO : recursive function call to split vector in half; sort each half (recursive calls)
        ???               // first half of vector      
        ???               // second half of vector    
        */
        MergeSortSubVector(data, low, middle1);
        MergeSortSubVector(data, middle2, high);
        
        



        // merge two sorted vectors after split calls return
        Merge( data, low, middle1, middle2, high );
    } // end if
}

/*
for previous done: PA0
*/

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int leftIndex = low; // index into left subvector //左半第一個             
    int rightIndex = middle2; // index into right subvector  //右半第一個       
    int combinedIndex = low; // index into temporary working vector //左半第一個當i
    vector< int > combined; // working vector              
    // std::vector<int> combined(right - left + 1);
    // output two subvectors before merging
    #ifdef _DEBUG_ON_
    cout << "merge:   ";                  
    displaySubVector( low, middle1 );     
    cout << endl << "         ";          
    displaySubVector( middle2, high );    
    cout << endl;  
    #endif
        
    /*TODO : merge vectors until reaching end of either*/
    while ( leftIndex <= middle1 && rightIndex <= high ) //當順序都還對
        {
        // place smaller of two current elements into result
        // and move to next space in vector
        if(data[leftIndex]<=data[rightIndex]){
            //combined[combinedIndex - left] = data[leftIndex]; //就把左邊的放上去
            combined.push_back(data[leftIndex]);
            leftIndex++; //左邊右移
        }else{
            //combined[combinedIndex - left] = data[rightIndex]; //就把左邊的放上去
            combined.push_back(data[rightIndex]);
            rightIndex++;
        }
        combinedIndex++;//換放下一個數
        } // end while //一直做直到都跑完
    
    if ( leftIndex == middle2 ) // if at end of left vector          
        {                                                               
        // copy in rest of right vector 就直接把右半複製貼上
        while(rightIndex<=high){//右半的尾端
            //combined[combinedIndex - left]=data[rightIndex];
            combined.push_back(data[rightIndex]);
            rightIndex++;
            combinedIndex++;
        }
        
        } // end if                                                     
    else // at end of right vector                                   
        {                                                               
        // copy in rest of left vector
        while(leftIndex<=middle1){//左半的尾端
            //combined[combinedIndex - left]=data[leftIndex];
            combined.push_back(data[leftIndex]);
            leftIndex++;
            combinedIndex++;
        }
        } // end else
    
        
    /*TODO : copy values back into original vector
        ???
    */
        for (int i = low; i <= high; i++) {
        data[i] = combined.at(i - low);
    }
    //   for (int value : combined) {
    //     data[i] = value;
    //     cout << value << " ";
    // }
        
    // output merged vector         
    #ifdef _DEBUG_ON_
    cout << "         ";            
    displaySubVector( low, high );
    cout << endl << endl;           
    #endif
}

// bottom-up style implementation of merge sort
void SortTool::BottomUpMergeSort(vector<int>& data) 
{
  /*TODO :
    Implement merge sort in bottom-up style, in other words,
    without recursive function calls.
    Hint: 
    1. Divide data to n groups of one data each group
    2. Iteratively merge each pair of 2 neighbor groups into one larger group
    3. Finally we obtain exactly one sorted group
  */
    //本來merge sort是用recursive從下往上做, bottom up merge sort 是用while從上往下做
    // 1. Divide data to n groups of one data each group
    //每個data自己都先當一組merge 好的段段, 就省略了merge sort的deviding 的部份
    //===============================================================
    int numGroup=data.size(); //總共有幾組（最開始有幾個段段fu）
    int groupMem = 1; //每個group的人數
    while(numGroup>1){ //當現在還沒有merge到剩一組
    // while(groupMem<=data.size()){//<Debug6> 這樣, 還要多做一次才對, 但真不懂
        int i=1; //最左的<Debug> 因為merge()傳進去的是index, 所以是從零開始才對！或是保留1但最後傳進merge要-1！!

        // std::cout<<"loop1";
        while(i <= data.size()){    //<Debug3> 當還不是最後一組, 最後一組因為可能沒有滿, 要另外處理, 阿如果剛剛好, 在前一組剛好就會被做完, 就不會跑到跑下面的那個剩餘處理了
            // int a = 
            // Merge( data, left, middle1, middle2, right );
            // if((i+groupMem*2-1>=(data.size()-1))){//如果後面那組不完整的話（就是現在的i如果加上這組人會報表的話, 那就是這整個加到底了）, 就是merge到它到底
            //     Merge( data, i, i+groupMem-1, i+groupMem, data.size()-1 );//它和它隔壁的group merge起來
            // }else{
            //     Merge( data, i, i+groupMem-1, i+groupMem, i+groupMem*2-1 );//它和它隔壁的group merge起來
            // }
            Merge( data, i-1, i+groupMem-1-1, i+groupMem-1, std::min((int)data.size()-1, i+groupMem*2-1-1) );//它和它隔壁的group merge起來
            

            i=i+groupMem*2;//在併右邊那組兩個
            // std::cout<<"loop2";
        }
        // numGroup=(int)numGroup/groupMem; //就是組數會剛剛好
        // if(i<data.size()){//<Debug3> 如果最後一組處理完後還有剩下的（就是i index還沒超出最後一個數字）, 就會跑到這個
        //     //它自己成一組, 啥都不做, 等等再merge
        //     numGroup=numGroup+1; //會多一個不完全的組
        // }
        if(numGroup%2==0){ //<Debug> 是/2不是/groupMem!!
            numGroup=numGroup/2; //就是組數會剛剛好
        }else{
            numGroup=(int)numGroup/2+1; //int 是取整數, 多一個組
        }
        groupMem = groupMem*2;
    }

    
    //=========================== 下面錯的 ====================================
    // int numGroup=data.size(); //總共有幾組（最開始有幾個段段fu）
    // int groupMem = 1; //每個group的人數
    // // while(numGroup>1){ //當現在還沒有merge到剩一組
    // while(groupMem<data.size()){
    //     int i=0; //最左的<Debug> 因為merge()傳進去的是index, 所以是從零開始才對！或是保留1但最後傳進merge要-1！!

    //     std::cout<<"loop1";
    //     while(i < data.size()-groupMem){    //<Debug3> 當還不是最後一組, 最後一組因為可能沒有滿, 要另外處理, 阿如果剛剛好, 在前一組剛好就會被做完, 就不會跑到跑下面的那個剩餘處理了
    //         // int a = 
    //         // Merge( data, left, middle1, middle2, right );
    //         if((i+groupMem*2-1>=(data.size()-1))){//如果後面那組不完整的話（就是現在的i如果加上這組人會報表的話, 那就是這整個加到底了）, 就是merge到它到底
    //             Merge( data, i, i+groupMem-1, i+groupMem, data.size()-1 );//它和它隔壁的group merge起來
    //         }else{
    //             Merge( data, i, i+groupMem-1, i+groupMem, i+groupMem*2-1 );//它和它隔壁的group merge起來
    //         }

    //         i=i+groupMem*2;//在併右邊那組兩個
    //         std::cout<<"loop2";
    //     }
    //     // numGroup=(int)numGroup/groupMem; //就是組數會剛剛好
    //     // if(i<data.size()){//<Debug3> 如果最後一組處理完後還有剩下的（就是i index還沒超出最後一個數字）, 就會跑到這個
    //     //     //它自己成一組, 啥都不做, 等等再merge
    //     //     numGroup=numGroup+1; //會多一個不完全的組
    //     // }
    //     // if(numGroup%groupMem==0){
    //     //     numGroup=numGroup/groupMem; //就是組數會剛剛好
    //     // }else{
    //     //     numGroup=(int)numGroup/groupMem+1; //int 是取整數, 多一個組
    //     // }
    //     groupMem = groupMem*2;
        //void MergeSort::merge( int left, int middle1, int middle2, int right ) 
    

}

// Heap sort method, be aware that you are NOT required to implement heap sort in PA1
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
}
