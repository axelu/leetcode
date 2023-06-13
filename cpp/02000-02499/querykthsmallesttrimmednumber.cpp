
// 2343. Query Kth Smallest Trimmed Number
// https://leetcode.com/problems/query-kth-smallest-trimmed-number/



class Solution {
private:
    // count sort
    vector<pair<int,string>> count_sort(vector<pair<int,string>>& arr, int pos) {
        int n = arr.size();

        vector<pair<int,string>> out(n);
        int i;
        int count[10]; memset(count,0,sizeof count);

        for(i = 0; i < n; ++i)
            ++count[arr[i].second[pos]-'0'];

        // Change count[i] so that count[i] now contains actual
        //  position of this digit in output[]
        for(i = 1; i < 10; ++i)
            count[i] += count[i-1];

        for(i = n - 1; i >= 0; --i) {
            out[count[arr[i].second[pos]-'0']-1] = arr[i];
            --count[arr[i].second[pos]-'0'];
        }

        return out;
    }

public:
    vector<int> smallestTrimmedNumbers(vector<string>& nums, vector<vector<int>>& queries) {
        int nums_sz = nums.size();
        vector<pair<int,string>> numswidx(nums_sz);
        for(int i = 0; i < nums_sz; ++i)
            numswidx[i] = {i,nums[i]};

        int n = nums[0].size();

        int q_sz = queries.size();
        vector<pair<int,vector<int>>> qswidx(q_sz);
        for(int i = 0; i < q_sz; ++i)
            qswidx[i] = {i,queries[i]};
        sort(qswidx.begin(),qswidx.end(),[](const pair<int,vector<int>>& a, const pair<int,vector<int>>& b){
            return a.second[1] < b.second[1];
        });

        vector<int> ans(q_sz);

        int pos = n-1;

        for(int i = 0; i < q_sz; ++i) {
            int q = qswidx[i].first;
            int k = qswidx[i].second[0];
            int trim = qswidx[i].second[1];

            // radix sort
            for(; pos >= n-trim; --pos)
                numswidx = count_sort(numswidx,pos);

            ans[q] = numswidx[k-1].first;
        }

        return ans;
    }
};
