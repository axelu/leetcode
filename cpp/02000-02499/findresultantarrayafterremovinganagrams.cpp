
// 2273. Find Resultant Array After Removing Anagrams
// https://leetcode.com/problems/find-resultant-array-after-removing-anagrams/



class Solution {
public:
    vector<string> removeAnagrams(vector<string>& words) {

        for(auto it = next(words.begin()); it != words.end(); ) {
            // prev
            vector<int> pre(26,0);
            for(auto c: *prev(it))
                ++pre[c-'a'];
            // curr
            vector<int> cur(26,0);
            for(auto c: *it)
                ++cur[c-'a'];

            if( pre == cur )
                it = words.erase(it);
            else
                ++it;
        }

        return words;
    }
};
