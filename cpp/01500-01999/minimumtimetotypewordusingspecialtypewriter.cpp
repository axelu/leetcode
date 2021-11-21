
// 1974. Minimum Time to Type Word Using Special Typewriter
// https://leetcode.com/problems/minimum-time-to-type-word-using-special-typewriter/






// abcdefghijklmnopqrstuvwxyz
class Solution {
public:
    int minTimeToType(string word) {


        int ans = 0;

        int pointer = 0;  // initial position of the pointer is a aka 0;
        int t;
        for(int i = 0; i < word.size(); ++i) {

            t = word[i]-'a';
            if( pointer > t ) {
                //  counterclockwise,clockwise
                ans += min(pointer-t,t+(26-pointer));
            } else if(pointer < t) {
                //         clockwise,counterclockwise
                ans += min(t-pointer,(26-t)+pointer);
            }
            pointer = t;
            ++ans; // 1 sec to type the letter
        }

        return ans;
    }
};
