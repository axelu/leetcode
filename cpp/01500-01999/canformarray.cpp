
// 1640. Check Array Formation Through Concatenation
// https://leetcode.com/problems/check-array-formation-through-concatenation/


class Solution {
public:
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
        auto n = arr.size();
        auto m = pieces.size();

        int i = 0;
        while(i < n) {
            bool found = false;
            for(int j = 0; j < m; ++j) {
                if( pieces[j][0] == arr[i] ) {
                    found = true;
                    int k = pieces[j].size();
                    for(int l = 1; l < k; ++l) {
                        ++i;
                        if( pieces[j][l] != arr[i] ) return false;
                    }
                }
            }
            if( !found ) return false;
            ++i;
        }
        return true;
    }
};
