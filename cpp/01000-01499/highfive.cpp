
// 1086. High Five
// https://leetcode.com/problems/high-five/


class Solution {
public:
    vector<vector<int>> highFive(vector<vector<int>>& items) {
        map<int,multiset<int>> m;
        pair<map<int,multiset<int>>::iterator,bool> p;

        int id,score;
        for(int i = 0; i < items.size(); ++i) {
            id = items[i][0];
            score = items[i][1];
            p = m.insert({id,{score}});
            if( !p.second )
                p.first->second.insert(score);
        }

        vector<vector<int>> ans;
        int cnt,sum,ave;
        for(auto it = m.begin(); it != m.end(); ++it) {
            cnt = 0;
            sum = 0;
            for(auto its = it->second.rbegin(); its != it->second.rend(); ++its) {
                sum += *its;
                ++cnt;
                if( cnt == 5 ) break;
            }
            ave = sum/cnt;
            ans.push_back({it->first,ave});
        }

        return ans;
    }
};
