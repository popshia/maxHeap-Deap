// 10627130 林冠良 & 10627131 李峻瑋 // CodeBlocks 17.12
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <math.h>

using namespace std ;

typedef struct DataStruct {
    //string schoolNum = "\0" ;
    //string schoolName = "\0" ;
    //string departmentNum = "\0" ;
    //string departmentName = "\0" ;
    int index = 0 ;
    int student = 0 ;
    //int teacher = 0 ;
    //int graduated = 0 ;
    //string wholeSentence = "\0" ;
} DataStruct ;

static ifstream input ;
static ofstream output ;
static string FileN = "0" ;
static int Count = 0 ;

class OutStandingMove {
    vector<DataStruct> maxHeap ;
    vector<DataStruct> deap ;
    vector<DataStruct> leftDeap ;
    vector<DataStruct> rightDeap ;
    DataStruct tempData ;

public:
    void InputData( int function ) { // tool
        maxHeap.clear() ;
        maxHeap.clear() ;
        deap.clear() ;
        leftDeap.clear() ;
        rightDeap.clear() ;
        tempData.student = 0 ;
        tempData.index = 0 ;
        string sentence = "\0" ;
        getline( input, sentence ) ;
        getline( input, sentence ) ;
        getline( input, sentence ) ;

        while ( getline( input, sentence ) ) {
            // cout << sentence << endl ;
            tempData.index = Count + 1 ;
            // tempData.wholeSentence = sentence ;
            vector<string> cut ;
            string token ;
            istringstream cutStream( sentence ) ;

            while ( getline( cutStream, token, '\t' ) ) // cut the token one by one
                cut.push_back( token ) ;

            //tempData.schoolNum = cut[0] ;
            //tempData.schoolName = cut[1] ;
            //tempData.departmentNum = cut[2] ;
            //tempData.departmentName = cut[3] ;

            if ( cut[6].size() > 3 ) {
                cut[6].erase( find( cut[6].begin(), cut[6].end(), '"' ) ) ;
                cut[6].erase( find( cut[6].begin(), cut[6].end(), ',' ) ) ;
                cut[6].erase( find( cut[6].begin(), cut[6].end(), '"' ) ) ;
            } // erase '"' & ','
            tempData.student = atoi( cut[6].c_str() ) ;

            /*if ( cut[8].size() > 3 ) {
                cut[8].erase( find( cut[8].begin(), cut[8].end(), '"' ) ) ;
                cut[8].erase( find( cut[8].begin(), cut[8].end(), ',' ) ) ;
                cut[8].erase( find( cut[8].begin(), cut[8].end(), '"' ) ) ;
            } // erase '"' & ','
            tempData.graduated = atoi( cut[8].c_str() ) ;*/
            if ( function == 1 ) {
                maxHeap.push_back( tempData ) ;
                MaxHeap() ;
            } // function 1
            
            /*if ( function == 2 ) {
                deap.push_back( tempData ) ;
            } // function 2*/
            Count++ ;
        } // get the whole file
    } // InputData()

    void MaxHeapify( int child ) {
        int root = child / 2 ; // 取得root
        int largest = root ; // largest用來記錄包含root與child, 三者之中Key最大的node
        
        if ( root >= 1 && maxHeap[child].student > maxHeap[root].student )
            largest = child ;

        if ( largest != root ) { // 如果目前root的Key不是三者中的最大
            swap( maxHeap[largest], maxHeap[root] ) ; // 就調換root與三者中Key最大的node之位置
            MaxHeapify( root ) ; // 調整新的subtree成Max Heap
        } // if()
    } // MaxHeapify()
    
    void MinHeapify( int child ) {
        int root = child / 2 ; // 取得root
        int smallest = root ; // largest用來記錄包含root與child, 三者之中Key最大的node
        
        if ( root >= 1 && maxHeap[child].student < maxHeap[root].student )
            smallest = child ;
        
        if ( smallest != root ) { // 如果目前root的Key不是三者中的最大
            swap( maxHeap[smallest], maxHeap[root] ) ; // 就調換root與三者中Key最大的node之位置
            MinHeapify( root ) ; // 調整新的subtree成Max Heap
        } // if()
    } // MaxHeapify()

    void MaxHeap() {
        DataStruct emptyRoot ;
        maxHeap.insert( maxHeap.begin(), emptyRoot ) ;
        MaxHeapify( (int)maxHeap.size() - 1 ) ;
        maxHeap.erase( maxHeap.begin() ) ; // 將index(0)刪除
    } // MaxHeap()

    void Deap() {
        DataStruct emptyRoot ; // instal the empty root
        maxHeap.insert( maxHeap.begin(), emptyRoot ) ;
        MaxHeapify( (int)maxHeap.size() - 1 ) ;
    } // Deap()

    void Combine() {
        DataStruct emptyRoot ;
        deap.insert( maxHeap.begin(), emptyRoot ) ;
        // deap.push_back( leftDeap ) ;
        // deap.push_back( rightDeap ) ;
    } // Combine()

    void PrintMaxHeap() {
        for ( int i = 0 ; i < maxHeap.size() ; i ++ ) cout << maxHeap[i].index << " " << maxHeap[i].student << endl ;
        cout << "<MAX HEAP>" << endl ;
        cout << "root: [" << maxHeap.front().index<< "] " << maxHeap.front().student << endl ;
        cout << "rightmost bottom: [" << maxHeap.back().index<< "] " << maxHeap.back().student << endl ;
        int leftMost = 0 ;
        for ( int i = 1 ; i < maxHeap.size() ; leftMost++ ) i *= 2;
        leftMost = pow( 2,leftMost-1 ) - 1 ;
        // cout << leftMost << endl ;
        cout << "leftmost bottom: [" << maxHeap[leftMost].index<< "] " << maxHeap[leftMost].student << endl ;
        // cout << "leftmost+1 bottom: [" << maxHeap[leftMost+1].index<< "] " << maxHeap[leftMost+1].student << endl << endl ;
    } // PrintMaxHeap()

    void PrintDeap() {
        cout << "<DEAP>" << endl ;
        cout << "root: [" << deap[0].index<< "] " << deap[0].student << endl ;
        cout << "rightmost bottom: [" << deap[2].index<< "] " << deap[2].student << endl ;
        cout << "leftmost bottom: [" << deap[1].index<< "] " << deap[1].student << endl ;
    }
} ; // OutStandingMove

int main() {
    int command = 0 ;
    bool continueOrNot = false ;
    OutStandingMove function1 ;
    OutStandingMove function2 ;

    do {
        cout << "*****************************************" << endl ; // welcome message
        cout << "***** Max Heap & Deap               *****" << endl ;
        cout << "***** 0 : Quit                      *****" << endl ;
        cout << "***** 1 : Build a Max Heap          *****" << endl ;
        cout << "***** 2 : Build a Deap              *****" << endl ;
        cout << "*****************************************" << endl ;
        cout << endl << "Please enter your choice :" << endl ;

        cin >> command ; // read in user command

        if ( command == 0 ) { // bye :(((
            cout << "Bye :(((" << endl ;
            return 0 ;
        } // quit

        else if ( command > 2 || command < 0 ) { // wrong command
            cout << "Error command! please enter an acceptable command :" << endl << endl ;
            continueOrNot = true ;
        } // wrong command

        else if ( command == 1 ) { // function 1
            bool function1Confirm = false ;

            do {
                cout << "Please enter the file you want to build a MaxHeap or [0] to quit:" << endl ;
                cin >> FileN ;

                if ( FileN == "0" ) {
                    function1Confirm = true ;
                    continueOrNot = true ;
                } // quit

                else {
                    string fileName = "input" + FileN + ".txt" ;
                    input.open( fileName.c_str() ) ;
                    // cut the input FileN, try to open
                    if ( input.is_open() ) {
                        function1.InputData(1) ;
                        //function1.MaxHeap() ;
                        function1.PrintMaxHeap() ; // print
                        input.close() ;
                        output.close() ;
                        function1Confirm = true ;
                        continueOrNot = true ;
                    } // successfully opened
                    else cout << "*****  " << fileName << " does not exist!  *****" << endl ; // no file
                } // open and sort
            } while( ! function1Confirm ) ;

            Count = 0 ;
            FileN = "0" ;
        } // mission 1: Select & Bubble Sort

        else if ( command == 2 ) { // function 2
            bool function2Confirm = false ;

            do {
                cout << "Please enter the file you want to buid a Deap or [0] to quit:" << endl ;
                cin >> FileN ;

                if ( FileN == "0" ) {
                    function2Confirm = true ;
                    continueOrNot = true ;
                } // quit

                else {
                    string fileName = "input" + FileN + ".txt" ;
                    input.open( fileName.c_str() ) ;
                    // cut the input FileN, try to open
                    if ( input.is_open() ) {
                        function2.InputData(2) ;
                        function2.PrintDeap() ;
                        input.close() ;
                        output.close() ;
                        function2Confirm = true ;
                        continueOrNot = true ;
                    } // successfully opened
                    else cout << "*****  " << fileName << " does not exist!  *****" << endl ; // no file
                } // open and sort
            } while( ! function2Confirm ) ;

            Count = 0 ;
            FileN = "0" ;
        } // mission 2: Merge & Quick Sort
    } while( continueOrNot ) ;
} // main function
