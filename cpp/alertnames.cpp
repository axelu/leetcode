
// 1604. Alert Using Same Key-Card Three or More Times in a One Hour Period
// https://leetcode.com/problems/alert-using-same-key-card-three-or-more-times-in-a-one-hour-period/


class Solution {
public:
    vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
        auto n = keyName.size(); // keyName.length == keyTime.length
        unordered_map<string,vector<string>> um;
        for(int i = 0; i < n; ++i) {
            auto p = um.insert({keyName[i],{keyTime[i]}});
            if( !p.second )
                p.first->second.push_back(keyTime[i]);
        }

        vector<string> r;
        vector<string> * t;
        size_t m;
        int a,b;
        for(auto it = begin(um); it != end(um); ++it) {
            t = &it->second;
            m = t->size();
            if( m > 2 ) {
                sort(begin(*t),end(*t));
                for(int i = 0; i < m-2; ++i) {
                    a = stoi((*t)[i].substr(0,2)) * 60 + stoi((*t)[i].substr(3,2));
                    b = stoi((*t)[i+2].substr(0,2)) * 60 + stoi((*t)[i+2].substr(3,2));
                    if( b - a <= 60 ) {
                        r.push_back(it->first);
                        break;
                    }
                }
            }
        }
        sort(begin(r),end(r));
        return r;
    }
};
