
// 3186. Maximum Total Damage With Spell Casting
// https://leetcode.com/problems/maximum-total-damage-with-spell-casting/




class Solution {
private:

    long long mem[100000];

    long long rec(vector<long long>& pwr, vector<long long>& cnt, int n, int pos) {
        if( pos >= n )
            return 0LL;

        // we have a choice
        //    pick the current pos OR
        //    don't pick the current pos
        // if we arrived at pos, we can pick it

        if( mem[pos] != -1LL )
            return mem[pos];

        long long a = pwr[pos] * cnt[pos];
        if( pos + 1 < n && pwr[pos+1] > pwr[pos] + 2LL )
            a += rec(pwr, cnt, n, pos+1);
        else if( pos + 2 < n && pwr[pos+2] > pwr[pos] + 2LL )
            a += rec(pwr, cnt, n, pos+2);
        else if( pos + 3 < n )
            a += rec(pwr, cnt, n, pos+3);

        long long b = rec(pwr, cnt, n, pos + 1);

        return mem[pos] = max(a, b);
    }
public:
    long long maximumTotalDamage(vector<int>& power) {

        map<int,int> mp;
        for(int x: power)
            ++mp[x];

        vector<long long> pwr;
        vector<long long> cnt;
        for(auto it = mp.begin(); it != mp.end(); ++it) {
            pwr.push_back(it->first);
            cnt.push_back(it->second);
        }

        int n = pwr.size(); // pwr.size() == cnt.size()

        memset(mem,-1,sizeof mem);
        return rec(pwr, cnt, n, 0);
    }
};
