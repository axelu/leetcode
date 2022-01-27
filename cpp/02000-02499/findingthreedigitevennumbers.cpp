
// 2094. Finding 3-Digit Even Numbers
// https://leetcode.com/problems/finding-3-digit-even-numbers/



class Solution {
public:
    vector<int> findEvenNumbers(vector<int>& digits) {
        // even numbers end in 2, 4, 6, 8 and 0 regardless of how many digits they have

        int cnt[10];memset(cnt,0,sizeof cnt);
        for(int i : digits)
            ++cnt[i];

        vector<int> ans;

        unordered_map<int,int> um; // digit,count
        int x,rem;
        bool f;
        for(int i = 100; i < 999; ++i)
            if( i%2 == 0 ) {
                um.clear();
                x = i;
                while( x > 0 ) {
                    rem = x%10;
                    ++um[rem];
                    x /= 10;
                }
                f = true;
                for(auto p : um)
                   if( cnt[p.first] < p.second ) {
                       f = false;
                       break;
                    }
                if( f )
                    ans.push_back(i);
            }

        return ans;
    }
};
