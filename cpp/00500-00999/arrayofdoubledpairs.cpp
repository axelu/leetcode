
// 954. Array of Doubled Pairs
// https://leetcode.com/problems/array-of-doubled-pairs/
// day 11 August 2021 challenge
// https://leetcode.com/explore/featured/card/august-leetcoding-challenge-2021/614/week-2-august-8th-august-14th/3877/




class Solution {
public:
    bool canReorderDoubled(vector<int>& arr) {
        int n = arr.size(); // 0 <= arr.length <= 3 * 104; n is even
        if( n == 0 )
            return true;

        // sort the array, note that there can be duplicates
        // for arr[0] find the double in arr[1,n-1];
        // we need to keep track of the indicies already used, so maybe a map
        // with key andn count is the better data structure

        auto cmp = [](const int a, const int b){
            if( a < 0 && b < 0 ) {
                return a > b;
            } else if( a < 0 && b >= 0) {
                return true;
            } else if( a >= 0 && b > 0 ) {
                return a < b;
            } else {
                return false;
            }
        };
        map<int,int,decltype(cmp)> mp(cmp);

        for(int i = 0; i < n; ++i) {
            auto p = mp.insert({arr[i],1});
            if( !p.second)
                ++p.first->second;
        }

        int val,cnt;
        for(auto it = mp.begin(); it != mp.end(); ++it) {
            // cout << it->first << ":" << it->second << " ";

            val = it->first;
            cnt = it->second;
            if( val == 0 ) {
                if( cnt % 2 != 0 )
                    return false;
                continue;
            }

            if( cnt == 0 )
                continue;

            auto f = mp.find(2*val);
            if( f == mp.end() || f->second < cnt )
                return false;

            f->second -= cnt;
        }
        // cout << endl;


        return true;
    }
};
