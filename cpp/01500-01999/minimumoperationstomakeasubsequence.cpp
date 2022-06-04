
// 1713. Minimum Operations to Make a Subsequence
// https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/



class Solution {
public:
    int minOperations(vector<int>& target, vector<int>& arr) {
        // return minimum number of operations needed to make target a subsequence of arr
        // target consists of unique integers

        int target_sz = target.size();
        unordered_map<int,int> um;
        for(int i = 0; i < target_sz; ++i)
            um[target[i]] = i;

        // Longest Common Subsequence (LCS)
        vector<int> lcs;

        int arr_sz = arr.size();
        unordered_map<int,int>::iterator f;
        vector<int>::iterator lb;
        for(int i = 0; i < arr_sz; ++i) {
            f = um.find(arr[i]);
            if( f != um.end() ) {
                lb = lower_bound(lcs.begin(),lcs.end(),f->second);
                if( lb != lcs.end() )
                    *lb = f->second;
                else
                    lcs.push_back(f->second);
            }
        }

        return target_sz - lcs.size();
    }
};
