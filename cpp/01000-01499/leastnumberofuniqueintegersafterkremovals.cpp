
// 1481. Least Number of Unique Integers after K Removals
// https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/



class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        // we want to remove as many unique integers as possible

        unordered_map<int,int> us; // val,count
        for(int x: arr)
            ++us[x];

        int n = us.size(); // number of unique int in arr

        vector<pair<int,int>> v(n);
        int i = 0;
        for(auto p: us)
            v[i++] = p;

        sort(v.begin(),v.end(),[](const pair<int,int>& a, const pair<int,int>& b){
           return a.second < b.second;
        });

        int t = 0;
        for(int i = 0; i < n; ++i) {
            if( v[i].second <= k ) {
                // we can remove all occurences of the curr unique int
                ++t;
                k -= v[i].second;
            } else {
                break;
            }
        }

        return n-t;
    }
};
