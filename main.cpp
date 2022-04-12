#include "paginator.h"
#include "streamcollection.h"
#include <vector>
#include <numeric>
#include <set>
#include "math.h"

using namespace std;


void PrintSpacesPositions(const string& str) {
    auto begin = str.begin(), end = str.end(), space = find(str.begin(), str.end(), ' ');
    while(space != end){
        cout << distance(begin, space) << " ";
        space = find(next(space), end, ' ');
    }
}

template <typename Container>
auto FindNearestElement(const Container& container, auto border){
    auto it = container.lower_bound(border);
    if(it == container.begin()){
        return it;
    }
    auto prev_it = prev(it);
    if(it == container.end()){
        return prev_it;
    }
    if(abs(border - (*it)) < abs(border - (*prev_it))){
        return it;
    }else{
        return prev_it;
    }
}

int main() {
    set<int> numbers = {1, 4, 6};
    cout << *FindNearestElement(numbers, 0) << " " << *FindNearestElement(numbers, 3) << " "
         << *FindNearestElement(numbers, 5) << " " << *FindNearestElement(numbers, 6) << " "
         << *FindNearestElement(numbers, 100) << endl;

    set<int> empty_set;

    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    return 0;
}