#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
private:
    vector<double> arr;
    int n;

public:
    MaxHeap() {
        n = 0;
    }

    int N(){
        return n;
    }
    // returns the index of the parent node
    static int parent(int i) {
        return (i - 1) / 2;
    }

    // return the index of the left child 
    static int leftChild(int i) {
        return 2*i + 1;
    }

    // return the index of the right child 
    static int rightChild(int i) {
        return 2*i + 2;
    }

    // insert the item at the appropriate position
    void insertNode(double data) {

        // first insert the time at the last position of the array 
        // and move it up
        arr.push_back(data);
        n = n + 1;


        // move up until the heap property satisfies
        int i = n - 1;
        while (i != 0 && arr[parent(i)] < arr[i]) {
            swap(arr[parent(i)], arr[i]);
            i = parent(i);
        }
    }

    // moves the item at position i of array a
    // into its appropriate position
    void heapify(int i){
        // find left child node
        int left = leftChild(i);

        // find right child node
        int right = rightChild(i);

        // find the largest among 3 nodes
        int largest = i;

        // check if the left node is larger than the current node
        if (left <= n && arr[left] > arr[largest]) {
            largest = left;
        }

        // check if the right node is larger than the current node 
        // and left node
        if (right <= n && arr[right] > arr[largest]) {
            largest = right;
        }

        // swap the largest node with the current node 
        // and repeat this process until the current node is larger than 
        // the right and the left node
        if (largest != i) {
            swap(arr[i],arr[largest]);
            heapify(largest);
        }
    }

    // deletes the max item and return
    double deleteRoot() {
        double root = arr[0];

        // replace the first item with the last item
        arr[0] = arr[n - 1];
        n = n - 1;

        // maintain the heap property by heapifying the 
        // first item
        heapify(0);
        return root;
    }
};

class MinHeap {
private:
    vector<double> arr;
    int n;

public:
    MinHeap() {
        n = 0;
    }

    int N(){
        return n;
    }
    // returns the index of the parent node
    static int parent(int i) {
        return (i - 1) / 2;
    }

    // return the index of the left child 
    static int leftChild(int i) {
        return 2*i + 1;
    }

    // return the index of the right child 
    static int rightChild(int i) {
        return 2*i + 2;
    }

    // insert the item at the appropriate position
    void insertNode(double data) {

        // first insert the time at the last position of the array 
        // and move it up
        arr.push_back(data);
        n = n + 1;


        // move up until the heap property satisfies
        int i = n - 1;
        while (i != 0 && arr[parent(i)] > arr[i]) {
            swap(arr[parent(i)], arr[i]);
            i = parent(i);
        }
    }

    // moves the item at position i of array a
    // into its appropriate position
    void heapify(int i){
        // find left child node
        int left = leftChild(i);

        // find right child node
        int right = rightChild(i);

        // find the largest among 3 nodes
        int smallest = i;

        // check if the left node is larger than the current node
        if (left <= n && arr[left] < arr[smallest]) {
            smallest = left;
        }

        // check if the right node is larger than the current node 
        // and left node
        if (right <= n && arr[right] < arr[smallest]) {
            smallest = right;
        }

        // swap the largest node with the current node 
        // and repeat this process until the current node is larger than 
        // the right and the left node
        if (smallest != i) {
            swap(arr[i],arr[smallest]);
            heapify(smallest);
        }
    }

    // deletes the max item and return
    double deleteRoot() {
        double root = arr[0];

        // replace the first item with the last item
        arr[0] = arr[n - 1];
        n = n - 1;

        // maintain the heap property by heapifying the 
        // first item
        heapify(0);
        return root;
    }
};