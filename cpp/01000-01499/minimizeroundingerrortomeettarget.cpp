
// 1058. Minimize Rounding Error to Meet Target
// https://leetcode.com/problems/minimize-rounding-error-to-meet-target/




class Solution {
private:

    unordered_map<int,double> mem;

    double rec(vector<string>& prices, int n, int i, int target) {
        if( target < 0 )
            return -1.0;

        if( i == n )
            return target == 0 ? 0.0 : -1.0;

        // we have a choice
        //    round down Floor(pi) OR
        //    round up Ceil(pi)

        int key = i * 1000000 + target;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        double val = stod(prices[i]);

        // down
        int d = floor(val);
        double a_roundingerr = val - d;
        double a = rec(prices,n,i+1,target-d);

        // up
        int u = ceil(val);
        double b_roundingerr = u - val;
        double b = rec(prices,n,i+1,target-u);

        double ret = -1.0;

        if( a != -1.0 && b == -1.0 ) {
            ret = a_roundingerr + a;
        } else if( a == -1.0 && b != -1.0  ) {
            ret = b_roundingerr + b;
        } else if( a != -1.0 && b != -1.0  ) {
            ret =  min(a_roundingerr + a, b_roundingerr + b);
        }

        return mem[key] = ret;
    }

public:
    string minimizeError(vector<string>& prices, int target) {
        int n = prices.size();

        double ret = rec(prices,n,0,target);
        if( ret == -1.0 )
            return "-1";

        // C++20
        // return format("{:.3f}", ret);

        stringstream stream;
        stream << fixed << std::setprecision(3) << ret;
        return stream.str();
    }
};
