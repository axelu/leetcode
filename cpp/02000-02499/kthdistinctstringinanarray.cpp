
// 2053. Kth Distinct String in an Array
// https://leetcode.com/problems/kth-distinct-string-in-an-array/




class Solution {
public:
    string kthDistinct(vector<string>& arr, int k) {
        unordered_map<string,int> um; // key,idx
        pair<unordered_map<string,int>::iterator,bool> p;

        int idx = 0;
        vector<pair<string,int>> v; // key,cnt

        for(int i = 0; i < arr.size(); ++i) {
            p = um.insert({arr[i],idx});
            if( p.second ) {
                v.push_back({arr[i],1});
                ++idx;
            } else {
                ++v[p.first->second].second;
            }
        }

        int t = 0;
        for(int i = 0; i < v.size(); ++i)
            if( v[i].second == 1 ) {
                ++t;
                if( t == k )
                    return v[i].first;
            }

        return "";
    }
};
