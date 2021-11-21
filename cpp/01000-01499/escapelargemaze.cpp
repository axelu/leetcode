
// 1036. Escape a Large Maze
// https://leetcode.com/problems/escape-a-large-maze/


class Solution {
private:
    unordered_set<long long> blckd;
    bool reachedTarget;

    bool isEscapePossible(vector<int>& source, vector<int>& target) {
        int m = 1000000;
        int n = 1000000;
        int d = blckd.size(); // distance to be reached in cardinal direction

        // direction right,down,left,up
        int dirX[] = {0,1,0,-1};
        int dirY[] = {1,0,-1,0};

        // BFS
        unordered_set<long long> seen;
        queue<pair<int,int>> q;
        q.push({source[0],source[1]});
        seen.insert((long long)source[0]*1000000 +source[1]);
        int x,y,x_new,y_new;
        unordered_set<long long>::iterator be = blckd.end();
        while(!q.empty()) {
            x = q.front().first;
            y = q.front().second;
            q.pop();

            // explore in all 4 directions
            for(int i = 0; i < 4; ++i) {

                x_new = x + dirX[i];
                if( x_new < 0 || x_new == m )
                    continue;

                y_new = y + dirY[i];
                if( y_new < 0 || y_new == n )
                    continue;

                // blocked?
                if( blckd.find((long long)x_new*1000000 + y_new) != be )
                    continue;

                // seen?
                if( seen.find((long long)x_new*1000000 + y_new) != seen.end() )
                    continue;

                // target?
                if( x_new == target[0] && y_new == target[1] ) {
                    // cout << "reached target" << endl;
                    reachedTarget = true;
                    return true;
                }

                // far enough away?
                if( source[0]+(d-1) == x_new || source[0]-(d-1) == x_new ||
                    source[1]+(d-1) == y_new || source[1]-(d-1) == y_new ) {
                    // cout << x_new << " " << y_new << endl;
                    return true;
                }

                seen.insert((long long)x_new*1000000 + y_new);
                q.push({x_new,y_new});

            }
            // if our queue has more entries or equal number than there are blocked cells,
            // then it cannot be stopped
            if( q.size() >= d ) return true;
        }
        return false;
    }
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        // idea: for both source and target, if we can reach a point in the matrix, that is
        //       sx + blocked.size()-1 = px OR sx - blocked.size()-1 = px OR
        //       sy + blocked.size()-1 = py OR sy - blocked.size()-1 = py OR
        //       tx + blocked.size()-1 = px OR tx - blocked.size()-1 = px OR
        //       ty + blocked.size()-1 = py OR ty - blocked.size()-1 = py
        // then the answer is true

        for(int i = 0; i < blocked.size(); ++i)
            blckd.insert((long long)blocked[i][0]*1000000 + blocked[i][1]);

        reachedTarget = false;

        bool s2t = isEscapePossible(source,target);
        if( !s2t ) return false;
        if( reachedTarget ) return true;

        return isEscapePossible(target,source);
    }
};
