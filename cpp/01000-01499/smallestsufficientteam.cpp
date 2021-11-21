
// 1125. Smallest Sufficient Team
// https://leetcode.com/problems/smallest-sufficient-team/




class Solution {
private:
    // debug
    void printBinary(long x, int c) {
        for(int i = c-1; i >= 0; --i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }    
    
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        int n = req_skills.size();                  // number of skills required for this project
        unordered_map<string,int> um;               // skill,idx
        for(int i = 0; i < n; ++i)
            um.insert({req_skills[i],i});
        
        int k = people.size();                      // number of people to choose from
        unordered_map<int,vector<array<int,2>>> sp; // skill:{{person,skillMask},{person,skillMask},...}
        int skillMask;
        for(int i = 0; i < k; ++i) {
            skillMask = 0;
            for(int j = 0; j < people[i].size(); ++j)
                skillMask |= 1 << um[people[i][j]];
            // cout << "person " << i << " ";printBinary(skillMask,n);cout << endl;
            for(int j = n-1; j >= 0; --j) {
                if( skillMask & (1UL << j) ) {
                    auto p = sp.insert({j,{{i,skillMask}}});
                    if( !p.second )
                        p.first->second.push_back({i,skillMask});
                }
            }
        }
        
        // BFS
        queue<pair<int,long>> q;    // skillmask,team
        unordered_set<long> seen;   // team
        q.push({0,0});
        seen.insert(0L);
        int mask;                   // mask are the skills we have collected along our way
        long team;
        int mask_new;
        long team_new;
        while( !q.empty() ) {
            mask = q.front().first;
            team = q.front().second;
            q.pop();
            
            if( mask == (1<<n)-1 )  // we got all the skills we need
                break;
            
            // look for the 1st skill gap we have and
            // add all people people that have that skill
            for(int i = n-1; i >= 0; --i) {
                if( !(mask & (1UL << i)) ) {
                    for(int j = 0; j < sp[i].size(); ++j) {
                        
                        team_new = team | (1UL << sp[i][j][0]);
                        if( seen.count(team_new) )
                            continue;
                            
                        seen.insert(team_new);
                        
                        mask_new = mask | sp[i][j][1];
                        q.push({mask_new,team_new});
                    }
                    break;
                }
            }
            
        }
                
        vector<int> ret;
        for(int i = 59; i >= 0; --i)
            if( team & (1UL << i) ) 
                ret.push_back(i);
        
        return ret;
    }
};
