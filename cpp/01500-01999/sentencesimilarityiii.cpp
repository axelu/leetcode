
// 1813. Sentence Similarity III
// https://leetcode.com/problems/sentence-similarity-iii/



/* if sentence1.size() == sentence2.size()
 *    then return sentence1 == sentence2
 *
 *                      0123456789012345
 * example sentence1 = "My name is Haley" (size = 16),
                           12345678
 *                         --------
                            1234567
 *         sentence2 = "My Haley" (size = 8)
 * let sentence1.size() > sentence2.size()
 * let diff = sentence1.size() - sentence2.size()
 * sentence1 has a subsentence substc[i,i+diff-1]
 * with 0 <= i <= sentence1.size() - diff
 * either substc + sentence2 == sentence1 OR
 *        sentence2 + substc == sentence1 OR
 *        sentence2[0,k] + substc + sentence2[k+1,sentence2.size()-1] == sentence1
 */
class Solution {
private:
    bool is_equal(string& sentence1, int s1, string& sentence2, int s2) {
        for(; s1 < sentence1.size() && s2 < sentence2.size(); ++s1, ++s2)
            if( sentence1[s1] != sentence2[s2] )
                return false;
        return true;
    }

    bool is_equal(string& sentence1, string& sentence2, int n) {
        for(int i = 0; i < n; ++i)
            if( sentence1[i] != sentence2[i] )
                return false;
        return true;
    }

public:
    bool areSentencesSimilar(string& sentence1, string& sentence2) {
        int s1_sz = sentence1.size();
        int s2_sz = sentence2.size();
        if( s1_sz == s2_sz )
            return sentence1 == sentence2;

        if( s2_sz > s1_sz ) {
            // swap
            swap(s1_sz,s2_sz);
            swap(sentence1,sentence2);
        }

        // cout << sentence1 << " " << s1_sz << endl;
        // cout << sentence2 << " " << s2_sz << endl;

        // brute force
        // we will try every sentence1 substring of length diff
        // that starts at a non-space and ends at a space
        // and insert into every split of sentence2

        int diff = s1_sz - s2_sz;

        // sentence1 processing
        for(int i = 0; i <= s1_sz - diff + 1; ++i) {
            if( sentence1[i] != ' ' &&
                ( i == 0 || sentence1[i-1] == ' ' ) &&
                (i + diff - 1 == s1_sz || sentence1[i + diff - 1] == ' ') ) {

                if( i == 0 ) {
                    // compare sentence1[i+diff,s1_sz-1] to sentence2[0,s2_sz-1]
                    if( is_equal(sentence1,i+diff,sentence2,0) )
                        return true;

                } else if( i + diff - 1 == s1_sz ) {
                    // compare sentence1[0,s2_sz-1] to sentence2[0,s2_sz-1]
                    if( is_equal(sentence1,0,sentence2,0) )
                        return true;

                } else {
                    // left of subsentence
                    bool f = is_equal(sentence1,sentence2,i);
                    // right of subsentence
                    if( f && is_equal(sentence1,i+diff,sentence2,i) )
                       return true;
                }
            }
        }

        return false;
    }
};
