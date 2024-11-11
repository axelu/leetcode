
// 2248. Intersection of Multiple Arrays
// https://leetcode.com/problems/intersection-of-multiple-arrays/


class Solution {
public:
    vector<int> arraysIntersection(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {
        int n = arr1.size(); // 1 <= arr1.length, arr2.length, arr3.length <= 1000        
        map<int,int> m;
        vector<vector<int>> v = {arr1,arr2,arr3};
        pair<map<int,int>::iterator,bool> p;
        vector<int> ans;
        for(int i = 0; i < n; ++i)
            for(vector<int> arr : v) {
                if( arr.size() > i ) {
                    p = m.insert({arr[i],1});
                    if( !p.second ) {
                        ++p.first->second;
                        if( p.first->second == 3 ) ans.push_back(p.first->first);
                    }
                }
            }
        return ans;
    }
};
