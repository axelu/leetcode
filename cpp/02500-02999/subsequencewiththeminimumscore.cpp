
// 2565. Subsequence With the Minimum Score
// https://leetcode.com/problems/subsequence-with-the-minimum-score/








class Solution {
private:
    // binary search
    int upper_bound(int nums[], int n, int target) {
        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        // binary search upper bound while loop
        // upper bound -> greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= nums[mid] )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && nums[s] <= target )
            ++s;

        return s;
    }

public:
    int minimumScore(string s, string t) {
        int s_sz = s.size();
        int t_sz = t.size();
        // edge case
        if(t_sz == 1 ) {
            for(char c: s)
                if( c == t[0] )
                    return 0;
            return 1;
        }

        // if s_sz < t_sz, then at minimum we will have to delete t_sz - sz_sz from t

        // subsequence suffix
        int t_sfx[t_sz];memset(t_sfx,-1,sizeof t_sfx);
        int j = t_sz - 1;                               // index in t
        for(int i = s_sz-1; i >= 0 && j >= 0; --i) {    // index in s
            if( s[i] == t[j] ) {
                t_sfx[j] = i;
                --j;
            }
        }
        /*
        // debug
        for(int j = 0; j < t_sz; ++j)
            cout << j << ":" << t_sfx[j] << " ";
        cout << endl;
        */

        int ans = t_sz;

        // lets assume we are deleting char 0 in t as the left char
        j = 0;                          // index in t
        int ub = upper_bound(t_sfx, t_sz, -1);
        ans = min(ans, ub);

        for(int i = 0; i < s_sz; ++i) { // index in s
            if( s[i] == t[j] ) {
                // cout << "i " << i << " j " << j << endl;

                if( j+1 == t_sz ) {
                    // we made it
                    return 0;
                }

                // lets assume we delete the char j+1 in t as the left char
                ub = upper_bound(t_sfx, t_sz, i);
                // cout << "ub " << ub << endl;

                ans = min(ans, (ub - 1) - (j+1) + 1);
                ++j;
            }


        }

        return ans;
    }
};
