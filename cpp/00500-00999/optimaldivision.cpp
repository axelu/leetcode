
// 553. Optimal Division
// https://leetcode.com/problems/optimal-division/


class Solution {
private:
    string v2s(vector<int>& nums, int s, int e) {
        // strategy 0 max, 1 min
        if( e-s == 0 )
            return to_string(nums[s]);

        string t = "";
        for(int i = s; i <= e; ++i) {
            if( i > s )
                t += "/";
            t += to_string(nums[i]);
        }
        return t;
    }

    pair<string,double> mem[10][10][2];

    pair<string,double> rec(vector<int>& nums, int strategy, int s, int e) {
        // cout << " strategy " << strategy << " s " << s << " e " << e << endl;
        // strategy 0 max, 1 min
        if( e-s == 0 )
            return {v2s(nums,s,e),nums[s]};

        if( e-s == 1 )
            return {v2s(nums,s,e),(double)nums[s]/nums[e]};

        if( !mem[s][e][strategy].first.empty() )
            return mem[s][e][strategy];

        // if strategy is max: left max, right min
        // if strategy is min: left min, right max
        // left  [s,i]
        // right [i+1][e]

        pair<string,double> gl;
        pair<string,double> gr;

        if( strategy == 0 ) { // max
            pair<string,double> l;
            pair<string,double> r;
            double mx = -1.0;
            for(int i = s; i < e; ++i) {
                l = rec(nums,0,s,i);
                r = rec(nums,1,i+1,e);
                double t = l.second/r.second;
                // cout << t << endl;
                if( t > mx ) {
                    mx = t;
                    gl = l;
                    gr = r;
                }
            }
        } else {
            pair<string,double> l;
            pair<string,double> r;
            double mn = DBL_MAX;
            for(int i = s; i < e; ++i) {
                l = rec(nums,1,s,i);
                r = rec(nums,0,i+1,e);
                double t = l.second/r.second;
                if( t < mn ) {
                    mn = t;
                    gl = l;
                    gr = r;
                }
            }
        }

        // wrap right in paranthesis?
        bool wrap = false;
        for(char c : gr.first)
            if( !isdigit(c) )
                wrap = true;

        string t = "";
        t += gl.first+"/";
        t += wrap ? "("+gr.first+")" : gr.first;

        return mem[s][e][strategy] = {t,gl.second/gr.second};
    }

public:
    string optimalDivision(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return to_string(nums[0]);
        if( n == 2 )
            return to_string(nums[0])+"/"+to_string(nums[1]);

        return to_string(nums[0])+"/"+"("+v2s(nums,1,n-1)+")";

        // works
        // return rec(nums,0,0,nums.size()-1).first;
    }
};
