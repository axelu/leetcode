
// 2135. Count Words Obtained After Adding a Letter
// https://leetcode.com/problems/count-words-obtained-after-adding-a-letter/



class Solution {
public:
    int wordCount(vector<string>& startWords, vector<string>& targetWords) {
        // pre-process target words
        // bitmask,count for target words by length (length = number of set bits)
        unordered_map<int,int> tw[26+1];
        for(auto s : targetWords) {
            int s_sz = s.size();
            int mask = 0;
            for(int i = 0; i < s_sz; ++i)
               mask |= 1 << (s[i] - 'a');
            auto p = tw[s_sz].insert({mask,1});
            if( !p.second )
                ++p.first->second;
        }

        int ans = 0;
        for(auto s : startWords) {
            int s_sz = s.size();
            if( s_sz == 26 )
                continue;

            int mask = 0;
            for(int i = 0; i < s_sz; ++i)
               mask |= 1 << (s[i] - 'a');

            for(int i = 0; i < 26; ++i) {
                if( !((mask >> i) & 1) ) {
                    mask |= 1 << i;
                    auto f = tw[s_sz+1].find(mask);
                    if( f != tw[s_sz+1].end() && f->second ) {
                        ans += f->second;
                        f->second = 0; // mark as counted
                    }
                    mask &= ~(1 << i);
                }
            }
        }

        return ans;
    }
};
