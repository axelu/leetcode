
// 1296. Divide Array in Sets of K Consecutive Numbers
// https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/




class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        int n = nums.size();
        if( n % k )
            return false;
        if( k == 1 )
            return true;

        map<int,int> mp; // val,count
        for(int x: nums)
            ++mp[x];

        // for(auto it = mp.begin(); it != mp.end(); ++it)
        //     cout << it->first << ":" << it->second << endl;

        // remember last value that we have as starting point
        auto lst = mp.end();
        int i = 0;
        auto it = mp.begin();

        while( it != mp.end() ) {
            // cout << "outer loop " << it->first << ":" << it->second << endl;

            for(; i < k; ++i) {
                // cout << "inner loop " << i << " " << it->first << ":" << it->second << endl;
                if( i < k-1 ) {
                   if( next(it) == mp.end() || next(it)->first != it->first + 1 ||  next(it)->second == 0 )
                       return false;
                }
                --it->second;
                if( lst == mp.end() && it->second > 0 )
                    lst = it;
                ++it;
            }

            if( lst != mp.end() )
                it = lst;
            lst = mp.end();
            i = 0;
        }


        return true;
    }
};
