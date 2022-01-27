
// 841. Keys and Rooms
// https://leetcode.com/problems/keys-and-rooms/
// day 19 March 2021 challenge
// https://leetcode.com/explore/featured/card/march-leetcoding-challenge-2021/590/week-3-march-15th-march-21st/3677/



class Solution {
private:
    int N;
    int visited[1000];

    void dfs(vector<vector<int>>& rooms, int idx) {
        if( visited[idx] ) return;
        visited[idx] = 1;

        for(int i = 0; i < rooms[idx].size(); ++i)
            dfs(rooms,rooms[idx][i]);
    }

public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        N = rooms.size();

        for(int i = 0; i < N; ++i) visited[i] = 0;
        dfs(rooms,0);
        for(int i = 0; i < N; ++i)
            if( !visited[i] ) return false;
        return true;
    }
};
