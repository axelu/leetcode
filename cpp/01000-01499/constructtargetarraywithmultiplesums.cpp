
// 1354. Construct Target Array With Multiple Sums
// https://leetcode.com/problems/construct-target-array-with-multiple-sums/
// day 9 May 2021 challenge
// https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/599/week-2-may-8th-may-14th/3737/



class Solution {
public:
    bool isPossible(vector<int>& target) {
        int n = target.size();
        if( n == 1 ) return target[0] == 1;

        priority_queue<long> pq;
        long sum = 0;
        for(int i = 0; i < n; ++i) {
            sum += (long)target[i];
            pq.push(target[i]);
        }

        long largest,remainder,val;
        while( !pq.empty() && pq.top() > 1 ) {
            largest = pq.top();
            pq.pop();
            remainder = sum - largest;
            if( remainder == 1 ) return true; // can only happen if n = 2
            val = largest % remainder;
            if( val == 0 || val == largest ) return false;
            pq.push(val);
            sum = remainder + val;
        }
        return true;
    }
};
