
// 1182. Shortest Distance to Target Color
// https://leetcode.com/problems/shortest-distance-to-target-color/



class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {

        int i;
        int n = colors.size();
        // last seen indexes
        int dist1[n]; // closest idx to the right or left to color1 from idx
        int dist2[n]; // closest idx to the right or left to color2 from idx
        int dist3[n]; // closest idx to the right or left to color3 from idx

        int lastSeen1 = -1, lastSeen2 = -1, lastSeen3 = -1;

        // pass 1 left to right
        for(i = 0; i < n; ++i) {
            // distance to the left
            if( colors[i] == 1 )
                lastSeen1 = i;
            else if( colors[i] == 2 )
                lastSeen2 = i;
            else
                lastSeen3 = i;
            dist1[i] = lastSeen1;
            dist2[i] = lastSeen2;
            dist3[i] = lastSeen3;
        }

        lastSeen1 = -1, lastSeen2 = -1, lastSeen3 = -1;
        // pass 2 right to left
        for(i = n-1; i >= 0; --i) {
            // distance to the right
            if( colors[i] == 1 ) {
                lastSeen1 = i;
            } else if( colors[i] == 2 ) {
                lastSeen2 = i;
            } else  {
                lastSeen3 = i;
            }

            if( dist1[i] == -1 ) {
                dist1[i] = lastSeen1;
            } else if( lastSeen1 != -1 &&  i - dist1[i] > lastSeen1 - i ) {
                dist1[i] =  lastSeen1;
            }

            if( dist2[i] == -1 ) {
                dist2[i] = lastSeen2;
            } else if( lastSeen2 != -1 &&  i - dist2[i] > lastSeen2 - i ) {
                dist2[i] =  lastSeen2;
            }

            if( dist3[i] == -1 ) {
                dist3[i] = lastSeen3;
            } else if( lastSeen3 != -1 &&  i - dist3[i] > lastSeen3 - i ) {
                dist3[i] =  lastSeen3;
            }
        }

        n = queries.size();
        vector<int> ans(n);
        for(i = 0; i < n; ++i) {
           if( queries[i][1] == 1 ) {
               ans[i] = dist1[queries[i][0]] != -1 ? abs(queries[i][0] - dist1[queries[i][0]]) : -1;
           } else if( queries[i][1] == 2 ) {
               ans[i] = dist2[queries[i][0]] != -1 ? abs(queries[i][0] - dist2[queries[i][0]]) : -1;
           } else {
               ans[i] = dist3[queries[i][0]] != -1 ? abs(queries[i][0] - dist3[queries[i][0]]) : -1;
           }
        }

        return ans;
    }
};
