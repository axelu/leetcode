#include <iostream>
#include <cassert>
#include <chrono>

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// day 26 August 2020 challenge
// Fizz Buzz
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/552/week-4-august-22nd-august-28th/3437/
// https://leetcode.com/problems/fizz-buzz/


class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> r;
        r.reserve(n);

        // too slow
        /* 
        for(int i = 1; i <= n; ++i) {
            int rem3 = i % 3;
            int rem5 = i % 5;
            if( rem3 == 0 && rem5 == 0 ) {
                r.push_back("FizzBuzz");
            } else if ( rem3 == 0 ) {
                r.push_back("Fizz");
            } else if ( rem5 == 0 ) {
                r.push_back("Buzz");
            } else {
                r.push_back(to_string(i));
            }
        }
        */

		string s;
        for(int i = 1; i<= n; ++i){
		    s = "";
            if( i % 3 == 0 )
                s += "Fizz";
            if( i % 5 == 0 )
                s += "Buzz";
			if( s == "" )
				s = to_string(i);
            r.push_back(s);
        }





        // vector<string> r(n);
        // generate(r.begin(), r.end(), [i = 0] () mutable { return to_string(++i); });

        return r;
    }

    vector<int> fizzBuzzInt(int n) {
        vector<int> r(n);
        generate(r.begin(), r.end(), [n = 0] () mutable { return n++; });

        return r;
    }
};

int main() {
    Solution s;
    vector<string> r;
    vector<int> ri;

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    
    r = s.fizzBuzz(30);
    // ri = s.fizzBuzzInt(2147483647);

    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cout << elapsed_seconds.count() << endl;
    
    for(auto s : r) {
        cout << s << endl;
    }
    




    return 0;
}
