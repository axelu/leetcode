
// 3185. Count Pairs That Form a Complete Day II
// https://leetcode.com/problems/count-pairs-that-form-a-complete-day-ii/

// one pass

class Solution {
public:
    long long countCompleteDayPairs(vector<int>& hours) {
        int n = hours.size();

        long long ans = 0LL;

        long long cnt[25];memset(cnt,0,sizeof cnt);
        int rem = hours[n-1] % 24;
        if( rem == 0 )
            rem = 24;
        ++cnt[rem];
        for(int i = n-2; i >= 0; --i) {
            int rem = hours[i] % 24;
            ans += cnt[24 - rem];
            if( rem == 0 )
                ++cnt[24];
            else
                ++cnt[rem];
        }

        return ans;
    }
};



// two pass

class Solution {
public:
    long long countCompleteDayPairs(vector<int>& hours) {
        int n = hours.size();
        
        long long ans = 0LL;
        
        long long cnt[25];memset(cnt,0,sizeof cnt);
        for(int i = 0; i < n; ++i) {
            int rem = hours[i] % 24;
            if( rem == 0 )
                rem = 24;
            ++cnt[rem];
        }
        
        for(int i = 0; i < n-1; ++i) {
            int rem = hours[i] % 24;
            if( rem == 0 )
                --cnt[24];
            else
                --cnt[rem];
            ans += cnt[24 - rem];
        }
        
        return ans;
    }
};
