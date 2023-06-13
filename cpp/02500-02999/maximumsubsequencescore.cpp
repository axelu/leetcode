
// 2542. Maximum Subsequence Score
// https://leetcode.com/problems/maximum-subsequence-score/




class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size(); // nums1.size() == nums2.size()

        vector<array<long long,2>> v(n);
        for(int i = 0; i < n; ++i)
            v[i] = {nums1[i],nums2[i]};

        sort(v.begin(),v.end(),[](const array<long long,2>& a, const array<long long,2>& b){
            return a[1] > b[1];
        });

        long long ans = 0;

        long long sum = 0LL; // running sum
        // we will keep the k-1 largest nums1[0,1,...,i-1], and also nums1[i]
        priority_queue<long long,vector<long long>,greater<long long>> pq;

        for(int i = 0; i < n; ++i) {

            sum += v[i][0];
            pq.push(v[i][0]);

            if( pq.size() == k ) {

                // v[i][1] is our minimum factor as we sorted v by it desc
                ans = max(ans, sum * v[i][1]);

                sum -= pq.top();
                pq.pop();
            }
        }

        return ans;
    }
};
