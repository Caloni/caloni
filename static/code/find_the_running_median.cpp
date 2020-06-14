#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

void insert_new_element(vector<int>& a, size_t new_element)
{
	size_t begin = 0;
	size_t end = new_element;
	size_t sz = end - begin;
    size_t median= begin + sz / 2 - (sz % 2 ? 0 : 1);

    while( sz > 1 ) 
    {
        if( a[new_element] < a[median] ) 
			end = median;
        else
			begin = median + 1;
		sz = end - begin;
		median = median == begin? begin : begin + sz / 2 - (sz % 2 ? 0 : 1);
    }

	size_t insert_offset = a[new_element] < a[median] ? median : median + 1;
	int element = a[new_element];
	memmove(&a[insert_offset + 1], &a[insert_offset], (new_element - insert_offset) * sizeof(int));
	a[insert_offset] = element;
}

/*
 * Complete the runningMedian function below.
 */
vector<double> runningMedian(vector<int> a) 
{
	vector<double> ret;

	if (! a.empty())
		ret.push_back(a[0]);

	for( size_t new_element = 1; new_element < a.size(); ++new_element )
	{ 
		insert_new_element(a, new_element);
		size_t sz = new_element + 1;
		bool odd = sz % 2 ? true : false;
		size_t median = sz / 2 - (odd ? 0 : 1);
		double result = odd ? a[median] : (a[median] + a[median+1]) / 2.0;
		ret.push_back(result);
	}

    return ret;
}

int main()
{
	/*vector<int> test = { 12, 4, 5, 3, 8, 7, 5, 5 };
	for (size_t new_element = 1; new_element < test.size(); ++new_element)
		insert_new_element(test, new_element);
	return 0;*/

    ofstream fout(getenv("OUTPUT_PATH"));

    int a_count;
    cin >> a_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> a(a_count);

    for (int a_itr = 0; a_itr < a_count; a_itr++) 
    {
        int a_item;
        cin >> a_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        a[a_itr] = a_item;
    }

    vector<double> result = runningMedian(a);

    fout.precision(1);
    for (size_t result_itr = 0; result_itr < result.size(); result_itr++) 
    {
        fout << fixed << result[result_itr];

        if (result_itr != result.size() - 1) 
        {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

