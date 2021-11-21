
// 332. Reconstruct Itinerary
// https://leetcode.com/problems/reconstruct-itinerary/





class Solution {
private:

    bool dfs(vector<pair<string,int>> g[], int src, int step, int n,
             unordered_map<string,int>& um, vector<string>& ans, int seen[]) {
        // returns true if all tickets where consumed

        if( step == n ) return true;

        string dest;
        int destId,edgeId;
        unordered_set<int> seenl;
        bool f;
        for(int i = 0; i < g[src].size(); ++i) {
            dest   = g[src][i].first;
            destId = um.find(dest)->second;
            edgeId = g[src][i].second;

            if( seen[edgeId] )
                continue;

            if( seenl.count(destId) )
                continue;
            seenl.insert(destId);

            ans.push_back(dest);
            seen[edgeId] = 1;

            f = dfs(g,destId,step+1,n,um,ans,seen);
            if( f ) return true;

            // backtrack
            ans.pop_back();
            seen[edgeId] = 0;
        }
        return false;
    }

public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // tickets == edge list
        int n = tickets.size();

        int id = 0;
        unordered_map<string,int> um;  // airportcode,airportid
        unordered_map<string,int>::iterator f;
        vector<pair<string,int>> g[n+1]; // directed graph
        int src,dest;
        for(int i = 0; i < n; ++i) {
            // from
            f = um.find(tickets[i][0]);
            if( f == um.end() ) {
                um.insert({tickets[i][0],id});
                src = id;
                ++id;
            } else {
                src = f->second;
            }
            // to
            f = um.find(tickets[i][1]);
            if( f == um.end() ) {
                um.insert({tickets[i][1],id});
                dest = id;
                ++id;
            } else {
                dest = f->second;
            }
            g[src].push_back({tickets[i][1],i}); // dest,edgeid
        }

        // sort outgoing edges for every node
        for(int i = 0; i < id; ++i)
            sort(g[i].begin(),g[i].end(),[](const pair<string,int>& a, const pair<string,int>& b){
                return a.first < b.first;
            });


        vector<string> ans;
        ans.push_back("JFK");
        // JFK
        src = um.find("JFK")->second;
        int seen[n];memset(seen,0,sizeof seen);
        dfs(g,src,0,n,um,ans,seen);
        return ans;
    }
};
