
// 1122. Relative Sort Array
// https://leetcode.com/problems/relative-sort-array/

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        size_t n = arr2.size();
        unordered_map<int,int> um(n);
        for(int i = 0; i < n; ++i)
            um[arr2[i]] = i;
        unordered_map<int,int>::iterator ume = end(um);
        
        sort(begin(arr1),end(arr1),[um,ume](const int& a, const int& b){
            auto a_search = um.find(a);
            auto b_search = um.find(b);
            
            if( a_search != ume && b_search != ume ) {
                // both a and b are in arr2
                return a_search->second < b_search->second;
            } else if( a_search != ume && b_search == ume ) {
                // a in arr2, b NOT in arr2
                return true;
            } else if( a_search == ume && b_search != ume ) {
                // a NOT in arr2, b in arr2
                return false;
            }
            
            // neither a nor b are in arr2
            return a < b;
        });
        
        return arr1;
    }
};
