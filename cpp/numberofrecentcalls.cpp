
// day 1 October 2020 challenge
// https://leetcode.com/explore/featured/card/october-leetcoding-challenge/559/week-1-october-1st-october-7th/3480/
// https://leetcode.com/problems/number-of-recent-calls/


#include <iostream>
#include <cassert>
#include <chrono>

#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <iterator>
#include <queue>


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class RecentCounter {
private:
    queue<int> q;
public:
    RecentCounter() {
    }

    int ping(int t) {
        q.push(t);
        int l = q.back() - 3000;
        while( q.front() < l )
            q.pop();
        return q.size();
    }
};
/*
int main() {

    chrono::time_point<chrono::system_clock> start;
    chrono::time_point<chrono::system_clock> end;
    chrono::duration<double> elapsed_seconds;

    // start = chrono::system_clock::now();
    // do something
    // end = chrono::system_clock::now();
    // elapsed_seconds = end - start;
    // cout << "elapsed_seconds " << elapsed_seconds.count() << endl;

    RecentCounter s;
    assert(s.ping(1) == 1);
    assert(s.ping(100) == 2);
    assert(s.ping(3001) == 3);
    assert(s.ping(3002) == 3);
    assert(s.ping(10000) == 1);
    assert(s.ping(13000) == 2);

    return 0;
}*/

