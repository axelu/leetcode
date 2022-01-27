
// 2092. Find All People With Secret
// https://leetcode.com/problems/find-all-people-with-secret/



class Solution {
private:
    // binary search lower bound equal or greater
    int search(vector<array<int,2>>& arr, int s, int e, int x) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( arr[mid][1] >= x ) {
            // can we do better?
            int t = search(arr,s,mid-1,x);
            return t != -1 ? t : mid;
        } else {
            // arr[mid][1] < x
            return search(arr,mid+1,e,x);
        }
    }

    void dfs(vector<array<int,2>> g[], int u, int t, int seen[]) {
        // cout << "dfs " << u << " t " << t << endl;
        // we were already here at a better time
        if( seen[u] != -1 && seen[u] <= t )
            return;

        int pre = seen[u] != -1 ? seen[u] : 100001;
        seen[u] = t;

        // we will proceed from here to all edges
        // with a time >= t
        int n = g[u].size();
        int i = search(g[u],0,n-1,t);
        if( i == -1 )
            return;
        for(; i < n; ++i) {
            if( g[u][i][1] >= pre )
                break;
            dfs(g,g[u][i][0],g[u][i][1],seen);
        }

    }
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        // sort meetings by time non-decreasing
        sort(meetings.begin(),meetings.end(),[](const vector<int>& a, const vector<int>& b){
           return a[2] < b[2];
        });

        // undirected weighted graph
        vector<array<int,2>> g[n];
        // first person
        g[0].push_back({firstPerson,0});
        g[firstPerson].push_back({0,0});
        for(auto& m : meetings) {
            // cout << m[0] << " " << m[1] << " " << m[2] << endl;
            g[m[0]].push_back({m[1],m[2]});
            g[m[1]].push_back({m[0],m[2]});
        }

        // we will do a dfs starting from person 0
        int seen[n];memset(seen,-1,sizeof seen);

        vector<int> ans;
        dfs(g,0,0,seen);
        for(int i = 0; i < n; ++i) {
            // cout << i << ":" << seen[i] << " ";
            if( seen[i] != -1 )
                ans.push_back(i);
        }
        // cout << endl;

        return ans;
    }
};
