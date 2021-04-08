
// 697. Degree of an Array
// https://leetcode.com/problems/degree-of-an-array/



class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        int n = nums.size();

        unordered_map<int,array<int,3>> um; // int,{freq,firstidx,lastidx}
        pair<unordered_map<int,array<int,3>>::iterator,bool> p;
        for(int i = 0; i < n; ++i) {
            p = um.insert({nums[i],{1,i,i}});
            if( !p.second) {
                ++p.first->second[0];
                p.first->second[2] = i;
            }
        }

        vector<array<int,3>> v;
        for(auto it = um.begin(); it != um.end(); ++it)
            v.push_back(it->second);

        sort(v.begin(),v.end(),[](array<int,3>& a, array<int,3> b){
            if( a[0] > b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[2] - a[1] < b[2] - b[1] )
                    return true;
            }
            return false;
        });

        return v[0][2] - v[0][1] + 1;
    }
};
