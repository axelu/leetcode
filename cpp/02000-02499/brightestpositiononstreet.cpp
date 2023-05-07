
// 2021. Brightest Position on Street
// https://leetcode.com/problems/brightest-position-on-street/




// see also 2237. Count Positions on Street With Required Brightness
// https://leetcode.com/problems/count-positions-on-street-with-required-brightness/

class Solution {
    void update(map<int,int>& arr, int l, int r, int val) {
        arr[l] += val;
        arr[r+1] -= val;
    }

public:
    int brightestPosition(vector<vector<int>>& lights) {
        // we assume only one lamp at each position

        map<int,int> arr; // position,'change'

        // update the 'segements' that are illuminated by each light
        // range update
        for(auto& v: lights) {
            // cout << "light pos,range " << v[0] << "," << v[1] << endl;
            // v[0] = position, v[1] = range
            int l = v[0] - v[1]; // cout << "l " << l << endl;
            int r = v[0] + v[1]; // cout << "r " << r << endl;
            update(arr,l,r,1);
        }

        /*
        cout << "pos,change ";
        for(auto it = arr.begin(); it != arr.end(); ++it)
             cout << it->first << "," << it->second << " ";
        cout << endl;
        */

        int brightness = 0, mx_brightness = 0;
        int ans;
        int pre = 0;
        for(auto it = arr.begin(); it != arr.end(); ++it) {
            brightness += it->second;
            if( brightness > mx_brightness ) {
                mx_brightness = brightness;
                ans = it->first;
            }
        }

        return ans;
    }
};
