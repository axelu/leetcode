
// 2268. Minimum Number of Keypresses
// https://leetcode.com/problems/minimum-number-of-keypresses/



class Solution {
public:
    int minimumKeypresses(string s) {
        // idea: the chars that are used the most
        //    in s we need to map to the keys first, and so on

        vector<pair<char,int>> cnt(26);
        for(int i = 0; i < 26; ++i)
            cnt[i] = {'a'+i,0};

        for(char c: s)
            ++cnt[c-'a'].second;

        sort(cnt.begin(),cnt.end(),[](pair<char,int>& a, pair<char,int>& b){
            return a.second > b.second;
        });

        int ans = 0;

        for(int i = 0; i < 26; ++i) {
            int f = 1 + i/9;
            ans += cnt[i].second * f;
        }

        return ans;
    }
};
