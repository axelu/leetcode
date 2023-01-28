
// 2515. Shortest Distance to Target String in a Circular Array
// https://leetcode.com/problems/shortest-distance-to-target-string-in-a-circular-array/




class Solution {
public:
    int closetTarget(vector<string>& words, string target, int startIndex) {
        int n = words.size();

        int ans = 101;

        for(int i = 0; i < n; ++i)
            if( words[i] == target ) {
                int a,b;
                if( startIndex < i ) {
                    a = i - startIndex;
                    b = n-i + startIndex;
                } else {
                    a = startIndex - i;
                    b = n-startIndex + i;
                }
                ans = min({ans,a,b});
            }

        return ans != 101 ? ans : -1;
    }
};
