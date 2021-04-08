
// 1198. Find Smallest Common Element in All Rows
// https://leetcode.com/problems/find-smallest-common-element-in-all-rows/
// day 22 March 2021 challenge
// https://leetcode.com/explore/challenge/card/march-leetcoding-challenge-2021/591/week-4-march-22nd-march-28th/3680/


class Solution {
public:
    int smallestCommonElement(vector<vector<int>>& mat) {
        int m = mat.size();     // rows
        int n = mat[0].size();  // cols

        map<int,int> mp; // number,frequency
        pair<map<int,int>::iterator,bool> p;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j) {
                p = mp.insert({mat[i][j],1});
                if( !p.second )
                    ++p.first->second;
            }

        for(auto it = mp.begin(); it != mp.end(); ++it)
            if( it->second == m ) return it->first;

        return -1;
    }
};
