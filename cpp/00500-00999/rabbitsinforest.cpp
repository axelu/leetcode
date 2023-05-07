
// 781. Rabbits in Forest
// https://leetcode.com/problems/rabbits-in-forest/



/* example
 * each rabit answers that there are 3 other rabbits
 *
 * rabbit's answer                3  3  3  3  | 3  3  3  3  | 3  3  3  3  | 3 ...
 * + rabbit that we interviewed   1  1  1  1  | 1  1  1  1  | 1  1  1  1  | 1 ...
 * min rabbits                         4      |      8      |     12      |   ...
 */
class Solution {
public:
    int numRabbits(vector<int>& answers) {
        unordered_map<int,int> um;
        for(int x: answers)
            ++um[x];

        int ans = 0;
        for(auto it = um.begin(); it != um.end(); ++it) {
            // it->first = number of other rabbits of same calor
            //     and then there is the rabit that we interviewed
            int d = it->first + 1;

            int l = it->second - 1;

            ans += ((l / d) + 1) * d;
        }

        return ans;
    }
};
