
// 843. Guess the Word
// https://leetcode.com/problems/guess-the-word/




/*                012345
 * example secret vftnkr
 *
 *         word1  slbnia  guess returns 1 (match on secret at pos 3)
 *         word2  vvqvla  guess returns 1 (match to secret at pos 0)
 * NOTE: word1 and word2 match each other in pos 5, so we learned nothing!
 *
 *         word1  slbnia  guess returns 1 (match on secret at pos 3)
 *         word2  slbnta  guess returns 1 (match on secret at pos 3)
 * NOTE: word1 and word2 match each other except of in pos 4, so we know pos 4 is neither i nor t
 *         word1  slbnia  guess returns 1 (match on secret at pos 3)
 *         word2  slbtia  guess returns 0
 * NOTE: word1 and word2 match each other except of in pos 3, so we know pos 3 is n
 *         word1  slbnia  guess returns 1 (match on secret at pos 3)
 *         word2  slbnka  guess returns 2 (match on secret at pos 3 and pos 4)
 * NOTE: word1 and word2 match each other except of in pos 3, so we know pos 4 is k
 * The issue is, that this relies on us having at least 2 words matching in 5 pos.
 *
 * There is no guaruantee for us having that.
 *         word1  vfabcd  guess returns 2 (match on secret at pos 0 and pos 1)
 *         word2  xyabkr  guess returns 2 (match to secret at pos 4 and pos 5)
 * NOTE: word1 and word2 match each other in pos 2 and pos 3.
 *       Unless we have some third word to help with, we learned nothing.

 *
 */


/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
private:
    // matrix that contains for each word in words
    // a list of words by number of matched chars
    //       0   1   2    3    4    5
    // word0     1        2,3            says that word0 matches word1 in 1 position, word0 matches word2 and word3 in 3 positions
    // word1     0
    // word2              0,3
    // word3              0,2
    vector<int> match_cnt[100][6];

    int results[100];
    string secret;
    int guesses;
    unordered_set<char> not_secret[6]; // chars we know do not occupy the given position
    unordered_set<char> may_secret[6]; // chars that we know could occupy the given position

    bool is_candidate(vector<string>& words, int word_idx) {
        bool ret = true;
        for(int k = 0; k < 6; ++k) {
            if( (secret[k] != '#' && secret[k] != words[word_idx][k]) ||
                not_secret[k].find(words[word_idx][k]) != not_secret[k].end() ) {

                ret = false;
                break;
            }
        }

        // cout << "is_candidate " << words[word_idx]<< " " << ret << endl;
        return ret;
    }

    void res0(vector<string>& words, int word_idx) {
        for(int k = 0; k < 6; ++k) {
            not_secret[k].insert(words[word_idx][k]);
            may_secret[k].erase(words[word_idx][k]);
            if( may_secret[k].size() == 1 ) {
                secret[k] = *may_secret[k].begin();
            }
        }
        return;
    }

    bool is_secret_complete() {
        // cout << "secret " << secret << endl;
        for(char c: secret)
            if( c == '#' )
                return false;
        return true;
    }

    int _guess(string& word, Master& master) {
        int res = master.guess(word);
        ++guesses;
        // cout << "guess " << word << " " << res << " guesses " << guesses << endl;

        return res;
    }

    int _guess(vector<string>& words, int word_idx, Master& master) {
        if( results[word_idx] != -1 ) { // just in case, we don't want to waste guesses
            // cout << "guess " << words[word_idx] << " " << results[word_idx] << " guesses " << guesses << " cached" << endl;
            return results[word_idx];
        }

        int res = results[word_idx] = master.guess(words[word_idx]);
        ++guesses;
        // cout << "guess " << words[word_idx] << " " << res << " guesses " << guesses << endl;
        if( res == 0 )
            res0(words,word_idx);

        return res;
    }

public:
    void findSecretWord(vector<string>& words, Master& master) {
        // 10 <= allowedGuesses <= 30
        int words_sz = words.size(); // cout << "words_sz " << words_sz << endl;
        if( words_sz <= 10 ) {
            // brute force
            for(string& word: words) {
                int res = master.guess(word);
                if( res == 6 )
                    return;
            }
            return;
        }

        memset(results,-1,sizeof results); // don't repeat guesses
        secret = "######";                 // replace # with char if we are certain
        guesses = 0;                       // circuit breaker, the maximum ever allowed is 30

        // preprocess words
        vector<pair<int,int>> _words;
        for(int i = 0; i < words_sz; ++i) {
            for(int k = 0; k < 6; ++k) {
                may_secret[k].insert(words[i][k]);
            }

            for(int j = i+1; j < words.size(); ++j) {
                int matches = 0;
                for(int k = 0; k < 6; ++k) {
                    if( words[i][k] == words[j][k] )
                        ++matches;
                }
                // cout << words[i] << " matches " << words[j] << " in " << matches << " positions" << endl;
                match_cnt[i][matches].push_back(j);
                _words.push_back({i,matches});
                match_cnt[j][matches].push_back(i);
                _words.push_back({j,matches});
            }
        }
        // if for all words that we have a given position is the same char,
        // then we already know that secret must be that char at that position
        for(int k = 0; k < 6; ++k) {
            if( may_secret[k].size() == 1 ) {
                secret[k] = *may_secret[k].begin();
            }
        }
        // sort words by overlap with other words
        sort(_words.begin(),_words.end(),[](const pair<int,int>& a, const pair<int,int>& b){
            return a.second > b.second;
        });


        // make an initial guess till guess returns something other than 0;
        int last_res = 0;
        int last_word;
        for(int i = 0; last_res == 0 && i < words_sz; ++i) {
            last_word = _words[i].first;
            if( is_candidate(words,last_word) )
                last_res = _guess(words,last_word,master);
        }
        if( last_res == 6 )
            return;

        while( guesses < 30 ) {

            for(int i = 0; i < match_cnt[last_word][last_res].size() && guesses < 30; ++i) {

                int curr_word = match_cnt[last_word][last_res][i];
                if( results[curr_word] != -1 || !is_candidate(words,curr_word) )
                    continue;

                int res = _guess(words,curr_word,master);
                if( res == 6 )
                    return;

                // we expect a better result
                if( res > last_res ) {
                    // cout << "we got closer" << endl;
                    last_word = curr_word;
                    last_res = res;
                }

                if( is_secret_complete() ) {
                    _guess(secret,master); // TODO check if we still have a guess available
                    return;
                }

            }
            if( guesses < 30 ) {
                // we will be stuck
                for(int i = 0; i < words_sz; ++i) {
                    last_word = _words[i].second;
                    if( results[last_word] == -1 && is_candidate(words,last_word) ) {
                        last_res = _guess(words,last_word,master);
                        if( last_res == 0 )
                            continue;
                        if( last_res == 6 )
                            return;
                        if( is_secret_complete() ) {
                            _guess(secret,master); // TODO check if we still have a guess available
                            return;
                        }
                        break;
                    }
                }
            }
            // cout << "guesses " << guesses << " last_res " << last_res << endl;
        }

        // cout << "guesses " << guesses << " last_res " << last_res << endl;
        return;
    }
};
