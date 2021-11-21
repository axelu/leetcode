
// 1705. Maximum Number of Eaten Apples
// https://leetcode.com/problems/maximum-number-of-eaten-apples/



class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        int n = apples.size(); // apples.length == days.length == n

        int ans = 0;

        // store last day that apples could be consumed and their count
        // sort apples by last day that they could be consumed
        auto cmp = [](const array<int,2>& a, const array<int,2>& b) {
            return a[0] > b[0];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);


        int lastGoodDay,amount;
        int i = 0; // day
        for(; i < n; ++i) {
            //cout << "day " << i << " ";

            // harvest
            if( apples[i] != 0 )
                pq.push({i+days[i]-1,apples[i]});

            // discard rotten apples and eat 1 apple
            while(!pq.empty()) {
                lastGoodDay = pq.top()[0];
                amount      = pq.top()[1];
                pq.pop();

                if( lastGoodDay < i ) {
                    // do nothing
                } else {
                    ++ans;
                    --amount;
                    if( amount > 0 )
                        pq.push({lastGoodDay,amount});
                    break;
                }
            }
            //cout << "ans " << ans << endl;
        }

        // keep eating as long as there are apples
        while(!pq.empty()) {
            lastGoodDay = pq.top()[0];
            amount      = pq.top()[1];
            if( lastGoodDay >= i ) {
                // we can at most eat as many apples as there are,
                // or as many as there are days left before they are rotten
                int t = min(lastGoodDay-i+1,amount);
                ans += t;
                i += t;
            }
            pq.pop();
        }

        return ans;
    }
};
