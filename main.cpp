#include <iostream>
#include <iterator>
#include "myalgorithms.h"
#include <vector>
#include <list>
#include <deque>
using namespace std;
template <typename T>
inline void printElement(const T& coll, const std::string& optstr)
{
    std::cout<<optstr;
    for(auto elem :coll)
    {
        std::cout << elem <<", ";

    }
    std::cout<<std::endl;

}

void test_mismatch()
{
    myAlgorithms algo = myAlgorithms();
    vector<int> col1 = {1,2,3,4,5,6};
    list<int> col2 = {1,2,3,4,5,6};
    printElement(col1,"col1 ");
    printElement(col2,"col2 ");

    auto values = algo.mismatch(col1.begin(), col1.end(),col2.begin());
    //should check whether a mismatch exists
    if(values.first == col1.end())
        cout<<"no mismatch"<<endl;
    else
    {
        cout<<"first mismatch: "
            <<*values.first << " and "
            <<*values.second << endl;
    }
}
void test_set_algorithms()
{
    myAlgorithms algo = myAlgorithms();
    vector<int> c1 = {1,2,2,4,6,7,7,9};
    deque<int> 	c2 = {2,2,2,3,6,6,8,9};

    cout<<"c1:						";
    copy(c1.cbegin(), c1.cend(),
         ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<"c2:						";
    copy(c2.cbegin(), c2.cend(),
         ostream_iterator<int>(cout," "));
    cout<<endl<<endl;
    //set_union
    cout<<"set_union():				";
    algo.set_union(c1.cbegin(),c1.cend(),
                   c2.cbegin(),c2.cend(),
                   ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<"set_intersection():				";
    algo.set_intersection(c1.cbegin(),c1.cend(),
                   c2.cbegin(),c2.cend(),
                   ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<"set_difference():				";
    algo.set_difference(c1.cbegin(),c1.cend(),
                   c2.cbegin(),c2.cend(),
                   ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<"set_symmetric_difference():				";
    algo.set_symmetric_difference(c1.cbegin(),c1.cend(),
                   c2.cbegin(),c2.cend(),
                   ostream_iterator<int>(cout," "));
    cout<<endl;
}

int main()
{
    cout << "Hello World!" << endl;
    test_mismatch();
    test_set_algorithms();
    return 0;
}

