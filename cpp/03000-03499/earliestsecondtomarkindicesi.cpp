
// 3048. Earliest Second to Mark Indices I
// https://leetcode.com/problems/earliest-second-to-mark-indices-i/





class Solution {
private:
    pair<vector<pair<int,int>>,bool> get_latest(vector<int>& changeIndices, int i, int n) {
        vector<pair<int,int>> latest(n); // latest second, index (1-indexed)
        vector<bool> seen(n,false);
        int cnt = 0;
        for(; i >= 0; --i) {
            if( !seen[changeIndices[i]-1] ) {
                seen[changeIndices[i]-1] = true;
                ++cnt;
                latest[changeIndices[i]-1] = {i+1, changeIndices[i]};
            }
        }
        if( cnt < n )
            return {{},false};

        sort(latest.begin(),latest.end(),[](const pair<int,int>& a, const pair<int,int>& b){
            return a.first < b.first;
        });

        return {latest,true};
    }

    bool solve(vector<int>& nums, int n, vector<pair<int,int>> latest) {
        // latest: by second latest[i].first we have to have index latest[i].second (1-indexed marked)

        long spent_seconds = 0l;
        for(int i = 0; i < n; ++i) {
            long sec = (long)latest[i].first;            // latest second at which we can mark
            long val = (long)nums[latest[i].second - 1];

            // we will need to spend val + 1 seconds to mark
            spent_seconds += val + 1L;
            if( spent_seconds > sec )
                return false;
        }

        return true;
    }

    // binary search
    int search(vector<int>& nums, int n, vector<int>& changeIndices, int m, int s, int e) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        auto p = get_latest(changeIndices, mid, n);
        if( p.second && solve(nums, n, p.first) ) {
            // can we do better?
            int t = search(nums, n, changeIndices, m, s, mid-1);
            return t != -1 ? t : mid;
        }
        return search(nums, n, changeIndices, m, mid+1, e);
    }

public:
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        int n = nums.size();            // 1-indexed
        int m = changeIndices.size();   // 1 <= changeIndices[i] <= n; 1-indexed

        // quick check
        // all indicies [1,n] inclusive must be in change indicies for there to be a solution
        // there is no solution if nums[i] >= last second i appears in change indicies
        // there also in no solution if the total of nums[i] + n > m
        // there also is no solution if m < n because even if all nums[i] == 0, we still need time to mark them
        if( m < n )
            return -1;

        int ans = search(nums, n, changeIndices, m, n-1, m-1);
        return ans != -1 ? ans + 1 : -1;
    }
};
