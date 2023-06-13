
// 2611. Mice and Cheese
// https://leetcode.com/problems/mice-and-cheese/




/* if mouse1 eats exactly k types of cheese,
 *   then mouse2 eats exactly n-k types of cheese
 *
 * example
 *   k = 2
 *           0 1 2 3
 *   reward1 1 1 3 4
 *   reward2 4 4 1 1
 *
 *   if mouse1 eats reward1[2]      we gain 3 and loose out on 1
 *   if mouse1 would eat reward1[0] we gain 1 and loose out on 4
 *   prioritize the ones that mouse 1 eats
 *      reward1 > reward2, if comparing 2, prefer the one were reward1 is greater
 *   ...
 *  where reward1 == reward2: it doesn't matter if mouse1 or mouse2 eats them
 *  if mouse1 still needs to eat cheese where reward1 < reward2
 *  we want mouse1 to eat
 *  lets say we have reward1 6  5
 *                   reward2 8 10
 *  option 1: mouse1 6 + mouse2 10 -> gain 16   <- this is the choice we need to make
 *  option 2: mouse1 5 + mouse2  8 -> gain 13
 *  => in fact, we can apply above compare to just all rewardsX[i] to prioritize mouse1
 */
class Solution {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        int n = reward1.size(); // reward1.length == reward2.length

        if( k == n ) {
            // mouse1 eats all in reward1, mouse2 eats nothing in reward2
            return accumulate(reward1.begin(),reward1.end(),0);
        }
        if( k == 0 ) {
            // mouse1 eats nothing in reward1, mouse2 eats all in reward2
            return accumulate(reward2.begin(),reward2.end(),0);
        }

        auto cmp = [](const array<int,2>& a, const array<int,2>& b){
            // option1 mouse1 a[0] + mouse2 b[1]
            // option2 mouse1 b[0] + mouse2 a[1]
            int opt1 = a[0] + b[1];
            int opt2 = b[0] + a[1];
            return opt2 > opt1;
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);

        for(int i = 0; i < n; ++i)
            pq.push({reward1[i],reward2[i]});

        int sum = 0;

        while( !pq.empty() ) {
            if( k > 0 )
                sum += pq.top()[0];
            else
                sum += pq.top()[1];
            pq.pop();
            --k;
        }

        return sum;
    }
};
