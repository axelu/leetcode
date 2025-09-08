

// 3623. Count Number of Trapezoids I
// https://leetcode.com/problems/count-number-of-trapezoids-i/




class Solution {
private:
    const long mod = 1000000007;
public:
    int countTrapezoids(vector<vector<int>>& points) {
        // points is a 2D integer array points,
        // where points[i] = [xi, yi] represents the coordinates
        // of the ith point on the Cartesian plane

        int n = points.size();

        // we will count the number of points on each horizontal line
        // if there are 2 or more points, we can use that horizontal line
        // on each line, we can make number of pairs formula n * (n-1)/2,
        // where n is the number of points on that horizontal line
        // we need to multiply them

        map<int, long> h; // key: y value: count of points where yi == y
        for(int i = 0; i < n; ++i)
            ++h[points[i][1]];

        // debug
        // for(auto it = h.begin(); it != h.end(); ++it)
        //     cout << "y " << it->first << " nbr points " << it->second << endl;

        int h_sz = h.size();
        vector<long> suffixSum(h_sz);
        suffixSum[h_sz-1] = 0L;
        auto itr = h.rbegin();
        for(int i = h_sz-2; i >= 0; --i) {
            long pairs = (itr->second * (itr->second - 1)/2L) % mod;
            suffixSum[i] = (suffixSum[i+1] + pairs) % mod;
            ++itr;
        }

        long ans = 0L;
        auto it = h.begin();
        for(int i = 0; i < h_sz-1; ++i) {
            long pairs = (it->second * (it->second - 1L)/2L) % mod;
            ans = (ans + ((pairs * suffixSum[i]) % mod)) % mod;
            ++it;
        }

        return ans;
    }
};
