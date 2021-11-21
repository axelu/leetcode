
// 1436. Destination City
// https://leetcode.com/problems/destination-city/

class Solution {
public:
    string destCity(vector<vector<string>>& paths) {
        unordered_set<string> dep; // departure cities
        unordered_set<string> dst; // destination cities

        unordered_set<string>::iterator itdep;
        unordered_set<string>::iterator itdst;
        for(auto vs : paths) {
            // process departure city
            dep.insert(vs[0]);
            itdst = dst.find(vs[0]);
            if( itdst != dst.end() ) dst.erase(itdst);
            // process destination city
            itdep = dep.find(vs[1]);
            if( itdep == dep.end() ) {
                dst.insert(vs[1]);
            } else {
                itdst = dst.find(vs[1]);
                if( itdst != dst.end() ) dst.erase(itdst);
            }
        }

        return *dst.begin();
    }
};
