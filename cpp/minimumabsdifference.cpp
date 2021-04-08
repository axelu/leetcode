
// 1200. Minimum Absolute Difference
// https://leetcode.com/problems/minimum-absolute-difference/


class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        auto itb = begin(arr);
        auto ite = end(arr);
        sort(itb,ite);

        int mindiff = 2000001;
        for(auto it = next(itb); it != ite; ++it)
            mindiff = min(mindiff,abs(*(it-1) - *it));

        vector<vector<int>> r;
        vector<int> t;
        for(auto it = next(itb); it != ite; ++it)
            if( abs(*(it-1) - *it) == mindiff ) {
                if( *(it-1) < *it ) {t = {*(it-1),*it};}
                else {t = {*it,*(it-1)};}
                r.push_back(t);
            }

        return r;
    }
};
