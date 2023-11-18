
// 2366. Minimum Replacements to Sort the Array
// https://leetcode.com/problems/minimum-replacements-to-sort-the-array/





class Solution {
private:
    pair<int,long long> solve(int mx, int val) {
        // cout << "solve mx " << mx << " val " << val << endl;

        int a = val / mx;
        if( val % mx == 0 ) {
            // cout << "  new max " << mx << " nbr operations " << a-1 << endl;
            return {mx,a-1};

        }

        int t = a-1;
        int b = val - (t * mx);
        int c = b / 2;

        int d = val / (a+1);

        // cout << "  new max " << c << " nbr operations " << a << endl;
        // return {c,a};
        // cout << "  new max " << max(c,d) << " nbr operations " << a << endl;
        return {max(c,d),a};
    }
public:
    long long minimumReplacement(vector<int>& nums) {
        int n = nums.size();

        long long ans = 0LL;
        int mx = nums[n-1];
        for(int i = n-2; i >= 0; --i) {
            if( nums[i] <= mx ) {
                mx = nums[i];
            } else {
                auto p = solve(mx,nums[i]);
                mx = p.first;
                ans += p.second;
            }
        }

        return ans;
    }
};
