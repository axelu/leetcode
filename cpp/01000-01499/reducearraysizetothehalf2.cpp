






// 1338. Reduce Array Size to The Half
// https://leetcode.com/problems/reduce-array-size-to-the-half/
// day 6 July 2021 challenge
// https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/608/week-1-july-1st-july-7th/3804/



class Solution {
public:
    int minSetSize(vector<int>& arr) {
        int n = arr.size();

        int cnt[100001];memset(cnt,0,sizeof cnt);
        for(int i = 0; i < n; ++i)
            ++cnt[arr[i]];

        priority_queue<int> pq;
        for(int i = 0; i < 100001; ++i)
            if( cnt[i] > 0 )
                pq.push(cnt[i]);

        int ans = 0;
        int sz  = 0;
        while( sz < n/2 ) {
            sz += pq.top();
            pq.pop();
            ++ans;

        }

        return ans;
    }
};
