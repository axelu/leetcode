
// 385. Mini Parser
// https://leetcode.com/problems/mini-parser/



/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
    int N;

    NestedInteger rec(string& s, int& pos) {
        NestedInteger ni = NestedInteger();
        if( s[pos] == '[' ) {
            // nested list
            while( s[pos] != ']' ) {
                ++pos;
                if( s[pos] == ']' ) break; // empty list
                ni.add(rec(s,pos));
            }
            ++pos;
        } else {
            // individual integer, ends either at a comma or a closing square bracket
            string t = "";
            while( pos < N && s[pos] != ',' && s[pos] != ']' ) {
                t += s[pos];
                ++pos;
            }
            if( !t.empty() ) ni.setInteger(stoi(t));
        }
        return ni;
    }

public:
    NestedInteger deserialize(string s) {
        N = s.size();
        int pos = 0;
        return rec(s,pos);
    }
};
