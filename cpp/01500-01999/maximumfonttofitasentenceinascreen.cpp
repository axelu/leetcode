
// 1618. Maximum Font to Fit a Sentence in a Screen
// https://leetcode.com/problems/maximum-font-to-fit-a-sentence-in-a-screen/



/**
 * // This is the FontInfo's API interface.
 * // You should not implement it, or speculate about its implementation
 * class FontInfo {
 *   public:
 *     // Return the width of char ch when fontSize is used.
 *     int getWidth(int fontSize, char ch);
 *
 *     // Return Height of any char when fontSize is used.
 *     int getHeight(int fontSize)
 * };
 */
class Solution {
public:
    int maxFont(string text, int w, int h, vector<int>& fonts, FontInfo fontInfo) {
        int n = fonts.size();

        // binary search greatest element less than target or equal target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        int fontsize,height,width;
        bool f;
        while(s < e) {
            mid = s + ((e-s)/2);
            fontsize = fonts[mid];

            f = false;
            height = fontInfo.getHeight(fontsize);
            if( height <= h )
                f = true;
            if( f ) {
                width = 0;
                for(int i = 0; i < text.size(); ++i) {
                    width += fontInfo.getWidth(fontsize,text[i]);
                    if( width > w ) {
                        f = false;
                        break;
                    }
                }
            }

            if( f )
                s = mid+1;
            else
                e = mid;
        }
        if( !(s == 0 && f) )
            --s;

        return s == -1 ? -1 : fonts[s];
    }
};
