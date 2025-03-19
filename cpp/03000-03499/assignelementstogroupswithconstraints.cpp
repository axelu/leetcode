
// 3447. Assign Elements to Groups with Constraints
// https://leetcode.com/problems/assign-elements-to-groups-with-constraints/





class Solution {
public:
    vector<int> assignElements(vector<int>& groups, vector<int>& elements) {
        // 1 <= groups[i] <= 1e5; 1 <= elements[i] <= 1e5

        int grp_sz = groups.size();
        vector<int> ans(grp_sz, -1);

        // find the element at the smallest index that is a divisor for group[i]

        map<int,vector<int>> _groups;
        for(int i = 0; i < grp_sz; ++i)
            _groups[groups[i]].push_back(i);

        bool seen[100001]; memset(seen,false,sizeof seen);
        for(int i = 0; !_groups.empty() && i < elements.size(); ++i) {
            int div = elements[i];
            if( seen[div] )
                continue;
            // seen[div] = true;

            int grp_mn = _groups.begin()->first;
            int grp_mx = _groups.rbegin()->first;

            int mul = div;
            while( !_groups.empty() && mul <= grp_mx ) {
                seen[mul] = true;
                if( mul < grp_mn ) {
                    mul += div;
                    continue;
                }
                auto f = _groups.find(mul);
                if( f != _groups.end() ) {
                    for(int j = 0; j < f->second.size(); ++j)
                        ans[f->second[j]] = i;
                    _groups.erase(f);
                    if( !_groups.empty() ) {
                        grp_mn = _groups.begin()->first;
                        grp_mx = _groups.rbegin()->first;
                    }
                }
                mul += div;
            }
        }

        return ans;
    }
};
