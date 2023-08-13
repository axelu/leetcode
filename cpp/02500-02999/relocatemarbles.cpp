
// 2766. Relocate Marbles
// https://leetcode.com/problems/relocate-marbles/



class Solution {
public:
    vector<int> relocateMarbles(vector<int>& nums, vector<int>& moveFrom, vector<int>& moveTo) {


        set<int> st;
        for(int pos: nums)
            st.insert(pos);

        int moves_sz = moveFrom.size(); // moveFrom.size() == moveTo.size()
        for(int i = 0; i < moves_sz; ++i) {
            st.erase(moveFrom[i]);
            st.insert(moveTo[i]);
        }

        vector<int> ans(st.begin(),st.end());
        return ans;
    }
};
