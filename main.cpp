#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <regex>

using namespace std;

struct Household {
    string datetime;
    double gap;
    double grp;
    double v;
    double gi;
};

class MaxHeap {
private:
    int n;

public:
    vector<double> arr;
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
        arr.pop_back();
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
    int n;

public:
    vector<double> arr;
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
        arr.pop_back();
        // replace the first item with the last item
        arr[0] = arr[n - 1];
        n = n - 1;

        // maintain the heap property by heapifying the 
        // first item
        heapify(0);
        return root;
    }
};

class Handler { // here is our main handler class
	public:
        string selected_column;
		vector<string> features;
        string start_date;
        string stop_date;
        
        void add_data(stringstream &s){ // add the data and compute istatistics while streaming
            Household data;
            string buffer;
            string datebuff;
            string timebuff;

            getline(s, datebuff, ','); // ahhhh...
            getline(s, timebuff, ',');
            string fulldate = datebuff + "," + timebuff;

            if (start_date.empty()){
                start_date = fulldate;
            }
            stop_date = fulldate;

            getline(s, buffer, ',');
            data.gap = stod(buffer);
            // parse selected column and compute mean min max on the fly.
            if (selected_column == "gap"){
                double welford_X = data.gap;
                double oldM = welford_M;

                mean = (data.gap / double(array.size() + 1)) + (mean * (double(array.size()) / double(array.size() + 1)));
                summ_s1 += data.gap;
                summ_s2 += data.gap * data.gap;

                if (data.gap < minn){
                    minn = data.gap;
                }
                if (data.gap > maxx){
                    maxx = data.gap;
                } // compute firstq, median, and thirdq
                
                if (firstq_enable){
                    processFirstqHeaps(data.gap);
                }
                if (median_enable){
                    processMedianHeaps(data.gap);
                }
                if (thirdq_enable){
                    processThirdqHeaps(data.gap);
                }
            }

            getline(s, buffer, ',');
            data.grp = stod(buffer);

            if (selected_column == "grp"){
                mean = (data.grp / double(array.size() + 1)) + (mean * (double(array.size()) / double(array.size() + 1)));
                summ_s1 += data.grp;
                summ_s2 += data.grp * data.grp;
                if (data.grp < minn){
                    minn = data.grp;
                }
                if (data.grp > maxx){
                    maxx = data.grp;
                } // compute firstq, median, and thirdq
                if (firstq_enable){
                    processFirstqHeaps(data.grp);
                }
                if (median_enable){
                    processMedianHeaps(data.grp);
                }
                if (thirdq_enable){
                    processThirdqHeaps(data.grp);
                }
            }

            getline(s, buffer, ',');
            data.v = stod(buffer);

            if (selected_column == "v"){
                mean = (data.v / double(array.size() + 1)) + (mean * (double(array.size()) / double(array.size() + 1)));
                summ_s1 += data.v;
                summ_s2 += data.v * data.v;

                if (data.v < minn){
                    minn = data.v;
                }
                if (data.v > maxx){
                    maxx = data.v;
                } // compute firstq, median, and thirdq
                if (firstq_enable){
                    processFirstqHeaps(data.v);
                }
                if (median_enable){
                    processMedianHeaps(data.v);
                }

                if (thirdq_enable){
                    processThirdqHeaps(data.v);
                }
            }

            getline(s, buffer);
            data.gi = stod(buffer);

            if (selected_column == "gi"){
                mean = (data.gi / double(array.size() + 1)) + (mean * (double(array.size()) / double(array.size() + 1)));
                summ_s1 += data.gi;
                summ_s2 += data.gi * data.gi;

                if (data.gi < minn){
                    minn = data.gi;
                }
                if (data.gi > maxx){
                    maxx = data.gi;
                }
                if (firstq_enable){
                    processFirstqHeaps(data.gi);
                }
                if (median_enable){
                    processMedianHeaps(data.gi);
                }

                if (thirdq_enable){
                    processThirdqHeaps(data.gi);
                }
            }

            array.push_back(data); // ofc keep track of data because i have 16gig ram xD.
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

        double get_std(){
            // stay safe folks!
            double std;
            double sum;
            for (int i = 0; i < array.size(); i++){
                if (selected_column == "gap"){
                    sum += ((array[i].gap - mean) * (array[i].gap - mean));

                }
                if (selected_column == "grp"){
                    sum += ((array[i].grp - mean) * (array[i].grp - mean));
                }
                if (selected_column == "v"){
                    sum += ((array[i].v - mean) * (array[i].v - mean));
                }
                if (selected_column == "gi"){
                    sum += ((array[i].gi - mean) * (array[i].gi - mean));
                }
            }
            if (array.size() < 2){
                return 0;
            }
            sum = sum / double(array.size() - 1);
            std = sqrt(sum);
            return std;
        }

        double get_running_std(){
            // its not numerically stable but does the job ? (hope so xD)
            double s0 = array.size();
            return sqrt((summ_s2 * s0 - summ_s1 * summ_s1) / (s0 * (s0 - 1)) - 1);
        }

        void enable_firstq(){
            firstq_enable = true;
        }

        void enable_median(){
            median_enable = true;
        }
        
        void enable_thirdq(){
            thirdq_enable = true;
        }

    private:
        vector<Household> array;

        MinHeap firstq_right_heap;
        MaxHeap firstq_left_heap;
        bool firstq_enable = false;

        MinHeap median_right_heap;
        MaxHeap median_left_heap;
        bool median_enable = false;
        
        MinHeap thirdq_right_heap;
        MaxHeap thirdq_left_heap;
        bool thirdq_enable = false;

        double firstq;
        double median;
        double thirdq;

        double minn = INT64_MAX;
        double summ_s1 = 0;
        double summ_s2 = 0;
        double maxx = 0;
        double mean = 0;

        double welford_M = 0;
        double welford_S = 0;

        double rheap_pct(MaxHeap &lhap, MinHeap &rhap){
            return double(lhap.N()) / (lhap.N() + rhap.N() - 1);
        }
        double lheap_pct(MaxHeap &lhap, MinHeap &rhap){
            return double(lhap.N() - 1) / (lhap.N() + rhap.N() - 1);
        }

        double firstq_lheap_coefff(MaxHeap &lhap, MinHeap &rhap, double quant){
            double r_pct = rheap_pct(lhap, rhap);
            double l_pct = lheap_pct(lhap, rhap);
            return (quant - l_pct) / (r_pct - l_pct);
        }

        double firstq_rheap_coefff(MaxHeap &lhap, MinHeap &rhap, double quant){
            double r_pct = rheap_pct(lhap, rhap);
            double l_pct = lheap_pct(lhap, rhap);
            return (r_pct - quant) / (r_pct - l_pct);
        }

        void processFirstqHeaps(double &key){
            // push to left heap
            firstq_left_heap.insertNode(key);
            // delete root and push to right heap
            firstq_right_heap.insertNode(firstq_left_heap.deleteRoot());
            // check if our firstq heaps balanced 1k | 3k
            while (3 * firstq_left_heap.N() < 1 * firstq_right_heap.N()){
                firstq_left_heap.insertNode(firstq_right_heap.deleteRoot());
            }
            // calculate percentiles of each heap and coeff
            double firstq_lheap_pct = lheap_pct(firstq_left_heap, firstq_right_heap);
            double firstq_rheap_pct = rheap_pct(firstq_left_heap, firstq_right_heap);
            double firstq_lheap_coeff = firstq_lheap_coefff(firstq_left_heap, firstq_right_heap, 0.25);
            double firstq_rheap_coeff = firstq_rheap_coefff(firstq_left_heap, firstq_right_heap, 0.25);
            firstq = firstq_left_heap.arr[0] * (1 - firstq_lheap_coeff) + firstq_right_heap.arr[0] * (1 - firstq_rheap_coeff);
        }

        void processMedianHeaps(double &key){
            // push to left heap 
            median_left_heap.insertNode(key);

            // delete root and push to right heap
            median_right_heap.insertNode(median_left_heap.deleteRoot());

            while (median_left_heap.N() < median_right_heap.N()){
                median_left_heap.insertNode(median_right_heap.deleteRoot());
            }
            // then calculate mean
            if ((median_left_heap.N() + median_right_heap.N()) % 2 == 1){
                median = median_left_heap.arr[0];
            } else {
                median = median_left_heap.arr[0] * 0.5 + median_right_heap.arr[0] * 0.5;
            }
        }

        void processThirdqHeaps(double &key){
            // like firstq heap but inversed
            // push to right heap 
            thirdq_right_heap.insertNode(key); 
            // delete root and push to left heap
            thirdq_left_heap.insertNode(thirdq_right_heap.deleteRoot());
            // check if our thirdq heaps balanced 3k | 1k
            while (3 * thirdq_right_heap.N() < 1 * thirdq_left_heap.N()){
                thirdq_right_heap.insertNode(thirdq_left_heap.deleteRoot());
            }
            // calculate percentiles of each heap and coeff
            double thirdq_lheap_pct = lheap_pct(thirdq_left_heap, thirdq_right_heap);
            double thirdq_rheap_pct = rheap_pct(thirdq_left_heap, thirdq_right_heap);
            double thirdq_lheap_coeff = firstq_lheap_coefff(thirdq_left_heap, thirdq_right_heap, 0.75);
            double thirdq_rheap_coeff = firstq_rheap_coefff(thirdq_left_heap, thirdq_right_heap, 0.75); 
            // its show time...
            thirdq = thirdq_left_heap.arr[0] * (1 - thirdq_lheap_coeff) + thirdq_right_heap.arr[0] * (1 - thirdq_rheap_coeff);
        }

        vector<double> returnDataArray(){ // i thought i would use it xD
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
    string filename = argv[1];
	// string filename = "./inputs/input_std_10.txt";
    string outname = regex_replace(filename, std::regex("input"), "output");
    ofstream ofile;
    ofile.open(outname, ios::trunc); // open a filestream given argv input_*.txt -> output_*.txt

    string temp;
    int feature_count;
    int line_count;
    fstream file;
    Handler handler; // create our handler class object;

    file.open(filename, ios::in);
    getline(file, temp); // some getline bs... 
    feature_count = stoi(temp); // read how many features to keep
    for (int i = 0; i < feature_count; i++) {
        getline(file, temp);
        if (temp == "firstq"){
            handler.enable_firstq();
        } else if (temp == "median"){
            handler.enable_median();
        } else if (temp == "thirdq"){
            handler.enable_thirdq();
        }

        handler.features.push_back(temp);
    }
    getline(file, temp);
    getline(file, temp); // more getline bs.
    stringstream s(temp);
    getline(s, temp, ',');
    line_count = stoi(temp); // get line count 
    getline(s, temp);
    handler.selected_column = temp; // get selected column

    for (int i = 0; i < line_count; i++) { // lets begin
        getline(file, temp);
        if(temp == "add"){ // if its add
            i++; // we gon use getline so increment iterator.
            getline(file, temp);
            stringstream s(temp);
            handler.add_data(s); // append data to our data_array
        } else if(temp == "print"){ // if its print then pass it to ofstream
            ofile << handler.start_date << "," << handler.stop_date << ",";
            for(int i = 0; i < handler.features.size(); i++){

                if (handler.features[i] == "mean"){ // pretty self-explanatory tbh.
                    ofile << handler.get_mean();
                } else if (handler.features[i] == "std"){
                    ofile << handler.get_std();
                } else if (handler.features[i] == "min"){
                    ofile << handler.get_min();
                } else if (handler.features[i] == "firstq"){
                    ofile << handler.get_firstq();
                } else if (handler.features[i] == "median"){
                    ofile << handler.get_median();
                } else if (handler.features[i] == "thirdq"){
                    ofile << handler.get_thirdq();
                } else if (handler.features[i] == "max"){
                    ofile << handler.get_max();
                }

                if (i == handler.features.size() - 1){
                    ofile << "\n";
                } else {
                    ofile << ",";
                }
            }
        }
    }
    ofile.close(); // dont leave open pointer behind.
    file.close();
    return 0; // goodbye!
}