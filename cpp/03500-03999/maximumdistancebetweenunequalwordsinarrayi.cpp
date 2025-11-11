
// 3696. Maximum Distance Between Unequal Words in Array I
// https://leetcode.com/problems/maximum-distance-between-unequal-words-in-array-i/



class Solution {
public:
    int maxDistance(vector<string>& words) {
        map<string,pair<int,int>> mp; // key: word; value: {first idx, last idx}

        for(int i = 0; i < words.size(); ++i) {
            auto p = mp.insert({words[i], {i,i}});
            if( !p.second )
                p.first->second.second = i;
        }

        int ans = 0;

        for(auto& p: mp) {
            string word = p.first;
            int fst = p.second.first;
            int lst = p.second.second;

            for(auto& pi: mp) {
                if( pi.first == word )
                    continue;

                ans = max(ans, abs(pi.second.second - fst)+1);
                ans = max(ans, abs(lst - pi.second.first)+1);
            }
        }

        return ans;
    }
};
