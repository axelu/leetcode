
// 2868. The Wording Game
// https://leetcode.com/problems/the-wording-game/




class Solution {
private:
    bool cmp(string& a, string& b) {
        // returns true if string a is lexicographically less than string b
        // it is guaranteed that a and b are different

        // A string s is lexicographically greater than a string t,
        // if in the first position where s and t differ,
        // string s has a letter that appears later in the alphabet than
        // the corresponding letter in t.
        // If the first min(s.length, t.length) characters do not differ,
        // then the longer string is the lexicographically greater one.

        int a_sz = a.size();
        int b_sz = b.size();
        for(int i = 0; i < min(a_sz,b_sz); ++i)
            if( a[i] != b[i] )
                return a[i] < b[i];

        return a_sz < b_sz;
    }

    bool is_closely_greater(string& a, string& b) {
        // returns true if string a is closely greater than string b
        // it is guaranteed that string a is lexicographically greater than string b

        // A word w is closely greater than a word z if the following conditions are met:
        // w is lexicographically greater than z.
        // If w1 is the first letter of w and z1 is the first letter of z,
        // w1 should either be equal to z1 or be the letter after z1 in the alphabet.
        // For example, the word "care" is closely greater than "book" and "car", b
        // ut is not closely greater than "ant" or "cook".

        char a1 = a[0];
        char b1 = b[0];
        return a1 == b1 || a1 == b1 + 1;
    }

    vector<int> mem;

    vector<int> nxt_alice;
    vector<int> nxt_bob;
    int alice_greatest[26];
    int bob_greatest[26];

    bool dfs(int u, vector<pair<int,int>>& v, vector<string>& a, vector<string>& b) {
        // cout << "dfs u " << u << endl;

        if( mem[u] != -1 )
            return mem[u];

        int player = v[u].second; // 0 alice, 1 bob
        // the current player played her/his current word
        // the oponent will try to play optimally

        // if the oponent cannot make a move, the current player wins
        // it is optimal that the oponent plays his greatest closely greater word,
        // unless ...
        if( player == 0 ) {
            int go = -1;
            int nxt = nxt_bob[u];
            while( nxt != -1 && is_closely_greater(b[v[nxt].first],a[v[u].first]) ) {
                // bob could play the word b[v[nxt].first]
                // bob would win playing that word if:
                //    alice does not have a word that starts with the same letter and is lexicographically greater AND
                //    alice does not have a word that starts with with letter + 1
                int fst_char = b[v[nxt].first][0] - 'a';
                if( (alice_greatest[fst_char] == -1 || cmp(a[v[alice_greatest[fst_char]].first],b[v[nxt].first])) &&
                    (fst_char == 25 || alice_greatest[fst_char + 1] == -1 ) )
                    return mem[u] = false;

                go = nxt;
                nxt = nxt_bob[nxt];
            }
            // play greatest closely greater word if any
            if( go != -1 ) {
                bool f = dfs(go,v,a,b);
                if( !f )
                   return mem[u] = false;
            }

        } else {
            int go = -1;
            int nxt = nxt_alice[u];
            while( nxt != -1 && is_closely_greater(a[v[nxt].first],b[v[u].first]) ) {
                // alice could play the word a[v[nxt].first]
                // alice would win playing that word if:
                //    bob does not have a word that starts with the same letter and is lexicographically greater AND
                //    bob does not have a word that starts with with letter + 1
                int fst_char = a[v[nxt].first][0] - 'a';
                if( (bob_greatest[fst_char] == -1 || cmp(b[v[bob_greatest[fst_char]].first],a[v[nxt].first])) &&
                    (fst_char == 25 || bob_greatest[fst_char + 1] == -1 ) )
                    return mem[u] = true;

                go = nxt;
                nxt = nxt_alice[nxt];
            }
            // play greatest closely greater word if any
            if( go != -1 ) {
                bool f = dfs(go,v,a,b);
                if( f )
                   return mem[u] = true;
            }
        }

        // the oponent was not able to win, the current player wins
        return mem[u] = player == 0;
    }

public:
    bool canAliceWin(vector<string>& a, vector<string>& b) {
        // player 0 alice
        // player 1 bob

        // a and b are lexicographically sorted.
        // All the words in a and b combined are distinct.

        int a_sz = a.size(); // cout << "a_sz " << a_sz << endl;
        int b_sz = b.size(); // cout << "b_sz " << b_sz << endl;

        // let us merge a and b
        int i = 0, j = 0, k = 0;
        vector<pair<int,int>> v(a_sz + b_sz); // idx in a or b, player
        while( i < a_sz && j < b_sz ) {
            if( cmp(a[i],b[j]) ) {
                v[k] = {i,0};
                ++i;
            } else {
                v[k] = {j,1};
                ++j;
            }
            ++k;
        }
        while( i < a_sz ) {
            v[k] = {i,0};
            ++i;
            ++k;
        }
        while( j < b_sz ) {
            v[k] = {j,1};
            ++j;
            ++k;
        }


        // lets go backwards through v and record the next index alice and next index bob
        nxt_alice.assign(a_sz + b_sz,-1);
        nxt_bob.assign(a_sz + b_sz,-1);
        int lst_seen_alice = -1;
        int lst_seen_bob = -1;
        // record from right to left the index at which we first saw a word beginning with char a-z
        memset(alice_greatest,-1,sizeof alice_greatest);
        memset(bob_greatest,-1,sizeof bob_greatest);
        for(int i = a_sz + b_sz - 1; i >= 0; --i) {
            nxt_alice[i] = lst_seen_alice;
            nxt_bob[i] = lst_seen_bob;
            if( v[i].second == 0 ) {
                lst_seen_alice = i;
                int fst_char = a[v[i].first][0] - 'a';
                if( alice_greatest[fst_char] == -1 )
                    alice_greatest[fst_char] = i;
            } else {
                lst_seen_bob = i;
                int fst_char = b[v[i].first][0] - 'a';
                if( bob_greatest[fst_char] == -1 )
                    bob_greatest[fst_char] = i;
            }
        }

        // alice starts the game by playing her lexicographically smallest word
        int a_start = 0;
        if( v[0].second != 0 )
            a_start = nxt_alice[0];

        mem.assign(a_sz + b_sz,-1);
        return dfs(a_start,v,a,b);
    }
};
