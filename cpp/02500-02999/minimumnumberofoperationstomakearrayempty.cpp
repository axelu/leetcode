
// 2870. Minimum Number of Operations to Make Array Empty
// https://leetcode.com/problems/minimum-number-of-operations-to-make-array-empty/





class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();

        unordered_map<int,int> um; // val, frequency
        int one = 0;
        for(int val: nums) {
            ++um[val];
            if( um[val] == 1 )
                ++one;
            else if( um[val] == 2 )
                --one;
        }

        if( one )
            return -1;

        // we will greedily try to use the three delete operations
        // and revert to the two delete operation as needed
        // example: if freq = 10, we can delete 3 2x and delete 2x for a total of 5 operations

        int ans = 0;
        for(auto p: um) {
            int freq = p.second;
            int rem = freq % 3;
            if( rem == 0 )
                ans += freq / 3;
            else if( rem == 1 )
                ans += 2 + ((freq - 4) / 3);
            else // rem == 2
                ans += 1 + ((freq - 2) / 3);
        }

        return ans;
    }
};
