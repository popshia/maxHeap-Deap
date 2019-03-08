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
static int Count = 1 ;
static int Command = 0 ;

class OutStandingMove {
    DataStruct tempData ;
    int layer = 0 ;
    int opposite = 0 ;
    int leftCorner = 0 ;

public:
    vector<DataStruct> maxHeap ;
    vector<DataStruct> deap ;

    void InputData( int function ) { // tool
        maxHeap.clear() ;
        deap.clear() ;
        tempData.student = 0 ;
        tempData.index = 0 ;
        string sentence = "\0" ;
        getline( input, sentence ) ;
        getline( input, sentence ) ;
        getline( input, sentence ) ;

        if ( function == 2 ) deap.insert( deap.begin(), tempData ) ;

        while ( getline( input, sentence ) ) {
            // cout << sentence << endl ;
            layer = (int)floor(log2(Count+1)) ;
            opposite = (int)exp2(layer-1) ;
            leftCorner = opposite*3 - 1 ;
            tempData.index = Count ;
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
                MaxHeap( maxHeap ) ;
            } // function 1

            if ( function == 2 ) {
                deap.push_back( tempData ) ;
                Deap( deap, Count, leftCorner ) ;
            } // function 2

            Count++ ;
        } // get the whole file
    } // InputData()

    void MaxHeapify( vector<DataStruct> & data, int child ) {
        int root ;
        if ( Command == 1 ) root = child / 2 ; // 取得root
        else root = ( child-1 ) / 2 ;
        int largest = root ; // largest用來記錄包含root與child, 三者之中Key最大的node

        if ( root >= 1 && data[child].student > data[root].student )
            largest = child ;

        if ( largest != root ) { // 如果目前root的Key不是三者中的最大
            swap( data[largest], data[root] ) ; // 就調換root與三者中Key最大的node之位置
            MaxHeapify( data, root ) ; // 調整新的subtree成Max Heap
        } // if()
    } // MaxHeapify()

    void MinHeapify( vector<DataStruct> & data, int child ) {
        int root ;
        if ( Command == 1 ) root = child / 2 ; // 取得root
        else root = ( child-1 ) / 2 ;
        int smallest = root ; // largest用來記錄包含root與child, 三者之中Key最大的node

        if ( root >= 1 && data[child].student < data[root].student )
            smallest = child ;

        if ( smallest != root ) { // 如果目前root的Key不是三者中的最大
            swap( data[smallest], data[root] ) ; // 就調換root與三者中Key最大的node之位置
            MinHeapify( data, root ) ; // 調整新的subtree成Max Heap
        } // if()
    } // MaxHeapify()

    void MaxHeap( vector<DataStruct> & data ) {
        DataStruct emptyRoot ;
        data.insert( data.begin(), emptyRoot ) ;
        MaxHeapify( data, (int)data.size() - 1 ) ;
        data.erase( data.begin() ) ; // 將index(0)刪除
    } // MaxHeap()

    void Deap( vector<DataStruct> & data, int count, int leftCorner ) {
        if ( count < leftCorner ) MinHeapify( data, (int)data.size() - 1 ) ;
        else MaxHeapify( data,(int)data.size() - 1 ) ;
    } // Deap()

    void CompareAndRebuild() {
    }

    void Print( vector<DataStruct> data ) {
        for ( int i = 0 ; i < data.size() ; i ++ ) cout << data[i].index << " " << data[i].student << endl ;
        if ( Command == 1 ) {
            cout << "<MAX HEAP>" << endl ;
            cout << "root: [" << data.front().index<< "] " << data.front().student << endl ;
        } // function 1
        else cout << "<DEAP>" << endl ;
        cout << "rightmost bottom: [" << data.back().index<< "] " << data.back().student << endl ;
        int leftMost = 0 ;
        for ( int i = 1 ; i < data.size() ; leftMost++ ) i *= 2;
        leftMost = pow( 2,leftMost-1 ) - 1 ;
        // cout << leftMost << endl ;
        cout << "leftmost bottom: [" << data[leftMost].index<< "] " << data[leftMost].student << endl ;
        // cout << "leftmost+1 bottom: [" << maxHeap[leftMost+1].index<< "] " << maxHeap[leftMost+1].student << endl << endl ;
    } // PrintMaxHeap()
} ; // OutStandingMove

int main() {
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

        cin >> Command ; // read in user command

        if ( Command == 0 ) { // bye :(((
            cout << "Bye :(((" << endl ;
            return 0 ;
        } // quit

        else if ( Command > 2 || Command < 0 ) { // wrong command
            cout << "Error command! please enter an acceptable command :" << endl << endl ;
            continueOrNot = true ;
        } // wrong command

        else if ( Command == 1 ) { // function 1
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
                        function1.InputData(Command) ;
                        //function1.MaxHeap() ;
                        function1.Print( function1.maxHeap ) ; // print
                        input.close() ;
                        output.close() ;
                        function1Confirm = true ;
                        continueOrNot = true ;
                    } // successfully opened
                    else cout << "*****  " << fileName << " does not exist!  *****" << endl ; // no file
                } // open and sort
            } while( ! function1Confirm ) ;

            Count = 1 ;
            FileN = "0" ;
        } // mission 1: Select & Bubble Sort

        else if ( Command == 2 ) { // function 2
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
                        function2.InputData(Command) ;
                        function2.Print( function2.deap ) ;
                        input.close() ;
                        output.close() ;
                        function2Confirm = true ;
                        continueOrNot = true ;
                    } // successfully opened
                    else cout << "*****  " << fileName << " does not exist!  *****" << endl ; // no file
                } // open and sort
            } while( ! function2Confirm ) ;

            Count = 1 ;
            FileN = "0" ;
        } // mission 2: Merge & Quick Sort
    } while( continueOrNot ) ;
} // main function
