
// 1183. Maximum Number of Ones
// https://leetcode.com/problems/maximum-number-of-ones/





/* it maybe most beneficial to cluster the ones in the upper left corner
 * of the square submatrix
 * after that we need to figure out if it is better to put the remaining ones
 * in the row below that cluster or in the column to the right of that cluster
 * example width = 8, height = 8, sideLength = 6, maxOnes = 4  -> answer = 36
 *
 *            01234567
 *          0 11 11 11
 *          1 11 11 11
 *          2
 *          3 11 11 11
 *          4 11 11 11
 *          5
 *          6 11 11 11
 *          7 11 11 11
 *
 * but then take example width = 24, height = 5, sideLength = 4, maxOnes = 4  -> answer = 48
 * in this case it is best to fill the top row of the submatrix with ones
 */
class Solution {
public:
    int maximumNumberOfOnes(int width, int height, int sideLength, int maxOnes) {
        if( maxOnes == 0 )
            return 0;

        int nbr_h = width / sideLength;   // number of complete submatricies horizontally
        int rem_h = width % sideLength;   // number of remaining columns
        int nbr_v = height / sideLength;  // number of complete submatricies vertically
        int rem_v = height % sideLength;  // number of remaining rows

        vector<int> v;

        // for each position in our submatrix, lets count how often
        // if repeats in the entire matrix
        // we want to put the ones in the most repeating positions
        for(int i = 0; i < sideLength; ++i) {
            for(int j = 0; j < sideLength; ++j) {
                // we are at grid[i][j]
                int r = i < rem_v ? nbr_v + 1 : nbr_v;
                int c = j < rem_h ? nbr_h + 1 : nbr_h;
                v.push_back(r*c);
            }
        }

        sort(v.begin(),v.end(),greater<int>());
        int ans = 0;
        for(int i = 0; i < maxOnes; ++i)
            ans += v[i];

        return ans;
    }
};
