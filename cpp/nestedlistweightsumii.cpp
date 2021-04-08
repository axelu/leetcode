
// 364. Nested List Weight Sum II
// https://leetcode.com/problems/nested-list-weight-sum-ii/


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
private:
    vector<vector<int>> v;

    void rec(vector<NestedInteger>& nestedList, int depth) {
        size_t n = nestedList.size();
        if( v.size() == depth )
            v.push_back({});
        for(int i = 0; i < n; ++i)
            if( nestedList[i].isInteger() )
                v[depth].push_back(nestedList[i].getInteger());
            else
                rec(nestedList[i].getList(),depth+1);
    }

public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        int sum = 0;
        rec(nestedList,0);

        int t = 0;
        int f = v.size();
        for(int i = 0; i < v.size(); ++i) {
            for(int j = 0; j < v[i].size(); ++j) {
                t += v[i][j];
            }
            sum += t*f;
            t = 0;
            --f;
        }

        return sum;
    }
};
