
// 2070. Most Beautiful Item for Each Query
// https://leetcode.com/problems/most-beautiful-item-for-each-query/



class Solution {
public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        int qsz = queries.size();

        vector<array<int,2>> _queries(qsz); // queries idx,price
        for(int i = 0; i < qsz; ++i)
            _queries[i] = {i,queries[i]};
        // sort queries by price asc
        sort(_queries.begin(),_queries.end(),[](const array<int,2>& a, const array<int,2>&b){
            return a[1] < b[1];
        });

        // sort items by price asc
        sort(items.begin(),items.end(),[](const vector<int>& a, const vector<int>&b){
            return a[0] < b[0];
        });


        vector<int> ans(qsz,0);
        int mxBeauty = 0;
        int i = 0; // index in sorted items list
        for(int j = 0; j < qsz; ++j) {
            int query_idx   = _queries[j][0];
            int query_price = _queries[j][1];

            while( i < items.size() && items[i][0] <= query_price ) {
                mxBeauty = max(mxBeauty,items[i][1]);
                ++i;
            }

            ans[query_idx] = mxBeauty;
        }

        return ans;
    }
};
