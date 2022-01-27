
// 2137. Pour Water Between Buckets to Make Water Levels Equal
// https://leetcode.com/problems/pour-water-between-buckets-to-make-water-levels-equal/




class Solution {
private:
    // binary search
    double search(vector<int>& buckets, int loss, double s, double e) {
        // cout << "search s " << s << " e " << e << endl;
        // compare float
        if( s > e && e+1e-5 >= s ||
            e > s && s+1e-5 >= e )
            return s;
        if( s > e )
            return -1.0;

        double mid = s + ((e-s)/2.0);
        // cout << "mid " << mid << endl;

        double in = 0.0, out = 0.0;
        for(int i : buckets)
            if( i < mid )
                in += mid - i;
            else if( i > mid )
                out += i - mid;
        // cout << "in " << in << " out " << out << endl;

        if( out-(out*loss/100) >= in ) {
            // can we do better?
            double t = search(buckets,loss,mid,e);
            return t != -1.0 ? t : mid;
        } else {
            return search(buckets,loss,s,mid);
        }
    }

public:
    double equalizeWater(vector<int>& buckets, int loss) {
        double mn = 100000.0;
        double mx = 0.0;

        for(int i : buckets) {
            if( i < mn )
                mn = i;
            if( i > mx )
                mx = i;
        }

        // ans lies between [mn,mx] inclusive
        if( mn == mx )
            return mn;

        return search(buckets,loss,mn,mx);
    }
};
