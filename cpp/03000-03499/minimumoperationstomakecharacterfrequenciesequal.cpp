
// 3389. Minimum Operations to Make Character Frequencies Equal
// https://leetcode.com/problems/minimum-operations-to-make-character-frequencies-equal/





class Solution {
private:
    int cnt[26];
    int mem[26][2];

    int rec(int target, int pos, bool can_take_from_previous) {
        if( pos == 26 )
            return 0;

        // if can_take_from_previous, then
        // previous position count is target

        if( mem[pos][can_take_from_previous] != -1 )
            return mem[pos][can_take_from_previous];

        int ret = INT_MAX;

        if( cnt[pos] <= target ) {
            // we have a choice
            //    increase to target OR
            //    decrease to 0

            // increase to target
            // how many do we need?
            int need = target - cnt[pos];
            // can we take from previous and if so, how many?
            int can_take = 0;
            if( can_take_from_previous ) {
                // we can only take from it if it was greater than target
                if( cnt[pos-1] > target )
                    can_take = cnt[pos-1] - target;
            } else if( pos > 0 ) {
                can_take = cnt[pos-1];
            }
            ret = max(0, need - can_take) + rec(target, pos+1, true);

            // decrease to 0
            ret = min(ret, cnt[pos] + rec(target, pos+1, false));

        } else {
            // decrease to target
            ret = (cnt[pos] - target) + rec(target, pos+1, true);
        }

        return mem[pos][can_take_from_previous] = ret;
    }

public:
    int makeStringGood(string s) {

        // we either decrease a char to a count of 0 OR
        // increase/decrease a char to a count of target
        // target is in range of the min or max occurence
        // of each char
        // we will simply try each target

        int mn = INT_MAX;
        int mx = INT_MIN;
        memset(cnt,0,sizeof cnt);
        for(auto c: s) {
            ++cnt[c-'a'];
            mn = min(mn, cnt[c-'a']);
            mx = max(mx, cnt[c-'a']);
        }

        int ans = s.size(); // worst case
        for(int target = mn; target <= mx; ++target) {
            memset(mem,-1,sizeof mem);
            ans = min(ans, rec(target, 0, false));
        }

        return ans;
    }
};
