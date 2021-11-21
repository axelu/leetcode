
// 451. Sort Characters By Frequency
// https://leetcode.com/problems/sort-characters-by-frequency/


class Solution {
public:
    string frequencySort(string& s) {

        vector<vector<int>> v(256,vector<int>(2,0));
        for(int i = 0; i < 256; ++i)
            v[i][0] = i;

        int n = s.size();
        for(int i = 0; i < n; ++i)
            ++v[(int)s[i]][1];

        sort(v.begin(),v.end(),[](const vector<int>& a, const vector<int>& b){
            return a[1] > b[1];
        });

        int pos = 0;
        for(int i = 0; i < v.size(); ++i)
            for(int j = 0; j < v[i][1]; ++j) {
                s[pos] = (char)v[i][0];
                ++pos;
            }

        return s;
    }
};
