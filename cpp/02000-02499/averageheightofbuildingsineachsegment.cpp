
// 2015. Average Height of Buildings in Each Segment
// https://leetcode.com/problems/average-height-of-buildings-in-each-segment/




class Solution {
public:
    vector<vector<int>> averageHeightOfBuildings(vector<vector<int>>& buildings) {
        sort(buildings.begin(),buildings.end(),[](const vector<int>& a, const vector<int>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) {
                    return true;
                }
            }
            return false;
        });

        map<int,pair<int,int>> mp;

        for(auto it = buildings.begin(); it != buildings.end(); ++it) {
            int start  = (*it)[0];
            int end    = (*it)[1];
            int height = (*it)[2];

            mp[start].first += 1;
            mp[start].second += height;

            mp[end].first  -= 1;
            mp[end].second -= height;

        }

        vector<vector<int>> ans;

        int cnt = 0;
        int hgt = 0;
        vector<int> t = {};
        for(auto it = mp.begin(); it != mp.end(); ++it) {
            if( !t.empty() ) {
                if( !ans.empty() && ans.back()[2] == t[2] && ans.back()[1] == t[0] ) {
                    ans.back()[1] = it->first;
                } else {
                    t[1] = it->first;
                    ans.push_back(t);
                }
            }

            cnt += it->second.first;
            hgt += it->second.second;
            // cout << it->first << " cnt " << cnt << " hgt " << hgt << endl;

            if( cnt > 0 ) {
                t = {it->first,-1,hgt/cnt};
            } else {
                t = {};
            }
        }






        return ans;
    }
};
