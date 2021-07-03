
// 1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance
// https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/





class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // n cities numbered from 0 to n-1
        // edges[i] = [u,v,weight] represents a bidirectional and weighted edge between cities
        
        int i,j,k;
        long u,v,w;
        
        // Floyd-Warshall
        // compute any-point to any-point distances
        long dist[n][n]; // minimum distances initialized to ∞ (infinity)
        for(i = 0; i < n; ++i)
            for(j = 0; j < n; ++j)
                dist[i][j] = INT_MAX;
        
        for(i = 0; i < edges.size(); ++i) {
            u = edges[i][0];
            v = edges[i][1];
            w = edges[i][2];
            dist[u][v] = w;
            dist[v][u] = w;
        }    

        for(i = 0; i < n; ++i)
            dist[i][i] = 0;

        for(k = 0; k < n; ++k)
            for(i = 0; i < n; ++i)
                for(j = 0; j < n; ++j)
                    if( dist[i][j] > dist[i][k] + dist[k][j] ) 
                        dist[i][j] = dist[i][k] + dist[k][j];
        
        
        // for each city calculate the number of reachable cities within the threshold
        // return the city with the smallest number of cities that are reachable through 
        // some path and whose distance is at most distanceThreshold, if there are 
        // multiple such cities, return the city with the greatest number
        
        int reachableCities = INT_MAX;
        int ans;
        for(i = 0; i < n; ++i) { // current city
            int c = 0;           // count of reachable cities from current city
            for(j = 0; j < n; ++j) {
                if( i == j ) continue;
                if( dist[i][j] <= distanceThreshold )
                    ++c;
            }
            if( c <= reachableCities ) {
                reachableCities = c;
                ans = i;
            }
        }
        
        return ans;
    }
};
