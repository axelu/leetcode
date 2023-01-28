
// 2237. Count Positions on Street With Required Brightness
// https://leetcode.com/problems/count-positions-on-street-with-required-brightness/


// https://www.geeksforgeeks.org/binary-indexed-tree-range-updates-point-queries/
// binary indexed tree (BIT)
// opting for method 2 just using array and prefixSum

class Solution {
private:
    void update(int arr[], int l, int r, int val) {
        arr[l] += val;
        arr[r+1] -= val;
    }

public:
    int meetRequirement(int n, vector<vector<int>>& lights, vector<int>& requirement) {
        int arr[n+1];memset(arr,0,sizeof arr);

        // update the 'segements' that are illuminated by each light
        // range update
        for(auto& v: lights) {
            // v[0] = position, v[1] = range
            int l = max(0, v[0] - v[1]);
            int r = min(n-1, v[0] + v[1]);
            update(arr,l,r,1);
        }

        // prefixSum[i] is brightness at position i
        int prefixSum[n];
        prefixSum[0] = arr[0];
        for(int i = 1; i < n; ++i)
            prefixSum[i] = prefixSum[i-1] + arr[i];

        int ans = 0;
        for(int i = 0; i < n; ++i)
            if( prefixSum[i] >= requirement[i] )
                ++ans;

        return ans;
    }
};
