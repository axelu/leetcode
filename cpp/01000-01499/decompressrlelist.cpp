
// 1313. Decompress Run-Length Encoded List
// https://leetcode.com/problems/decompress-run-length-encoded-list/


class Solution {
public:
    vector<int> decompressRLElist(vector<int>& nums) {
        auto n = nums.size();
        vector<int> r;
        for(int i = 0; i < n; i += 2)
            for(int k = 0; k < nums[i]; ++k)
                r.push_back(nums[i+1]);
        return r;
    }
};
