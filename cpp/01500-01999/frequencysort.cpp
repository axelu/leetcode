
// 1636. Sort Array by Increasing Frequency
// https://leetcode.com/problems/sort-array-by-increasing-frequency/


class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {

        int a[201]; memset(a,0,sizeof a);

        for(auto it = begin(nums);it != end(nums); ++it)
            ++a[*it+100];

        vector<vector<int>> b;
        for(int i = 0; i <=200; ++i)
            if( a[i] > 0 ) b.push_back({a[i],i-100});

        sort(begin(b),end(b),[](vector<int> a, vector<int> b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] && a[1] > b[1] ) {
                return true;
            }
            return false;
        });

        vector<int> r;
        for(auto it = begin(b);it != end(b); ++it)
            for(int i = 0; i < (*it)[0]; ++i)
                r.push_back((*it)[1]);

        return r;
    }
};
