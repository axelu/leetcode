
// 1423. Maximum Points You Can Obtain from Cards
// https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/
// day 11 May 2021 challenge
// https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/599/week-2-may-8th-may-14th/3739/




class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        if( k == 1 ) return max(cardPoints[0],cardPoints[n-1]);

        int totalPts = 0, sumOfCurrentWindow = 0;
        int i;
        for(i = 0; i < n; ++i) {
            totalPts += cardPoints[i];
            if( i == n-k-1 ) sumOfCurrentWindow = totalPts;
        }
        if( k == n ) return totalPts;

        /*
        cout << "n                  " << n << endl;
        cout << "totalPts           " << totalPts << endl;
        cout << "sumOfCurrentWindow " << sumOfCurrentWindow << endl;
        */

        int ans = totalPts-sumOfCurrentWindow;
        for(i = n-k; i < n; ++i) {
            sumOfCurrentWindow -= cardPoints[i-n+k];
            sumOfCurrentWindow += cardPoints[i];
            ans = max(ans,totalPts-sumOfCurrentWindow);
        }

        return ans;
    }
};
