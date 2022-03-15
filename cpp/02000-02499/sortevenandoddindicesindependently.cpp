
// 2164. Sort Even and Odd Indices Independently
// https://leetcode.com/problems/sort-even-and-odd-indices-independently/



class Solution {
public:
    vector<int> sortEvenOdd(vector<int>& nums) {
        int n = nums.size();
        vector<int> odd_non_increasing;
        vector<int> even_non_decreasing;

        for(int i = 0; i < n; ++i)
            if( i % 2 )
                odd_non_increasing.push_back(nums[i]);
            else
                even_non_decreasing.push_back(nums[i]);

        sort(even_non_decreasing.begin(),even_non_decreasing.end());
        sort(odd_non_increasing.begin(),odd_non_increasing.end(),greater<int>());

        int o = 0, e = 0;
        for(int i = 0; i < n; ++i)
            if( i % 2 )
                nums[i] = odd_non_increasing[o++];
            else
                nums[i] = even_non_decreasing[e++];

        return nums;
    }
};



