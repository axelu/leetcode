
// 2976. Minimum Cost to Convert String I
// https://leetcode.com/problems/minimum-cost-to-convert-string-i/




class Solution {
private:
    const int INF = 100000001;
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {

        // we need to figure out the cheapest cost to convert character x to character y
        // once we know that, we can simply go from left to right through source and add up the cost
        // we will treat original and changed as a edges in a directed weighted graph

        // Floyd-Warshall
        int dist[26][26];
        for(int i = 0; i < 26; ++i)
            for(int j = 0; j < 26; ++j)
                dist[i][j] = INF; // max 26 steps x max cost 1000000 -> 26000000 worst case

        for(int i = 0; i < cost.size(); ++i) {
            int u = original[i] - 'a';
            int v = changed[i] - 'a';
            int w = cost[i];
            // only use if smaller
            dist[u][v] = min(dist[u][v], w);
        }

        for(int i = 0; i < 26; ++i)
            dist[i][i] = 0;

        for(int k = 0; k < 26; ++k)
            for(int i = 0; i < 26; ++i)
                for(int j = 0; j < 26; ++j)
                    if( dist[i][j] > dist[i][k] + dist[k][j] )
                        dist[i][j] = dist[i][k] + dist[k][j];

        long long ans = 0LL;

        for(int i = 0; i < source.size(); ++i) {
            int u = source[i] - 'a';
            int v = target[i] - 'a';
            int w = dist[u][v];
            if( w == INF )
                return -1;

            ans += (long long) w;
        }

        return ans;
    }
};
