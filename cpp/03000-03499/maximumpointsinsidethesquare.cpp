
// 3143. Maximum Points Inside the Square
// https://leetcode.com/problems/maximum-points-inside-the-square/




class Solution {
public:
    int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
        int n = s.size(); // s.length == points.length

        map<int,array<int,26>> um;
        for(int i = 0; i < n; ++i) {
            int t = max(abs(points[i][0]), abs(points[i][1]));
            ++um[t][s[i]-'a'];
        }

        int ans = 0;

        int cnt[26];memset(cnt,0,sizeof cnt);
        for(auto it = um.begin(); it != um.end(); ++it) {
            // cout << it->first << " ";
            int t = 0;
            bool flag = true;
            for(int i = 0; i < 26; ++i) {
                // cout << (char)('a' + i) << ":" <<  it->second[i] << " ";
                if( it->second[i] > 1 || it->second[i] + cnt[i] > 1 ) {
                    flag = false;
                    break;
                }
                if( !flag )
                    break;
                t += it->second[i];
                cnt[i] += it->second[i];
            }
            // cout << endl;
            if( !flag )
                break;
            ans += t;
        }

        return ans;
    }
};
