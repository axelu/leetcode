
// 2534. Time Taken to Cross the Door
// https://leetcode.com/problems/time-taken-to-cross-the-door/





class Solution {
private:
    int cross(queue<array<int,2>>& q, int t, int direction, int& out_dir, vector<int>& ans) {
        t = max(t+1, q.front()[0]);
        ans[q.front()[1]] = t;
        q.pop();
        out_dir = direction;
        return t;
    }
public:
    vector<int> timeTaken(vector<int>& arrival, vector<int>& state) {
        int n = arrival.size(); // arrival.size() = state.size()

        vector<int> ans(n);

        queue<array<int,2>> in;
        queue<array<int,2>> out;

        for(int i = 0; i < n; ++i)
            if( state[i] == 0 )
                in.push({arrival[i],i});
            else
                out.push({arrival[i],i});

        int t = -1; // last time the door was used
        int dir;    // 0 enter aka in, 1 out aka exit
        while( !in.empty() && !out.empty() ) {
            int arrival_in  = in.front()[0];
            int arrival_out = out.front()[0];

            if( t == -1 || (arrival_in > t + 1 && arrival_out > t + 1) ) {
                // the door was not used in the previous second
                if( in.front()[0] < out.front()[0] ) {
                    t = cross(in,t,0,dir,ans);

                } else if( in.front()[0] > out.front()[0] ) {
                    t = cross(out,t,1,dir,ans);

                } else { // in.front()[0] == out.front()[0]
                    // the person who wants to exit goes
                    t = cross(out,t,1,dir,ans);
                }

            } else if( arrival_in > t + 1 ) {
                t = cross(out,t,1,dir,ans);
            } else if( arrival_out > t + 1 ) {
                t = cross(in,t,0,dir,ans);
            } else if( dir == 0 ) {
                t = cross(in,t,0,dir,ans);
            } else {
                t = cross(out,t,1,dir,ans);
            }
        }
        // finish up
        // we have people either waiting to enter OR to exit
        // just process them in order
        while( !in.empty() )
            t = cross(in,t,0,dir,ans);
        while( !out.empty() )
            t = cross(out,t,1,dir,ans);

        return ans;
    }
};
