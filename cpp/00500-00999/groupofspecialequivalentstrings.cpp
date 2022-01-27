
// 893. Groups of Special-Equivalent Strings
// https://leetcode.com/problems/groups-of-special-equivalent-strings/




class Solution {
public:
    int numSpecialEquivGroups(vector<string>& A) {
        int n = A.size();
        unordered_set<string> us;
        string odd,even;
        for(int i = 0; i < n; ++i) {
            odd = "";
            even = "";
            for(int j = 0; j < A[i].size(); ++j) {
                if( j % 2 ) even += A[i][j];
                else odd += A[i][j];
            }
            sort(even.begin(),even.end());
            sort(odd.begin(),odd.end());
            us.insert(even + odd);
        }
        return us.size ();
    }
};
