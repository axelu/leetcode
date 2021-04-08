
// 1311. Get Watched Videos by Your Friends
// https://leetcode.com/problems/get-watched-videos-by-your-friends/




class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {

        int n = friends.size(); // n == watchedVideos.length == friends.length

        // BFS
        // friends is an undirected graph
        // we are rooting the graph in id

        queue<pair<int,int>> q; // person,level
        int seen[n]; memset(seen,0,sizeof seen);

        q.push({id,0});
        seen[id] = 1;
        unordered_map<string,int> videos;
        pair<unordered_map<string,int>::iterator,bool> p;
        while( !q.empty() ) {
            if( q.front().second == level )
                // gather videos
                for(int i = 0; i < watchedVideos[q.front().first].size(); ++i) {
                    p = videos.insert({watchedVideos[q.front().first][i],1});
                    if( !p.second )
                        ++p.first->second;
                }
            else
                for(int i = 0; i < friends[q.front().first].size(); ++i)
                    if( !seen[friends[q.front().first][i]] ) {
                        seen[friends[q.front().first][i]] = 1;
                        q.push({friends[q.front().first][i],q.front().second+1});
                    }
            q.pop();
        }

        auto cmp = [](pair<string,int>& left, pair<string,int>& right) {
            if( left.second > right.second )
                return true;
            else if( left.second == right.second )
                if( left.first > right.first ) return true;
            return false;
        };
        priority_queue<pair<string,int>,vector<pair<string,int>>,decltype(cmp)> pq(cmp);
        for(auto it = videos.begin(); it != videos.end(); ++it)
            pq.push(*it);

        vector<string> ans(pq.size());
        int i = 0;
        while( !pq.empty() ) {
            ans[i] = pq.top().first;
            pq.pop();
            ++i;
        }
        return ans;
    }
};
