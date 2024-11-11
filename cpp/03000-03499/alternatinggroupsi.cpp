
// 3206. Alternating Groups I
// https://leetcode.com/problems/alternating-groups-i/



class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors) {
        int n = colors.size();

        int ans = 0;

        // brute force
        for(int i = 0; i < n; ++i) {
            int a = colors[i];
            int b = colors[(i + 1) % n];
            int c = colors[(i + 2) % n];
            if( b != a and c == a )
                ++ans;
        }

        return ans;
    }
};
