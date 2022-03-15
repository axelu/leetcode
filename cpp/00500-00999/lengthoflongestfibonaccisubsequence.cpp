
// 873. Length of Longest Fibonacci Subsequence
// https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/


class Solution {
private:
    int n;
    unordered_map<int,int> um; // val,idx
    int mem[1000][1000];

    int rec(vector<int>& arr, int i, int j) {
        if( mem[i][j] != -1 )
            return mem[i][j];

        int ret = 0;

        int t = arr[i] + arr[j];
        auto f = um.find(t);
        if( f != um.end() )
            ret = 1 + rec(arr,j,f->second);

        return mem[i][j] = ret;
    }



public:
    int lenLongestFibSubseq(vector<int>& arr) {
        // arr is strictly increasing
        n = arr.size();

        for(int i = 0; i < n; ++i)
            um[arr[i]] = i;

        int ans = 0;
        memset(mem,-1,sizeof mem);

        for(int i = 0; i < n-2; ++i) {
            for(int j = i+1; j < n-1; ++j) {
                int ret = 0;
                int t = arr[i] + arr[j];
                auto f = um.find(t);
                if( f != um.end() )
                    ret = 3 + rec(arr,j,f->second);

                ans = max(ans,ret);
            }
        }

        return ans;
    }
};
