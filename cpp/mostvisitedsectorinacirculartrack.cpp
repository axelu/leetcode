
// Most Visited Sector in a Circular Track
// https://leetcode.com/problems/most-visited-sector-in-a-circular-track/



class Solution {
public:
    vector<int> mostVisited(int n, vector<int>& rounds) {
        map<int,int> sectors; // map of sectors 1 indexed and their visits;
        for(int i = 1; i <= n; ++i)
            sectors.insert({i,0});

        ++sectors[rounds[0]];
        int m = rounds.size();
        for(int i = 2; i <= m; ++i) {
            int s = rounds[i - 2]; // start sector
            int e = rounds[i - 1]; // end sector
            if( s < n ) {
                if( e > s ) {
                    for(int k = s + 1; k <= e; ++k)
                        ++sectors[k];
                } else {
                    for(int k = s + 1; k <= n; ++k)
                        ++sectors[k];
                    for(int k = 1; k <= e; ++k)
                        ++sectors[k];
                }
            } else { // s == n
                for(int k = 1; k <= e; ++k)
                    ++sectors[k];
            }

        }
/*
        for(auto it = sectors.begin(); it != sectors.end(); ++it)
            cout << "sector " << it->first << " count " << it->second << endl;
*/
        // swap sectors, most visited sectors at the end with values desc
        multimap<int,int> count;
        for(auto it = sectors.rbegin(); it != sectors.rend(); ++it)
            count.insert(make_pair(it->second, it->first));
/*
        for(auto it = count.begin(); it != count.end(); ++it)
            cout << "count " << it->first << " sector " << it->second << endl;
*/
        vector<int> r;
        int max = count.rbegin()->first;
        auto it = count.rbegin();
        while( it->first == max && it != count.rend() ) {
            r.push_back(it->second);
            ++it;
        }

        return r;
    }
};
