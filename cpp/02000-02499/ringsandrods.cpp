
// 2103. Rings and Rods
// https://leetcode.com/problems/rings-and-rods/



class Solution {
public:
    int countPoints(string rings) {
        unordered_set<int> r,g,b;
        for(int i = 0; i < rings.size(); i += 2) {
            if( rings[i] == 'R' )
                r.insert(rings[i+1]-48);
            else if( rings[i] == 'G' )
                g.insert(rings[i+1]-48);
            else
                b.insert(rings[i+1]-48);
        }

        int ans = 0;
        for(auto itr = r.begin(); itr != r.end(); ++itr)
            if( g.find(*itr) != g.end() && b.find(*itr) != g.end() )
                ++ans;

        return ans;
    }
};
