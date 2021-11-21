
// 1488. Avoid Flood in The City
// https://leetcode.com/problems/avoid-flood-in-the-city/




class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        vector<int> ans(n,-1);

        // preprocessing
        unordered_set<int> full;
        pair<unordered_set<int>::iterator,bool> p1;
        unordered_map<int,vector<int>> um; // lake,days it rains on lake (except 1st day)
        pair<unordered_map<int,vector<int>>::iterator,bool> p2;
        for(int i = 0; i < n; ++i) {
            if( rains[i] == 0 )
                continue;
            p1 = full.insert(rains[i]);
            if( !p1.second ) {
                p2 = um.insert({rains[i],{i}});
                if( !p2.second )
                    p2.first->second.push_back(i);
            }
        }

        unordered_map<int,int> nextRainDayIndex; // keeping track of next rain day
        for(auto i : full)
            nextRainDayIndex[i] = 0;


        auto cmp = [](const array<int,2>& a, const array<int,2>& b) {
            return a[1] > b[1];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);

        full.clear();


        int nextRainDayIdx,nextRainDay;
        for(int i = 0; i < n; ++i) {
            if( rains[i] > 0 ) {
                // it is a rain day
                // mark lake as full
                p1 = full.insert(rains[i]);
                if( !p1.second ) // lake was full
                    return {};

                // when does it rain next on this lake? (if ever)
                nextRainDayIdx = nextRainDayIndex[rains[i]];
                if( nextRainDayIdx < um[rains[i]].size() ) {
                    nextRainDay = um[rains[i]][nextRainDayIndex[rains[i]]];
                    ++nextRainDayIndex[rains[i]];
                    pq.push({rains[i],nextRainDay});
                }
            } else {
                // it is a NON rain day, we can drain a lake
                if( !pq.empty() ) {
                    full.erase(pq.top()[0]);
                    ans[i] = pq.top()[0];
                    pq.pop();
                } else {
                    ans[i] = 1000000000;
                }
            }
        }

        return ans;
    }
};
