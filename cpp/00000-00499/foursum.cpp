
// 18. 4Sum
// https://leetcode.com/problems/4sum/



class Solution {
private:
    int * Nums;
    size_t N;
    vector<vector<int>> ans;

    void twoSum(int target, int l, vector<int>& prefix) {
        int r = N - 1;   // right idx
        int sum;
        while(l < r) {
            sum = Nums[l] + Nums[r];
            if( sum == target ) {
                vector<int> t = prefix;
                t.push_back(Nums[l]); t.push_back(Nums[r]);
                ans.push_back(t);
                ++l; while(l<r && Nums[l-1] == Nums[l]) ++l;
                --r; while(l<r && Nums[r+1] == Nums[r]) --r;
            } else if( sum < target ) {
                ++l;
            } else {
                // sum > 0
                --r;
            }
        }
    }

    void rec(int target, int k, int s, vector<int>& prefix) {
        // cout << "rec target=" << target << " k=" << k << " s=" << s << endl;

        // short circuit
        if( accumulate(Nums+s,Nums+s+k,0) > target ||
            accumulate(Nums+N-k,Nums+N,0) < target )
                return;

        if( k == 2 ) {
            twoSum(target,s,prefix);
            return;
        }

        for(int i = s; i <= N-k; ++i) {
            if( i > s && Nums[i-1] == Nums[i] ) continue;
            vector<int> t = prefix;
            t.push_back(Nums[i]);
            rec(target-Nums[i],k-1,i+1,t);
        }
    }

public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int k = 4; // fourSum
        N = nums.size();
        if( N < k ) return {};
        if( N == k ) {
            if( accumulate(nums.begin(),nums.end(),0) == target ) return {nums};
            else return {};
        }

        sort(nums.begin(),nums.end());
        Nums = nums.data();

        vector<int> prefix;
        rec(target,k,0,prefix);
        return ans;
    }
};
