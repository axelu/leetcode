
// 360. Sort Transformed Array
// https://leetcode.com/problems/sort-transformed-array/



class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {

        int x = nums[0];
        int f = a*x*x + b*x + c;
        vector<int> ans{f};
        int s,n,e,mid;
        vector<int>::iterator it;
        for(int i = 1; i < nums.size(); ++i) {
            x = nums[i];
            f = a*x*x + b*x + c;

            // returns 'n' if nums[n-1] <= target
            // returns  0  if nums[0] > target
            // binary search upper bound while loop
            // upper bound -> greater than target
            s = 0;
            n = ans.size(); // n = nums.size()
            e = n;
            while(s < e) {
                mid = s + ((e-s)/2);
                if( f >= ans[mid] )
                    s = mid + 1;
                else
                    e = mid;
            }
            if( s < n && ans[s] <= f )
                ++s;

            if( s == n ) {
                ans.push_back(f);
            } else if( s == 0 ) {
                ans.insert(ans.begin(),f);
            } else {
                it = ans.begin();
                advance(it,s);
                ans.insert(it,f);
            }

        }

        return ans;
    }
};
