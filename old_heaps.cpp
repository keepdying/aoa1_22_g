#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
    public:
        vector<double> arr;
        // Function to insert a new node to the Heap
        void insertNode(double Key){
            // Increase the size of Heap by 1
            n = n + 1;
            // Insert the element at end of Heap
            arr.push_back(Key);
            // Heapify the new node following a
            // Bottom-up approach
            heapify(n, n - 1);
        }
        double deleteRoot(){
            double root = arr[0];
            // Get the last element
            double lastElement = arr[n - 1];
            // Replace root with last element
            arr[0] = lastElement;
            // Decrease size of heap by 1
            arr.pop_back();
            n = n - 1;
            // heapify the root node
            heapify(n, 0);
            return root;
        }

        int N(){
            return n;
        }

    private:
        int n = 0;
        void heapify(int n, int i){
            // Find parent
            int parent = (i - 1) / 2;
            if (arr[parent] > 0){
                // For Max-Heap
                // If current node is greater than its parent
                // Swap both of them and call heapify again
                // for the parent
                if (arr[i] > arr[parent]) {
                    swap(arr[i], arr[parent]);
                    // Recursively heapify the parent node
                    heapify(n, parent);
                }
            }
        }   
};

class MinHeap {
    public:
        vector<double> arr;
        // Function to insert a new node to the Heap
        void insertNode(double Key){
            // Increase the size of Heap by 1
            n = n + 1;
            // Insert the element at end of Heap
            arr.push_back(Key);
            // Heapify the new node following a
            // Bottom-up approach
            heapify(n, n - 1);
        }
        double deleteRoot()
        {
            double root = arr[0];
            // Get the last element
            double lastElement = arr[n - 1];
            // Replace root with last element
            arr[0] = lastElement;
            // Decrease size of heap by 1
            arr.pop_back();
            n = n - 1;
            // heapify the root node
            heapify(n, 0);
            return root;
        }

        int N(){
            return n;
        }
    private:
        int n = 0;
        void heapify(int n, int i){
            // Find parent
            int parent = (i - 1) / 2;
            if (arr[parent] > 0){
                // For Min-Heap
                // If current node is less than its parent
                // Swap both of them and call heapify again
                // for the parent
                if (arr[i] < arr[parent]) {
                    swap(arr[i], arr[parent]);
                    // Recursively heapify the parent node
                    heapify(n, parent);
                }
            }
        }   
};