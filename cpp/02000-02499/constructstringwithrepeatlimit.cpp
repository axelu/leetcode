
// 2182. Construct String With Repeat Limit
// https://leetcode.com/problems/construct-string-with-repeat-limit/




class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        map<char,int> mp;
        for(char c: s)
            ++mp[c];

        // greedily construct the ansewr string
        //   as long as we have the highest char, use it up to repeatLimit times
        //   if we still have highest char left, then sprinkle in one of next highest char
        //   then continue to draw from highest char

        string ans = "";
        auto it = mp.rbegin();
        auto it_not0 = next(it); // keeping track of the next non-zero count char
        while( it != mp.rend() ) {

            int k = 0;
            while( k < repeatLimit && it->second > 0 ) {
                ans.push_back(it->first);
                ++k;
                --it->second;
            }

            if( k == repeatLimit ) { // we placed the current char repeatLimit times
                if( it->second > 0 ) { // we still have more of the current char
                    if( it_not0 != mp.rend() ) {
                        ans.push_back(it_not0->first);
                        --it_not0->second;
                        if( it_not0->second == 0 )
                            ++it_not0;
                    } else {
                        // we are done as there are no more other chars left
                        break;
                    }
                } else {
                    it = it_not0;
                    it_not0 = next(it);
                }


            } else { // we ran out of the current char before reaching repeatLimit
                it = it_not0;
                it_not0 = next(it);
            }
        }

        return ans;
    }
};
