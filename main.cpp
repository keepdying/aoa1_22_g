#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

struct Household {
    string datetime;
    double gap;
    double grp;
    double v;
    double gi;
};

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
        string start_date;
        string stop_date;
        
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
            data.gap = stod(buffer);

            if (selected_column == "gap"){
                summ+= data.gap;
                if (data.gap < minn){
                    minn = data.gap;
                }
                if (data.gap > maxx){
                    maxx = data.gap;
                }
                processHeaps(data.gap);
            }

            getline(s, buffer, ',');
            data.grp = stod(buffer);

            if (selected_column == "grp"){
                summ+= data.grp;
                if (data.grp < minn){
                    minn = data.grp;
                }
                if (data.grp > maxx){
                    maxx = data.grp;
                }
                processHeaps(data.grp);
            }

            getline(s, buffer, ',');
            data.v = stod(buffer);

            if (selected_column == "v"){
                summ+= data.v;
                if (data.v < minn){
                    minn = data.v;
                }
                if (data.v > maxx){
                    maxx = data.v;
                }
                processHeaps(data.v);
            }

            getline(s, buffer);
            data.gi = stod(buffer);

            if (selected_column == "gi"){
                summ+= data.gi;
                if (data.gi < minn){
                    minn = data.gi;
                }
                if (data.gi > maxx){
                    maxx = data.gi;
                }
                processHeaps(data.gi);
            }

            array.push_back(data);

            mean = summ / array.size();



        }

        double get_firstq(){
            return firstq;
        }

        double get_median(){
            return median;
        }

        double get_thirdq(){
            return thirdq;
        }

        double get_mean(){
            return mean;
        }

        double get_max(){
            return maxx;
        }

        double get_min(){
            return minn;
        }

        double get_sum(){
            return summ;
        }

        double get_std(){
            double std;
            double sum;
            for (int i = 0; i < array.size(); i++){
                if (selected_column == "gap"){
                    sum += (array[i].gap - mean) * (array[i].gap - mean);

                }
                if (selected_column == "grp"){
                    sum += (array[i].grp - mean) * (array[i].grp - mean) ;
                }
                if (selected_column == "v"){
                    sum += (array[i].v - mean) * (array[i].v - mean);
                }
                if (selected_column == "gi"){
                    sum += (array[i].gi - mean) * (array[i].gi - mean);
                }
            }
            sum = sum / double(array.size());
            std = sqrt(sum);
            return std;
        }


    private:
        vector<Household> array;

        MinHeap firstq_min_heap;
        MaxHeap firstq_max_heap;

        MinHeap median_min_heap;
        MaxHeap median_max_heap;
        
        MinHeap thirdq_min_heap;
        MaxHeap thirdq_max_heap;

        double firstq;
        double median;
        double thirdq;

        double minn = INT64_MAX;
        double maxx;
        double mean = 0;
        double summ = 0;

        void processHeaps(double &key){
            if (median_min_heap.N() == 0){

                firstq_min_heap.insertNode(key);
                firstq = key;

                median_min_heap.insertNode(key);
                median = key;

                thirdq_min_heap.insertNode(key);
                thirdq = key;
                return;

            } else if (median_min_heap.N() == 1 and median_max_heap.N() == 0){

                firstq_max_heap.insertNode(key);
                median_max_heap.insertNode(key);
                thirdq_max_heap.insertNode(key);

                if(median_min_heap.arr[0] > median_max_heap.arr[0]){
                    swap(firstq_min_heap.arr[0], firstq_max_heap.arr[0]);
                    swap(median_min_heap.arr[0], median_max_heap.arr[0]);
                    swap(thirdq_min_heap.arr[0], thirdq_max_heap.arr[0]);
                }

                firstq = (firstq_min_heap.arr[0] + firstq_max_heap.arr[0]) / double(2);
                median = (median_min_heap.arr[0] + median_max_heap.arr[0]) / double(2);
                thirdq = (thirdq_min_heap.arr[0] + thirdq_max_heap.arr[0]) / double(2);
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
                double root = median_min_heap.deleteRoot();
                median_max_heap.insertNode(root);
                median = (median_min_heap.arr[0] + median_max_heap.arr[0]) / double(2);
            } else if (median_max_heap.N() > median_min_heap.N() + 1){
                double root = median_max_heap.deleteRoot();
                median_min_heap.insertNode(root);
                median = (median_min_heap.arr[0] + median_max_heap.arr[0]) / double(2);
            } else if (median_min_heap.N() == median_max_heap.N()) {
                median = (median_min_heap.arr[0] + median_max_heap.arr[0]) / double(2);
            } else if (median_min_heap.N() == (median_max_heap.N() + 1)){
                median = median_min_heap.arr[0];
            } else {
                median = median_max_heap.arr[0];
            }

            if(key > firstq){
                firstq_max_heap.insertNode(key);
            } else if (key == firstq){
                if(3 * firstq_min_heap.N() < firstq_max_heap.N()){
                    firstq_min_heap.insertNode(key);
                } else {
                    firstq_max_heap.insertNode(key);
                }
            } else {
                firstq_min_heap.insertNode(key);
            }
            // check size and set firstq accordingly
            if (3 * firstq_min_heap.N() > firstq_max_heap.N() + 1){
                double root = firstq_min_heap.deleteRoot();
                firstq_max_heap.insertNode(root);
                firstq = (firstq_min_heap.arr[0] + firstq_max_heap.arr[0]) / double(2);
            } else if (firstq_max_heap.N() > 3 * firstq_min_heap.N() + 1){
                double root = firstq_max_heap.deleteRoot();
                firstq_min_heap.insertNode(root);
                firstq = (firstq_min_heap.arr[0] + firstq_max_heap.arr[0]) / double(2);
            } else if (3 * firstq_min_heap.N() == firstq_max_heap.N()) {
                firstq = (firstq_min_heap.arr[0] + firstq_max_heap.arr[0]) / double(2);
            } else if (3 * firstq_min_heap.N() == (firstq_max_heap.N() + 1)){
                firstq = firstq_min_heap.arr[0];
            } else {
                firstq = firstq_max_heap.arr[0];
            }

            if(key > thirdq){
                thirdq_max_heap.insertNode(key);
            } else if (key == thirdq){
                if(thirdq_min_heap.N() < 3 * thirdq_max_heap.N()){
                    thirdq_min_heap.insertNode(key);
                } else {
                    thirdq_max_heap.insertNode(key);
                }
            } else {
                thirdq_min_heap.insertNode(key);
            }
            // check size and set thirdq accordingly
            if (thirdq_min_heap.N() > 3 * thirdq_max_heap.N() + 1){
                double root = thirdq_min_heap.deleteRoot();
                thirdq_max_heap.insertNode(root);
                thirdq = (thirdq_min_heap.arr[0] + thirdq_max_heap.arr[0]) / double(2);
            } else if (3 * thirdq_max_heap.N() > thirdq_min_heap.N() + 1){
                double root = thirdq_max_heap.deleteRoot();
                thirdq_min_heap.insertNode(root);
                thirdq = (thirdq_min_heap.arr[0] + thirdq_max_heap.arr[0]) / double(2);
            } else if (thirdq_min_heap.N() == thirdq_max_heap.N()) {
                thirdq = (thirdq_min_heap.arr[0] + thirdq_max_heap.arr[0]) / double(2);
            } else if (thirdq_min_heap.N() == (thirdq_max_heap.N() + 1)){
                thirdq = thirdq_min_heap.arr[0];
            } else {
                thirdq = thirdq_max_heap.arr[0];
            }

        }

        vector<double> returnDataArray(){
            vector<double> data_array;
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
            i++;
            getline(file, temp);
            stringstream s(temp);
            handler.add_data(s);
        } else if(temp == "print"){
            cout << handler.start_date << "," << handler.stop_date << ",";
            for(int i = 0; i < handler.features.size(); i++){

                if (handler.features[i] == "mean"){
                    cout << handler.get_mean();
                } else if (handler.features[i] == "std"){
                    cout << handler.get_std();
                } else if (handler.features[i] == "min"){
                    cout << handler.get_min();
                } else if (handler.features[i] == "firstq"){
                    cout << handler.get_firstq();
                } else if (handler.features[i] == "median"){
                    cout << handler.get_median();
                } else if (handler.features[i] == "thirdq"){
                    cout << handler.get_thirdq();
                } else if (handler.features[i] == "max"){
                    cout << handler.get_max();
                }

                if (i == handler.features.size() - 1){
                    cout << "\n";
                } else {
                    cout << ",";
                }
            }
        }
    }
    return 0;
}