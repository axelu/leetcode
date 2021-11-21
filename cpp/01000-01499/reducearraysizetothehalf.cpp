
// 1338. Reduce Array Size to The Half
// https://leetcode.com/problems/reduce-array-size-to-the-half/



class Solution {
public:
    int minSetSize(vector<int>& arr) {
        int cnt[100001];memset(cnt,0,sizeof cnt);
        int i,n = arr.size();
        for(i = 0; i < n; ++i)
            ++cnt[arr[i]];

        sort(cnt,cnt+100001,greater<int>());
        int sum = 0;
        for(i = 0; sum < n/2; ++i)
            sum += cnt[i];

        return i;
    }
};
