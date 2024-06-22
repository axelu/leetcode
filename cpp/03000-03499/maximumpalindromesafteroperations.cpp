
// 3035. Maximum Palindromes After Operations
// https://leetcode.com/problems/maximum-palindromes-after-operations/

/* test cases to try
["abcd","e","f"]
["abbb","ba","aa"]
["abc","ab"]
["cd","ef","a"]
["aa","bc"] 
["aagha","bc"]
["dba","g"]
["aab","ac","bb"]
*/




class Solution {
public:
    int maxPalindromesAfterOperations(vector<string>& words) {
        int n = words.size();

        int nbr_words_even_length = 0;
        int nbr_chrs_in_even_length_words = 0;
        int nbr_words_odd_length = 0;
        int nbr_chrs_in_odd_length_words = 0;
        int total_nbr_chars = 0;
        int cnt[26]; memset(cnt,0,sizeof cnt);
        vector<int> lengths;
        for(int i = 0; i < n; ++i) {
            int word_sz = words[i].size();
            total_nbr_chars += word_sz;
            lengths.push_back(word_sz);

            if( word_sz % 2 == 0 ) {
                ++nbr_words_even_length;
                nbr_chrs_in_even_length_words += word_sz;
            } else {
                ++nbr_words_odd_length;
                nbr_chrs_in_odd_length_words += word_sz;
            }
            for(int j = 0; j < word_sz; ++j)
                ++cnt[words[i][j]-'a'];
        }
        sort(lengths.begin(),lengths.end());

        int nbr_chrs_even_length = 0; // distinct
        int nbr_chrs_even_length_total = 0;
        int nbr_chrs_odd_length = 0; // distinct
        int nbr_chrs_odd_length_gt_one = 0;
        int nbr_chrs_odd_length_total = 0;
        for(int i = 0; i < 26; ++i) {
            if( cnt[i] > 0 ) {
                if( cnt[i] % 2 == 0 ) {
                    ++nbr_chrs_even_length;
                    nbr_chrs_even_length_total += cnt[i];
                } else {
                    ++nbr_chrs_odd_length;
                    if( cnt[i] > 1 ) {
                        ++nbr_chrs_even_length;
                        nbr_chrs_even_length_total += cnt[i] - 1;
                    }
                }
            }
        }
        nbr_chrs_odd_length_total = nbr_chrs_odd_length;

        if( nbr_words_odd_length >= nbr_chrs_odd_length ) {
            // we can make all words into palindromes
            return nbr_words_odd_length + nbr_words_even_length;

        } else { // nbr_words_odd_length < nbr_chrs_odd_length

            // we need to distribute the excess amount of odd chars optimally, or said differently
            // we need to make the most amount of palindromes,
            // so we greedily make the shortest palindromes first

            int i = 0;
            for(; i < lengths.size(); ++i) {

                if( lengths[i] % 2 == 0 ) {
                    // even length word
                    if( lengths[i] <= nbr_chrs_even_length_total ) {
                        // we can still make this word
                        nbr_chrs_even_length_total -= lengths[i];
                    } else {
                        break;
                    }

                } else {
                    // odd length word
                    if( nbr_chrs_odd_length > 0 ) {
                        if( nbr_chrs_even_length_total >= lengths[i] - 1) {
                            --nbr_chrs_odd_length;
                            nbr_chrs_even_length_total -= lengths[i] - 1;
                        } else {
                            break;
                        }
                    } else if( nbr_chrs_even_length_total >= 0 ) {
                        // we will draw [2 chars] from the even length chars
                        //   one odd char for the current word and
                        //   one odd char in the bucket of odd chars
                        ++nbr_chrs_odd_length;

                        nbr_chrs_even_length_total -= 2;
                    } else {
                        break;
                    }
                }
            }

            return i;
        }
    }
};
