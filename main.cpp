#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

struct Household {
    string datetime;
    float gap;
    float grp;
    float v;
    float gi;
};

class MaxHeap {
    public:
        vector<float> arr;
        // Function to insert a new node to the Heap
        void insertNode(float Key){
            // Increase the size of Heap by 1
            n = n + 1;
            // Insert the element at end of Heap
            arr[n - 1] = Key;
            // Heapify the new node following a
            // Bottom-up approach
            heapify(n, n - 1);
        }
        float deleteRoot(){
            float root = arr[0];
            // Get the last element
            float lastElement = arr[n - 1];
            // Replace root with last element
            arr[0] = lastElement;
            // Decrease size of heap by 1
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
        vector<float> arr;
        // Function to insert a new node to the Heap
        void insertNode(float Key){
            // Increase the size of Heap by 1
            n = n + 1;
            // Insert the element at end of Heap
            arr[n - 1] = Key;
            // Heapify the new node following a
            // Bottom-up approach
            heapify(n, n - 1);
        }
        float deleteRoot()
        {
            float root = arr[0];
            // Get the last element
            float lastElement = arr[n - 1];
            // Replace root with last element
            arr[0] = lastElement;
            // Decrease size of heap by 1
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
                if (arr[i] < arr[parent]) {
                    swap(arr[i], arr[parent]);
                    // Recursively heapify the parent node
                    heapify(n, parent);
                }
            }
        }   
};

class Handler {
	public:
        string selected_column;
		vector<string> features;
        
        void add_data(stringstream &s){
            Household data;
            string buffer;
            string datebuff;
            string timebuff;

            getline(s, datebuff, ',');
            getline(s, timebuff, ',');
            string fulldate = datebuff + "," + timebuff;

            if (start_date.empty()){
                start_date = fulldate;
            }
            stop_date = fulldate;

            getline(s, buffer, ',');
            data.gap = stof(buffer);

            if (selected_column == "gap"){
                summ+= data.gap;
                if (data.gap < minn){
                    minn = data.gap;
                }
                if (data.gap > maxx){
                    maxx = data.gap;
                }
            }

            getline(s, buffer, ',');
            data.grp = stof(buffer);

            if (selected_column == "grp"){
                summ+= data.grp;
                if (data.grp < minn){
                    minn = data.grp;
                }
                if (data.grp > maxx){
                    maxx = data.grp;
                }
            }

            getline(s, buffer, ',');
            data.v = stof(buffer);

            if (selected_column == "v"){
                summ+= data.v;
                if (data.v < minn){
                    minn = data.v;
                }
                if (data.v > maxx){
                    maxx = data.v;
                }
            }

            getline(s, buffer);
            data.gi = stof(buffer);

            if (selected_column == "gi"){
                summ+= data.gi;
                if (data.gi < minn){
                    minn = data.gi;
                }
                if (data.gi > maxx){
                    maxx = data.gi;
                }
            }

            array.push_back(data);

            mean = summ / array.size();



        }

        // float get_firstq(){

        // }

        float get_median(){


        }

        // float get_thirdq(){
            
        // }

        float get_mean(){
            return mean;
        }

        float get_max(){
            return maxx;
        }

        float get_min(){
            return minn;
        }

        float get_sum(){
            return summ;
        }

        float get_std(){
            float std;
            float sum;
            for (int i = 0; i < array.size(); i++){
                if (selected_column == "gap"){
                    sum += (array[i].gap - mean);

                }
                if (selected_column == "grp"){
                    sum += (array[i].grp - mean);
                }
                if (selected_column == "v"){
                    sum += (array[i].v - mean);
                }
                if (selected_column == "gi"){
                    sum += (array[i].gi - mean);
                }
            }
            return sqrt(sum / array.size());
        }


    private:
        vector<Household> array;

        MinHeap firstq_min_heap;
        MaxHeap firstq_max_heap;

        MinHeap median_min_heap;
        MaxHeap median_max_heap;
        
        MinHeap thirdq_min_heap;
        MaxHeap thirdq_max_heap;

        float firstq;
        float median;
        float thirdq;

        float minn;
        float maxx;
        float mean = 0;
        float summ = 0;
        string start_date;
        string stop_date;

        void processHeaps(float &key){
            if (median_min_heap.N() == 0){

                firstq_min_heap.insertNode(key);

                firstq = key;

                median_min_heap.insertNode(key);
                median = key;

                thirdq_min_heap.insertNode(key);
                thirdq = key;
                return;

            } else if (median_min_heap.N() == 1 & median_max_heap.N() == 0){

                firstq_min_heap.insertNode(key);
                median_min_heap.insertNode(key);
                thirdq_min_heap.insertNode(key);

                if(median_min_heap.arr[0] > median_max_heap.arr[0]){
                    swap(firstq_min_heap.arr[0], firstq_max_heap.arr[0]);
                    swap(median_min_heap.arr[0], median_max_heap.arr[0]);
                    swap(thirdq_min_heap.arr[0], thirdq_max_heap.arr[0]);
                }

                firstq = (firstq_min_heap.arr[0] + firstq_max_heap.arr[0]) / 2;
                median = (median_min_heap.arr[0] + median_max_heap.arr[0]) / 2;
                thirdq = (thirdq_min_heap.arr[0] + thirdq_max_heap.arr[0]) / 2;
                return;
            }

            // process median

            if(key > median){
                median_max_heap.insertNode(key);
            } else if (key == median){
                if(median_min_heap.N() < median_max_heap.N()){
                    median_min_heap.insertNode(key);
                } else {
                    median_max_heap.insertNode(key);
                }
            } else {
                median_min_heap.insertNode(key);
            }
            // check size and set median accordingly
            if (median_min_heap.N() > median_max_heap.N() + 1){
                float root = median_min_heap.deleteRoot();
                median_max_heap.insertNode(root);
                median = (median_min_heap.arr[0] + median_max_heap.arr[0]) / 2;
            } else if (median_max_heap.N() > median_min_heap.N() + 1){
                float root = median_max_heap.deleteRoot();
                median_min_heap.insertNode(root);
                median = (median_min_heap.arr[0] + median_max_heap.arr[0]) / 2;
            } else if (median_min_heap.N() == median_max_heap.N()) {
                median = (median_min_heap.arr[0] + median_max_heap.arr[0]) / 2;
            } else if (median_min_heap.N() == (median_max_heap.N() + 1)){
                median = median_min_heap.arr[0];
            } else {
                median = median_max_heap.arr[0];
            }

            if(key > firstq){
                median_max_heap.insertNode(key);
            } else if (key == firstq){
                if(median_min_heap.N() < median_max_heap.N()){
                    median_min_heap.insertNode(key);
                } else {
                    median_max_heap.insertNode(key);
                }
            } else {
                median_min_heap.insertNode(key);
            }
            // check size and set median accordingly
            if (median_min_heap.N() > median_max_heap.N() + 1){
                float root = median_min_heap.deleteRoot();
                median_max_heap.insertNode(root);
                median = (median_min_heap.arr[0] + median_max_heap.arr[0]) / 2;
            } else if (median_max_heap.N() > median_min_heap.N() + 1){
                float root = median_max_heap.deleteRoot();
                median_min_heap.insertNode(root);
                median = (median_min_heap.arr[0] + median_max_heap.arr[0]) / 2;
            } else if (median_min_heap.N() == median_max_heap.N()) {
                median = (median_min_heap.arr[0] + median_max_heap.arr[0]) / 2;
            } else if (median_min_heap.N() == (median_max_heap.N() + 1)){
                median = median_min_heap.arr[0];
            } else {
                median = median_max_heap.arr[0];
            }

        }

        vector<float> returnDataArray(){
            vector<float> data_array;
            for (int i = 0; i < array.size(); i++){
                if (selected_column == "gap"){
                    data_array[i] = array[i].gap;
                }
                if (selected_column == "grp"){
                    data_array[i] = array[i].grp;
                }
                if (selected_column == "v"){
                    data_array[i] = array[i].v;
                }
                if (selected_column == "gi"){
                    data_array[i] = array[i].gi;
                }
            }
            return data_array;
        }
};

int main(int argc, char ** argv) {
    // string filename = argv[1];
	string filename = "input1.txt";
    string temp;
    int feature_count;
    int line_count;
    fstream file;
    Handler handler;

    file.open(filename, ios::in);
    getline(file, temp);
    feature_count = stoi(temp);
    for (int i = 0; i < feature_count; i++) {
        getline(file, temp);
        handler.features.push_back(temp);
    }

    getline(file, temp);
    stringstream s(temp);
    getline(s, temp, ',');
    line_count = stoi(temp);
    getline(s, temp);
    handler.selected_column = temp;

    for (int i = 0; i < line_count; i++) {
        getline(file, temp);
        if(temp == "add"){
            getline(file, temp);
            stringstream s(temp);
            handler.add_data(s);
        }
    }
    return 0;
}