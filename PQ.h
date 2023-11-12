#ifndef PQ_H
#define PQ_H

#include "dsexceptions.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "AvlTree.h"
#include "BinaryHeap.h"

// PQ class
//
// Template parameter: ID
// Constructors:
// PQ --> constructs a new empty queue
// PQ( tasks, priorities ) --> constructs a new queue with a given set of task IDs and priorities 
// ******************PUBLIC OPERATIONS*********************
// void insert( x, p )       --> Insert task ID x with priority p 
// ID findMin( )  --> Return a task ID with smallest priority, without removing it 
// ID deleteMin( )   --> Remove and return a task ID with smallest priority 
// void updatePriority( x, p )   --> Changes priority of ID x to p (if x not in PQ, inserts x);
// bool isEmpty( )   --> Return true if empty; else false
// int size() --> return the number of task IDs in the queue 
// void makeEmpty( )  --> Remove all task IDs (and their priorities)
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename ID>
// ID is the type of task IDs to be used; the type must be Comparable (i.e., have < defined), so IDs can be AVL Tree keys.
class PQ
{

  public:

    // Constructor
    // Initializes a new empty PQ
    PQ() {
      currentSize = 0;
      capacity = 100;
    }
  
    // Constructor
    // Initializes a new PQ with a given set of tasks IDs and priorities  
    //      priority[i] is the priority for ID task[i] 
    PQ( const std::vector<ID> & tasks, const std::vector<int> & priorities ) {
      currentSize = tasks.size();
      capacity = 100 + tasks.size();
      vector<int> priority_arr = BH.get_priorityArray();
      priority_arr.resize(capacity);
      for (int i = 0; i < currentSize; i++){
        priority_arr[i] = priorities[i];
        AVL.insert(tasks[i]);
      }
      BH.makeHeap();
    }; 
						     
    // Emptiness check 
    bool isEmpty( ) const {
      return (currentSize == 0);
    }

    // Deletes and Returns a task ID with minimum priority
    //    Throws exception if queue is empty
    const ID & deleteMin(){
      if (isEmpty()){
        throw UnderflowException{};
      } else {
        return deleteMin_private();
      }
    }

    // Returns an ID with minimum priority without removing it
    //     Throws exception if queue is empty
    const ID & findMin() {
      if (isEmpty()) {
        throw UnderflowException{ };
      } else {
        return findMin_private();
      }
    }


    // Insert ID x with priority p.
    void insert( const ID & x, int p ) {
      return insert_private(x, p);
    }

    // Update the priority of ID x to p
    //    Inserts x with p if s not already in the queue
    void updatePriority( const ID & x, int p ) {
      updatePriority_private(x, p);
    }

    // Return the number of task IDs in the queue
    int size() const { 
      return currentSize;
    }

    // Delete all IDs from the PQ
    void makeEmpty( ) {
      BH.makeEmpty();
      AVL.makeEmpty();
      currentSize = 0;
      return;
    }

    // print content in PQ
    void printPQ(){
      printPQ_private();
    }

  private:

    int currentSize;
    int capacity;
    BinaryHeap<int> BH;
    AvlTree<ID> AVL;

    void printPQ_private(){
      cout << "currentSize: " << currentSize << endl;
      cout << "capacity: " << capacity << endl;
      BH.printArrays();
      cout << "AvlTree: " << endl;
      AVL.printTree(); 
    }

    void insert_private( const ID & x, int p ) {
      BH.insert(p, x);
      BH.makeHeap();
      AVL.makeEmpty();
      for (int i = 0; i < currentSize; i++){
        AVL.insert(BH.get_taskID()[i], i);
      } 
      currentSize++;
      return;
    }

    const ID & findMin_private() {
      return BH.get_taskID()[0];
    }

    const ID & deleteMin_private() {
      ID min_ID = BH.extractMin();
      ID* min_ID_ptr = &min_ID;
      AVL.makeEmpty();
      for (int i = 0; i < currentSize; i++){
        AVL.insert(BH.get_taskID()[i], i);
      }    
      currentSize--;
      return *min_ID_ptr;
    }

    void updatePriority_private(const ID & x, int p){
      bool inArray;
      int index = 0;
      vector<ID> idArray = BH.get_taskID();
      for (int i = currentSize - 1; i > -1; i--){
        if (idArray[i] == x){ 
          inArray = true;
          index = i;
        }
      }
      if (!inArray || index == 0){
        cout << "ID " << x << " doesn't exist, adding it" << endl;
        insert_private(x,p);
      } else {
        cout << "ID exists, updating its priority at" << "priority_array[" << index << "]"<< endl;
        BH.get_priorityArray()[index] = p;
        cout << "ID " << x <<" has new priority: " <<  BH.get_priorityArray()[index] << endl;
        BH.makeHeap();
      }
    return;
  }
};

#endif
