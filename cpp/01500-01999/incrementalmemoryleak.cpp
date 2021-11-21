
// 1860. Incremental Memory Leak
// https://leetcode.com/problems/incremental-memory-leak/



class Solution {
public:
    vector<int> memLeak(int memory1, int memory2) {
        // 0 <= memory1, memory2 <= 2^31 - 1 (= INT_MAX = 2147483647)
        // available memory = memory1 + memory2
        // best case aka max memory available: 4294967294 = INT_MAX + INT_MAX
        // memory gets consumed at the rate of the sum of consecutive numbers
        // formula: n/2*(1stnumber+lastnumber) -> n/2*(1+n)
        // our 1stnumber is 1, our last number is upper bound for the number of seconds
        // for the best case: n = 92681 -> 4294883880 < 4294967294
        //                    n = 92682 -> 4295022903 > 4294967294
        // in the best case we are out of memory after 92681 seconds

        // brute force simulation
        int i = 1;
        for(; i < 92682; ++i) {
            if( memory1 < i && memory2 < i )
                break;
            if( memory1 >= memory2 )
                memory1 -= i;
            else
                memory2 -= i;
        }
        vector<int> ans{i,memory1,memory2};
        return ans;
    }
};
