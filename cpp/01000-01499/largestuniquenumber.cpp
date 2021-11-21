
// 1133. Largest Unique Number
// https://leetcode.com/problems/largest-unique-number/




class Solution {
public:
    int largestUniqueNumber(vector<int>& A) {
        int n = A.size();
        if( n == 1 ) return A[0];

        set<int> ans;
        unordered_map<int,int> seen;
        unordered_map<int,int>::iterator f;
        for(int i = 0; i < n; ++i) {
            f = seen.find(A[i]);
            if( f == seen.end() ) {
                seen.insert({A[i],1});
                ans.insert(A[i]);
            } else if ( f->second == 1 ) {
                ++f->second;
                ans.erase(A[i]);
            }
        }
        return ans.size() == 0 ? -1 : *ans.rbegin();

    }
};
