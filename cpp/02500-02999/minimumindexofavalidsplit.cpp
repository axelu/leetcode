
// 2780. Minimum Index of a Valid Split
// https://leetcode.com/problems/minimum-index-of-a-valid-split/




class Solution {
public:
    int minimumIndex(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return -1;

        unordered_map<int,int> cnt;

        unordered_set<int> l2rdominant[n]; // dominant elements left to right ending at i inclusive
        ++cnt[nums[0]];
        l2rdominant[0] = {nums[0]};
        for(int i = 1; i < n; ++i) {
            ++cnt[nums[i]];
            if( cnt[nums[i]] * 2 > i + 1 )
                l2rdominant[i].insert(nums[i]);

            // verify all others
            for(auto it = l2rdominant[i-1].begin(); it != l2rdominant[i-1].end(); ++it)
                if( cnt[*it] * 2 > i + 1 )
                    l2rdominant[i].insert(*it);
        }
        // cout << l2rdominant[3].size() << endl;       // expect 1
        // cout << *(l2rdominant[3].begin()) << endl;

        cnt.clear();

        unordered_set<int> r2ldominant[n]; // dominant elements right to left ending at i inclusive
        ++cnt[nums[n-1]];
        r2ldominant[n-1] = {nums[n-1]};
        for(int i = n-2; i >= 0; --i) {
            ++cnt[nums[i]];
            if( cnt[nums[i]] * 2 > n - i )
                r2ldominant[i].insert(nums[i]);

            // verify all others
            for(auto it = r2ldominant[i+1].begin(); it != r2ldominant[i+1].end(); ++it)
                if( cnt[*it] * 2 > n - i )
                    r2ldominant[i].insert(*it);
        }

        for(int i = 0; i < n-1; ++i) {
            if( l2rdominant[i].size() == 1 && r2ldominant[i+1].size() == 1 &&
                *(l2rdominant[i].begin()) == *(r2ldominant[i+1].begin()) ) {

                return i;
            }
        }

        return -1;
    }
};
