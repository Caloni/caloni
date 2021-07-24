---
categories:
- code
date: '2019-08-08'
link: https://gist.github.com/Caloni/31fd1105dd18374105d2eb00bce7ee3f
tags:
- draft
- ccpp
- english
title: Some things I learned in a Hacker Rank exercise
---

A couple of days ago I subscribed to Hacker Hank, a website specialized in provide interview exercises. The site is as a better version of Code Jam, with the possibility to Compile & Run the code, as well as running several test cases.

Talking with friends about one of them proposed a interesting puzzle called Find the Running Median. This is a good problem because it is easy to understand and tricky to implement.

My first attempt was naive, but worked for test cases where there were no duplicated numbers, a detail I overlooked in the description and happenned the very first test (lucky me it is possible to download the test cases, input and output, giving in return some of the points accumulated solving other problems).

    /*
     * Complete the runningMedian function below.
     */
    vector<double> runningMedian(ofstream& fout, vector<int> a) {
        vector<double> ret;
        set<int> oa;
    
        for( int n: a ) {
            oa.insert(n);
            auto oaMidIt = oa.size() == 1 ? oa.begin()
                : next(oa.begin(), oa.size() / 2 - (oa.size() % 2 == 0 ? 1 : 0) );
            auto oaMidIt2 = next(oaMidIt);
            double median;
            if( oa.size() % 2 == 1 ) {
                median = *oaMidIt;
            }
            else {
                median = ( *oaMidIt + *oaMidIt2 ) / 2.0;
            }
            fout << median << " " << n << "\n";
            ret.push_back(median);
        }
    
        return ret;
    }

So I started to draw in my window a new solution, based on inplace sort algorithm, using the same vector proposed skeleton by the site. The idea was to just move elements inside the vector, ordering them as calculating the median to evey new number.

    BEGIN --> 12,   4,   5,   3,   8,   7 <-- END
              ^     ^
              |     |-- SORTED_END
            MEDIAN          ^
                            |-- NEW
    
    BOOL ODD = TRUE;
    
    {
        DOUBLE MEDIAN = ODD ? MEDIAN : (MEDIAN + MEDIAN+1) / 2
        NEW = SORTED_END
        RECURSIVE/ITERATIVE_INSERT(BEGIN, SORTED_END, MEDIAN, NEW)
        ODD = ! ODD
        SORTED_END++
    } WHILE(  SORTED_END != END )
    INSERT(BEG, END, NEW, MED, ODD) {
        MED = SZ/2 - (SZ_ODD ? 0 : 1)
    
        1, 2, 3, 5, 6     (4)
              -
              < ?
        RIGHT OR LEFT
    /*my playground
    vector<int> test = { 12, 4, 5, 3, 8, 7, 5, 5 };
    for (size_t new_element = 1; new_element < test.size(); ++new_element)
    	insert_new_element(test, new_element);
    return 0;*/

I still wasn't thinking about the sort algorithm until I began to try and fail several times, but this try/error bitch always taught me how to make things faster then embryological bullshit to born from scribbed windows. It only requested a debugger to make the edit, compile, debug triple step.

I was still trying in the window, thought, until in one of these iteractions with the compiler/debugger I achieved a simples, clearer solution, using only offsets from the vector instead of iterators.

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
    	a.erase(a.begin() + new_element);
    	a.insert(a.begin() + insert_offset, element);
    }

This version almost done it, except for timeout error. Hacker Hank has a timeout of 2 seconds to C++ solutions and I was exceding it. After some thought (more try/error) I thought about change the container, but before I made a simples test: instead of using erase/insert methods make the things manually as in good old C.

    void insert_new_element(vector<int>& a, size_t new_element)
    {
        //...
    
    	size_t insert_offset = a[new_element] < a[median] ? median : median + 1;
    	int element = a[new_element];
        //a.erase(a.begin() + new_element);
        //a.insert(a.begin() + insert_offset, element);
    	memmove(&a[insert_offset + 1], &a[insert_offset], (new_element - insert_offset) * sizeof(int));
    	a[insert_offset] = element;
    }

And it worked. Now what I learned looking the other solutions.

There are incredible tools in C++, even since 98 or 11, that are frequently overlooked, but it is important to notice that the language has a framework for processing: containers, algorithms and so on. By example, looking for other solutions I learned about the characteristics of multiset and priorityqueue (spoiler: both have a ordering predicate and are logarithmic). There are smart functions in algorithm, too, as lowerbound.

A lot of solutions simply ignored the skeleton provided by the site and began its own code from scratch, eliminating the "request" that the numbers must be stored first in a vector. Sometimes, when there as skeleton in our life, we use them as guidelines, forgetting that "there is no spoon".

I hope you learned something, too. You can see my Hacker Rank attempts in the site (nickname caloni) or my GitHub repository.