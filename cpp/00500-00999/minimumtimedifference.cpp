
// 539. Minimum Time Difference
// https://leetcode.com/problems/minimum-time-difference/





class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        int n = timePoints.size(); // 2 <= timePoints.size() <= 2*10^4

        // convert to minutes 00:00 -> 0, 23:59 -> 1439
        vector<int> tp(n);
        int hh,mm;
        for(int i = 0; i < n; ++i) {
            hh = stoi(timePoints[i].substr(0,2));
            mm = stoi(timePoints[i].substr(3,2));
            tp[i] = hh*60+mm;
        }
        sort(begin(tp),end(tp));
        /*
        for(int i = 0; i < n; ++i)
            cout << tp[i] << " ";
        cout << endl;
        */

        int ans = 1401;
        for(int i = 1; i < n; ++i)
            ans = min(ans,tp[i]-tp[i-1]);

        // wrap around
        ans = min(ans,tp[0]+(1440-tp[n-1]));

        return ans;
    }
};
