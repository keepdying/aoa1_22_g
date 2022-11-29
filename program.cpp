#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <iosfwd>
#include <chrono>

using namespace std;

class Row
{
public:
	int bookID;
	string title;
	string authors;
	float average_rating;
};

int partition(vector<Row> &list, const int &low, const int &high, int &partition_count, int &swap_count);
void quicksort(vector<Row> &list, const int &low, const int &high, int &partition_count, int &swap_count);
vector<Row> read_rows(const string &filename, const int &line_count);
void write_rows(const vector<Row> &list, const string &filename);
void sort_and_calculate(vector<Row> &list, const string &amount);

vector<Row> read_rows(const string &filename, const int &line_count)
{
	fstream fp;
	fp.open(filename, ios::in | ios::out);
	if (!fp.is_open())
	{
		cerr << "File couldn't be open." << endl;
		exit(1);
	}

	string line, column;
	vector<Row> list;
	getline(fp, line); // in order to skip headers

	for (int i = 0; i < line_count; i++)
	{ // could be defined as a new function

		getline(fp, line);
		stringstream s(line);
		Row entry;
		getline(s, column, ',');
		entry.bookID = stoi(column);
		getline(s, column, ',');
		entry.title = column;
		getline(s, column, ',');
		entry.authors = column;
		getline(s, column, ',');
		entry.average_rating = stof(column);

		getline(s, column);

		list.push_back(entry);
	}
	fp.close();
	return list;
};

void write_rows(const vector<Row> &list, const string &filename)
{
	fstream fp;
	fp.open(filename, ios::out | ios::trunc);

	fp << "bookID,average_rating\n";

	for (int i = 0; i < list.size(); i++)
	{
		fp << list[i].bookID << "," << list[i].average_rating << "\n";
	}

	fp.close();
}

void quicksort(vector<Row> &list, const int &low, const int &high, int &partition_count, int &swap_count)
{	
	// cout << low << " " << high << "\n";
	if (low < high)
	{
		int pivot;
		pivot = partition(list, low, high, partition_count, swap_count);

		quicksort(list, low, pivot - 1, partition_count, swap_count);
		quicksort(list, pivot + 1, high, partition_count, swap_count);
	}
};

int partition(vector<Row> &list, const int &low, const int &high, int &partition_count, int &swap_count)
{
	partition_count++;

	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (list[j].average_rating < list[high].average_rating)
		{
			i++;
			swap_count++;
			iter_swap(list.begin() + i, list.begin() + j);
		}
	}
	swap_count++;
	iter_swap(list.begin() + i + 1, list.begin() + high);

	return i + 1;
};

void sort_and_calculate(vector<Row> &list, const string &amount)
{
	chrono::time_point<chrono::high_resolution_clock> start, end; // define start and end times.
	start = chrono::high_resolution_clock::now();
	int partition_count = 1;
	int swap_count = 0;
	quicksort(list, 0, list.size() - 1, partition_count, swap_count);
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;

	cout << "Total time elapsed for " << amount << " data: " << elapsed_seconds.count() * 1000 << " milliseconds"
		 << "\n";
	cout << "Partition count: " << partition_count << "\n"
		 << "Swap count: " << swap_count
		 << "\n\n";
};

int main()
{
	const string filename = "books.csv";
	ifstream inFile(filename);
	const int line_count = count(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>(), '\n') - 1;
	vector<Row> book_list = read_rows(filename, line_count);
	vector<Row> book_list_half;
	vector<Row> book_list_quarter;

	for (int i = 0; i < book_list.size() / 2; i++)
	{
		if (i < book_list.size() / 4)
		{
			book_list_quarter.push_back(book_list[i]);
		}

		book_list_half.push_back(book_list[i]);
	}

	sort_and_calculate(book_list, "all");
	sort_and_calculate(book_list_half, "half");
	sort_and_calculate(book_list_quarter, "quarter");

	const string sorted_filename = "sorted_books.csv";
	write_rows(book_list, sorted_filename);
};