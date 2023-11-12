#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "PQ.h"

int main(){

    PQ<int> test;
    test.printPQ();

    cout << "----------------------------------------------------------- inserting ------------------------------------------------------------" << endl;

    for (int i = 1; i < 11; i++){
        test.insert(i, i+30);
    }
    test.printPQ();

    cout << "----------------------------------------------------------- find min ------------------------------------------------------------" << endl;

    const int & found_min = test.findMin();
    cout << "find_min() returned: " << found_min << endl;

    cout << "----------------------------------------------------------- delete min ------------------------------------------------------------" << endl;
    
    int deleted_min = test.deleteMin();
    cout << "1st delete_min() returned: " << deleted_min << endl;
    cout << "After 1st delete_min(), the BH & Avltree look like: " << endl;
    test.printPQ();
    deleted_min = test.deleteMin();
    cout << "2nd delete_min() returned: " << deleted_min << endl;
    cout << "After 2nd delete_min(), the BH & Avltree look like: " << endl;
    test.printPQ();

    cout << "----------------------------------------------------------- update priority ------------------------------------------------------------" << endl;

    for (int i = 20; i < 25; i++){
        test.insert(i, i-19);     
    }
    cout << "Before updating the new priorities, the BH & Avltree look like: " << endl;
    test.printPQ();

    for (int i = 20; i < 25; i++){
        test.updatePriority(i, i-10);
    }
    cout << "After updating the new priorities, the BH & Avltree look like: " << endl;
    test.printPQ();

    cout << "----------------------------------------------------------- make empty ------------------------------------------------------------" << endl;

    test.makeEmpty();
    cout << "After makeEmpty(), the BH & Avltree look like: " << endl;
    test.printPQ();

    

    return 0;
}