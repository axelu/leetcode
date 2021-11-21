
// 341. Flatten Nested List Iterator
// https://leetcode.com/problems/flatten-nested-list-iterator/
// day 13 April 2021 challenge
// https://leetcode.com/explore/featured/card/april-leetcoding-challenge-2021/594/week-2-april-8th-april-14th/3706/



/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {
private:
    vector<int> v;
    int n,i;

    void rec(vector<NestedInteger>& nestedList) {
        size_t n = nestedList.size();
        for(int i = 0; i < n; ++i) {
            if( nestedList[i].isInteger() )
                v.push_back(nestedList[i].getInteger());
            else
                rec(nestedList[i].getList());
        }
    }

public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        rec(nestedList);
        n = v.size();
        i = 0;
    }

    int next() {
        int ans = v[i];
        ++i;
        return ans;
    }

    bool hasNext() {
        return i<n;
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
