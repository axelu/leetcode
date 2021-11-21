
// 378. Kth Smallest Element in a Sorted Matrix
// https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
// day 7 July 2021 challenge
// https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/608/week-1-july-1st-july-7th/3805/




class Solution {
private:
    vector<int> merge(vector<int>& a, vector<int>& b) {
        int i = 0, j = 0, k = 0;
        vector<int> res(a.size()+b.size());
        while( i < a.size() && j < b.size() ) {
            if( a[i] < b[j] ) {
                res[k] = a[i];
                ++i;
            } else {
                res[k] = b[j];
                ++j;
            }
            ++k;
        }
        while( i < a.size() ) {
            res[k] = a[i];
            ++i;
            ++k;
        }
        while( j < b.size() ) {
            res[k] = b[j];
            ++j;
            ++k;
        }

        return res;
    }

public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        // n x n matrix, basically n == matrix.size() == matrix[i].size()
        int n = matrix.size();

        vector<int> a = matrix[0];
        vector<int> r;
        for(int i = 1; i < n; ++i) {

            r = merge(a,matrix[i]);
            a = r;

        }

        return a[k-1];
    }
};
