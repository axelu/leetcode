
// 1299. Replace Elements with Greatest Element on Right Side
// https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/

class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        auto n = arr.size();

        vector<int> r(n);
        r[n-1] = -1;

        if( n == 1 ) return r;

        int mx = arr.back();
        for(int i = n-2; i >= 0; --i) {
            r[i] = mx;
            mx = max(mx,arr[i]);
        }

        return r;
    }
};
