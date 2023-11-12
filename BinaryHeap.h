#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "dsexceptions.h"
#include "math.h"
#include <vector>
#include <iostream> 
using namespace std;

template <typename ID>

class BinaryHeap {

    public: 

        BinaryHeap(){
            currentSize = 0;
            capacity = 100;
            priority_array.resize(capacity);
            //ptr_array.resize(capacity);
            taskID_list.resize(capacity);
        }

        BinaryHeap(const vector<int> & items) {
            currentSize = items.size();
            capacity = 100 + items.size();
            priority_array.resize(items.size());
            //ptr_array.resize(items.size());
            taskID_list.resize(items.size());
            for (long long unsigned int i = 0; i < items.size(); i++){
                priority_array[i] = items[i];
                //ptr_array[i] = i;
            }
        }

        bool isEmpty(){
            return currentSize == 0;
        }

        void makeEmpty(){
            return makeEmpty_private();
        }

        void makeHeap(){ 
            makeHeap_private();
        }

        int insert(ID & y, const ID & x) {
            int heap_index = insert_private(y, x);
            return heap_index;
        }

        ID & extractMin(){
            if (isEmpty()) {
                throw UnderflowException{};
            }
            return extractMin_private();
        }

        void printArrays() {
            printArrays_private();
        }

        vector<ID> & get_priorityArray(){
            return return_pirorityArray();
        }
/*
        vector<int> & get_ptrArray(){
            return return_ptrArray();
        }

*/
        vector<ID> & get_taskID(){
            return return_taskIDlist();
        }

    
    private: 

        int currentSize;
        int capacity;
        vector<ID> priority_array;
        // vector<int> ptr_array;
        vector<ID> taskID_list;

        void makeHeap_private() {
            for (double i = floor(currentSize/2)-1; i > 0; i--){
                // percolate down
                int k = 0;
                while (2*k + 1 < currentSize){
                    int child; 
                    child = 2*k+1;
                    if (2*k+2 < currentSize && priority_array[2*k+2] < priority_array[2*k+1]){
                        child = 2*k+2;
                    }
                    if (priority_array[child] < priority_array[k]){

                        int temp = priority_array[child];
                        priority_array[child] = priority_array[k];
                        priority_array[k] = temp;

                        temp = taskID_list[child];
                        taskID_list[child] = taskID_list[k];
                        taskID_list[k] = temp;

                        k = child;

                    } else {
                        return;
                    }
                }                
            }
            return;
        }

        ID insert_private(ID & y, const ID & k){

            if( currentSize == capacity ){
                capacity = priority_array.size() * 2;
                priority_array.resize( capacity );
                //ptr_array.resize( capacity );
            }

            priority_array[currentSize] = y;
            //ptr_array[currentSize] = currentSize;
            taskID_list[currentSize] = k;
            // percolate up
            int v = currentSize;
            double p = floor((v-1)/2);
            while (v > 0 && priority_array[v] < priority_array[p]){

                int temp = priority_array[v];
                priority_array[v] = priority_array[p];
                priority_array[p] = temp;

                temp = taskID_list[v];
                taskID_list[v] = taskID_list[p];
                taskID_list[p] = temp;

                v = p;
                p = floor((v-1)/2);
            }
            currentSize = currentSize + 1;
            return v;
        }

        ID & extractMin_private() {
            int temp = priority_array[0];
            ID temp_id = taskID_list[0];
            currentSize = currentSize - 1;
            priority_array[0] = priority_array[currentSize];
            priority_array[currentSize + 1] = temp;
            taskID_list[0] = taskID_list[currentSize];
            taskID_list[currentSize + 1] = temp_id;
            // percolate down
            int k = 0;
            while (2*k+1 < currentSize){
                int child;
                child = 2*k+1;
                if (2*k+2 < currentSize && priority_array[2*k+2] < priority_array[2*k+1]) {
                    child = 2*k+2;
                }
                if (priority_array[child] < priority_array[k]){

                    int temp = priority_array[child];
                    priority_array[child] = priority_array[k];

                    priority_array[k] = temp;
                    temp = taskID_list[child];
                    taskID_list[child] = taskID_list[k];
                    taskID_list[k] = temp;

                    k = child;
                } else {
                    return taskID_list[currentSize + 1];               
                }
            }
            return taskID_list[currentSize + 1];
        }

        void printArrays_private(){

            cout << "Priority_array: <" ;
            for (int i = 0; i < currentSize; i++){
                cout << priority_array[i]  << ", ";
            }   
            cout << ">" << endl;
/*
            cout << "ptr_array: <" ;
            for (int i = 0; i < currentSize; i++){
                cout <<  ptr_array[i]  << ", ";
            }
            cout << ">" << endl;
*/
            cout << "taskID_list: <" ;
            for (int i = 0; i < currentSize; i++){
                cout <<  taskID_list[i]  << ", ";
            }
            cout << ">" << endl;
            return;
        }

        vector<ID> & return_pirorityArray(){
            return priority_array;
        }
/*
        vector<int> & return_ptrArray(){
            return ptr_array;
        }
*/
        vector<ID> & return_taskIDlist() {
            return taskID_list;
        }

        void makeEmpty_private(){
            currentSize = 0;
        }

};

#endif