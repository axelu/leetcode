
// 287. Find the Duplicate Number
// https://leetcode.com/problems/find-the-duplicate-number/




// Floyd's algorithm
// https://en.wikipedia.org/wiki/The_Tortoise_and_the_Hare
// solution taken from approach #3
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();

        // Find the intersection point of the two runners.
        int tortoise = nums[0];
        int hare = nums[0];
        do {
          tortoise = nums[tortoise];
          hare = nums[nums[hare]];
        } while (tortoise != hare);

        // Find the "entrance" to the cycle.
        tortoise = nums[0];
        while (tortoise != hare) {
          tortoise = nums[tortoise];
          hare = nums[hare];
        }

        return hare;
    }
};
