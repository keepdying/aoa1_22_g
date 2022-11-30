#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

struct Household {
   uint32_t index;
   tm datetime;
   float gap;
   float grp;
   float v;
   float gi;
};

class Handler {
   public:
		 bool features [7];
		 string selected_column;

		 void add_data(string &str){

		 }

		 void print(){

		 }
   private:
		 vector<Household> array;
		 float minn;
		 tm start_date;
		 float maxx;
		 tm stop_date;

};


int main(int argc, char** argv){
   string filename = argv[1];
   string temp;
   uint8_t feature_count;
   uint32_t line_count;
   fstream file;

   Handler handler;

   file.open(filename,ios::in);
   getline(file, temp);
   feature_count = stoi(temp);

   for (uint8_t i = 0; i < feature_count; i++){
	 getline(file, temp);
	 if (temp == "mean"){
		handler.features[0] = true;
	 } else if (temp == "std"){
		handler.features[1] = true;
	 } else if (temp == "min"){
		handler.features[2] = true;
	 } else if (temp == "firstq"){
		handler.features[3] = true;
	 } else if (temp == "median"){
		handler.features[4] = true;
	 } else if (temp == "thirdq"){
		handler.features[5] = true;
	 } else if (temp == "max"){
		handler.features[6] = true;
	 }
   }
   getline(file, temp);
   getline(file, temp);
   stringstream s(temp);
   getline(s, temp, ',');
   line_count = stoi(temp);
   getline(s, temp);
   handler.selected_column = temp;

   for (uint32_t i = 0; i < line_count; i++){
	  getline(file,temp);
	  if (temp == "add"){
		 getline(file, temp);
		 handler.add_data(temp);
	  } else if (temp == "print"){
		 handler.print();
	  }
   }
   return 0;
}