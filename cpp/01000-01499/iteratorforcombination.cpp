#include <iostream>
#include <cassert>

#include <string>
#include <cmath>
#include <set>

using namespace std;

// 1286. Iterator for Combination
// https://leetcode.com/problems/iterator-for-combination
// day 13 of the August 2020 challenge
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/550/week-2-august-8th-august-14th/3422/

class CombinationIterator {
public:
    CombinationIterator(string characters, int combinationLength) {

        for (int n = 0;  n <= pow(2, characters.length()) - 1; n++ ) {

            int bits = 0;
            int i = n;
            while (i) { 
                bits += i & 1; 
                i >>= 1;
            }
            
            if ( bits == combinationLength ) {

                string s;
                for(int j = 0; j < characters.length(); j++) {
                    if( n & (1<<j) ) s.push_back(characters[j]);
                }
                r.insert(s);

            }
        }

    }

    string next() {

        string s;
        if ( !r.empty() ) {
            s = *r.begin();
            r.erase(r.begin());
        }
        return s;
    }

    bool hasNext() {
        return ( r.empty() ) ? false : true;
    }
private:
    set<string> r;
};

int main() {

    CombinationIterator* iterator = new CombinationIterator("abc", 2); // creates the iterator.
/*
    cout << iterator->next() << endl; // returns "ab"
    cout << iterator->hasNext() << endl; // returns true
    cout << iterator->next() << endl; // returns "ac"
    cout << iterator->hasNext() << endl; // returns true
    cout << iterator->next() << endl; // returns "bc"
    cout << iterator->hasNext() << endl; // returns false    
*/

    cout << iterator->hasNext() << endl; // returns true
    cout << iterator->next() << endl; // returns "ab"
    cout << iterator->hasNext() << endl; // returns true
    cout << iterator->hasNext() << endl; // returns true
    cout << iterator->next() << endl; // returns "ac"
    cout << iterator->next() << endl; // returns "bc"
    cout << iterator->hasNext() << endl; // returns false
    cout << iterator->hasNext() << endl; // returns false
    cout << iterator->hasNext() << endl; // returns false



 
    CombinationIterator* iterator1 = new CombinationIterator("bvwz", 2); // creates the iterator.

    do {
        cout << iterator1->next() << endl;
    } while ( iterator1->hasNext() );




    return 0;
}
