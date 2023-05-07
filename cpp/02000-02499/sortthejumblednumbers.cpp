
// 2191. Sort the Jumbled Numbers
// https://leetcode.com/problems/sort-the-jumbled-numbers/




class Solution {
private:

    int mapp(vector<int>& mapping, int x) {
        // edge case
        if( x == 0 )
            return mapping[0];

        int ret = 0;
        int f = 1;
        while( x > 0 ) {
            int t = x % 10;

            ret = ret + f * mapping[t];

            f *= 10;
            x /= 10;
        }

        return ret;
    }

public:
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
        int n = nums.size();

        vector<array<int,3>> v(n); // val nums, idx nums, mapped val nums
        for(int i = 0; i < n; ++i)
            v[i] = {nums[i], i, mapp(mapping,nums[i])};

        /*
        for(int i = 0; i < n; ++i)
            cout << v[i][0] << ":" << v[i][1] << ":" << v[i][2] << endl;
        */

        sort(v.begin(),v.end(),[](const array<int,3>& a, const array<int,3>& b){
           if( a[2] < b[2] ) {
               return true;
            } else if( a[2] == b[2] ) {
                if( a[1] < b[1] ) {
                    return true;
                }
            }
            return false;
        });

        for(int i = 0; i < n; ++i)
            nums[i] = v[i][0];

        return nums;
    }
};
