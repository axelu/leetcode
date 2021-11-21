
// 1128. Number of Equivalent Domino Pairs
// https://leetcode.com/problems/number-of-equivalent-domino-pairs/


class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        size_t n = dominoes.size();
        if( n <= 1 ) return 0;

        int r = 0;
        map<pair<int,int>,int> seen;

        seen.insert({{dominoes[0][0],dominoes[0][1]},1});
        map<pair<int,int>,int>::iterator it;
        int a,b;
        for(int i = 1; i < n; ++i) {
            a = dominoes[i][0];
            b = dominoes[i][1];

            if( a != b) {
                it = seen.find({b,a});
                if( it != end(seen) )
                    r += it->second;
            }

            it = seen.find({a,b});
            if( it != end(seen) ) {
                r += it->second;
                ++it->second;
            } else {
                seen.insert({{a,b},1});
            }
        }

        return r;
    }
};
