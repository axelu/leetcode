
// 1686. Stone Game VI
// https://leetcode.com/problems/stone-game-vi/


class Solution {
public:
    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
        int n = aliceValues.size(); // 1 <= n <= 10^5
        // n == aliceValues.length == bobValues.length

        auto cmp = [](const array<int,2>& a, const array<int,2>& b){
            int t1 = a[0]+a[1];
            int t2 = b[0]+b[1];
            return t1 < t2;
        };

        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);

        for(int i = 0; i < n; ++i)
            pq.push({aliceValues[i],bobValues[i]});

        int aliceScore = 0, bobScore = 0;
        int a,b;
        int alice = 1; // alice == 1 -> alice, alice == 0 -> bob
        while( !pq.empty() ) {
            a = pq.top()[0];
            b = pq.top()[1];
            pq.pop();

            if( alice )
                aliceScore += a;
            else
                bobScore += b;

            alice = !alice;
        }

        if( aliceScore > bobScore )
            return 1;   // Alice wins
        else if( aliceScore == bobScore )
            return 0;   // draw
        else
            return -1;  // Bob wins

    }
};
