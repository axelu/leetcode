
// 2327. Number of People Aware of a Secret
// https://leetcode.com/problems/number-of-people-aware-of-a-secret/



class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        // constraints
        //     2 <= n <= 1000
        //     1 <= delay < forget <= n

        // base case
        // n = 2, delay = 1, forget = 2
        // extreme case
        // n = 1000, delay = 1, forget = 1000

        // example
        // n = 6, delay = 2, forget = 4
        //        0  1  2  4
        // day 0  A  0  0  0
        // day 1  0  A  0  0
        // day 2  B  0  A  0
        // day 3  C  B  0  A
        // day 4  D  C  B  0
        // day 5  EF D  C  B  <- 5 people know


        long mod = 1000000007;

        deque<long> dq;
        for(int i = 0; i < forget-1; ++i)
            dq.push_front(0);
        dq.push_front(1); // on day 1, one person knows the secret.

        for(int i = 0; i < n-1; ++i) {
            long t = 0;
            for(int j = delay-1; j < forget-1; ++j)
                t = (t + dq[j]) % mod;
            dq.push_front(t);
            dq.pop_back();
        }

        long ans = 0;
        for(int i = 0; i < forget; ++i)
            ans = (ans + dq[i]) % mod;

        return ans;
    }
};
