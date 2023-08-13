
// 982. Triples with Bitwise AND Equal To Zero
// https://leetcode.com/problems/triples-with-bitwise-and-equal-to-zero/




/* 1,2,4 -> answer
 *   we combine 1,2 for 6; 1,4 for 6; 2,4 for 6 and 1,2,4 for 6; total 24
 * 1,2,6 -> answer 18
 *   we combine 1,2 for 6; 1,6 for 6; 2,6 for 0 and 1,2,6 for 6; total 18 (Note: 2 & 6 = 2)
 *
 */
class Solution {
public:
    int countTriplets(vector<int>& nums) {

        unordered_map<int,int> cnt_a_and_b; // a&b, count
        for(int a: nums)
            for(int b: nums)
                ++cnt_a_and_b[a&b];

        int ans = 0;
        for(int c: nums)
            for(auto it = cnt_a_and_b.begin(); it != cnt_a_and_b.end(); ++it)
                if( (c & it->first) == 0 )
                    ans += it->second;

        return ans;
    }
};
