
// 3692. Majority Frequency Characters
// https://leetcode.com/problems/majority-frequency-characters/



class Solution {
public:
    string majorityFrequencyGroup(string s) {
        int freq[26];memset(freq,0,sizeof freq);

        for(char c: s)
            ++freq[c-'a'];

        map<int,vector<char>> mp;
        for(int i = 0; i < 26; ++i)
            mp[freq[i]].push_back(i+'a');

        string ans = "";
        int max_group_size = 0;
        int f;
        for(auto p: mp) {
            int frequency = p.first;
            if( frequency == 0 )
                continue;
            int group_size = p.second.size();

            if( max_group_size < group_size ) {
                ans = "";
                for(char c: p.second )
                    ans.push_back(c);
                max_group_size = group_size;
                f = frequency;
            } else if( max_group_size == group_size ) {
                if( frequency > f ) {
                    ans = "";
                    for(char c: p.second )
                        ans.push_back(c);
                    // max_group_size = group_size;
                    f = frequency;
                }
            }
        }

        return ans;
    }
};
