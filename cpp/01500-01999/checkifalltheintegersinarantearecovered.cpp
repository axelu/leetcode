
// 1893. Check if All the Integers in a Range Are Covered
// https://leetcode.com/problems/check-if-all-the-integers-in-a-range-are-covered/






class Solution {
private:
    // binary search largest element less or equal element
    int search(vector<vector<int>>& arr, int s, int e, int target) {
        if( s > e ) return -1;

        int mid = s + ((e - s)/2);
        if( arr[mid][0] == target ) {
            return mid;
        } else if( arr[mid][0] > target ) {
            return search(arr,s,mid-1,target);
        } else {
            // can we do better?
            int ans = search(arr,mid+1,e,target);
            return ans != -1 ? ans : mid;
        }
    }

public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        int n = ranges.size();

        if( n == 1 )
            return ranges[0][0] <= left && ranges[0][1] >= right;


        // merge intervals
        sort(ranges.begin(),ranges.end());
        /*
        for(auto vi : ranges)
            cout << vi[0] << " " << vi[1] << endl;
        */
        vector<vector<int>> r;
        r.push_back(ranges[0]);
        int i, base = 0;
        for(i = 1; i < n; ++i) {

            if( ranges[i][0] <= r[base][1] + 1 ) {
                r[base][1] = max(r[base][1],ranges[i][1]);
            } else {
                r.push_back(ranges[i]);
                ++base;
            }
        }
        /*
        for(auto vi : r)
            cout << vi[0] << " " << vi[1] << endl;
        */


        // check [left,right] inclusive
        int t;
        for(i = left; i <= right; ++i) {
            // cout << "i " << i << endl;

            t = search(r,0,r.size()-1,i);
            if( t == -1 || r[t][1] < i )
                return false;
        }

        return true;
    }
};
