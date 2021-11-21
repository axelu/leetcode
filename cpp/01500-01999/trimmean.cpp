
// 1619. Mean of Array After Removing Some Elements
// https://leetcode.com/problems/mean-of-array-after-removing-some-elements/

class Solution {
public:
    double trimMean(vector<int>& arr) {
        sort(begin(arr),end(arr));
        auto n = arr.size();
        int d = n * 0.05;
        return accumulate(begin(arr)+d,end(arr)-d,0)/(double)(n - 2*d);
    }
};
