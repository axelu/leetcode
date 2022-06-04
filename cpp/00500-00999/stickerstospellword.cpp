
// 691. Stickers to Spell Word
// https://leetcode.com/problems/stickers-to-spell-word/



class Solution {
private:
    void printBinary(long x, int c) {
        /*
        for(int i = c-1; i >= 0; --i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        */
        for(int i = 0; i < c; ++i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }

    bool does_dominate(vector<int>& v, vector<int>& t) {
        // returns true if v dominates t
        // we say a sticker `v` dominates `t` if `v.count(letter) >= t.count(letter)` for all letters

        for(int i = 0; i < 26; ++i)
            if( v[i] < t[i] )
                return false;

        return true;
    }

    void apply_sticker(vector<int> sticker, string& target, int target_sz, int& mask) {
        for(int i = 0; i < target_sz; ++i) {
            if( (mask >> i) & 1 ) {
                int c = target[i]-'a';
                if( sticker[c] > 0 ) {
                    mask &= ~(1 << i);
                    --sticker[c];
                }
            }
        }
    }

    int mem[50][32768];

    long rec(vector<vector<int>>& stickers_cnt, int stickers_sz, int curr_sticker,
             int stickers_mx[], string& target, int target_sz, int mask) {

        // cout << "rec curr_sticker " << curr_sticker << " mask ";printBinary(mask,target_sz);

        if( curr_sticker == stickers_sz )
            return INT_MAX;

        if( mem[curr_sticker][mask] != -1 )
            return mem[curr_sticker][mask];

        // we have a choice
        //     don't use the current sticker at all
        //     use the current sticker up to stickers_mx[curr_sticker] times

        long a = rec(stickers_cnt,stickers_sz,curr_sticker+1,stickers_mx,target,target_sz,mask);

        int local_mask = mask;
        for(int i = 1; i <= stickers_mx[curr_sticker]; ++i) {
            // apply sticker
            apply_sticker(stickers_cnt[curr_sticker],target,target_sz,local_mask);
            if( local_mask == 0 ) {
                a = min(a,(long)i);
                break;
            }
            a = min(a,i + rec(stickers_cnt,stickers_sz,curr_sticker+1,stickers_mx,target,target_sz,local_mask));
        }

        return mem[curr_sticker][mask] = a;
    }
public:
    int minStickers(vector<string>& stickers, string target) {
        int tgt_sz = target.size();

        // count of each char in target
        int tgt_cnt[26];memset(tgt_cnt,0,sizeof tgt_cnt);
        for(char c : target)
            ++tgt_cnt[c-'a'];
        /*
        // debug
        for(int i = 0; i < 26; ++i) {
            char c = i+'a';
            cout << c << ":" << tgt_cnt[i] << " ";
        }
        cout << endl;
        */

        // count of each in stickers if the char occurs in target
        vector<vector<int>> stickers_cnt;
        int cnt[26];memset(cnt,0,sizeof cnt);
        for(auto& sticker : stickers) {
            vector<int> v(26,0);
            bool f = false;
            for(char c : sticker) {
                if( tgt_cnt[c-'a'] != 0 ) { // we only care about chars in target
                    f = true;
                    ++v[c-'a'];
                    ++cnt[c-'a'];
                }
            }
            // only add this sticker if it has a char that occurs in target
            if( f ) {
                // only add this sticker if it is NOT dominated by a sticker already in stickers_cnt
                bool add = true;
                for(auto& t : stickers_cnt) {
                    bool d = does_dominate(t,v); // returns true if t dominates v
                    if( d ) {
                        add = false;
                        break;
                    }
                }
                if( add ) {
                    // delete any stickers in stickers_cnt that this sticker dominates
                    auto it = stickers_cnt.begin();
                    while( it != stickers_cnt.end() ) {
                        if( does_dominate(v,*it) ) {
                            it = stickers_cnt.erase(it);
                        } else {
                            ++it;
                        }
                    }
                    stickers_cnt.push_back(v);
                }
            }
        }
        int stickers_sz = stickers_cnt.size();
        /*
        // debug
        for(int i = 0; i < stickers_sz; ++i) {
            cout << "sticker " << stickers[i] << endl;
            for(int c = 0; c < 26; ++c) {
                char ch = c+'a';
                cout << ch << ":" << stickers_cnt[i][c] << " ";
            }
            cout << endl;
        }
        */

        // can we even make the target?
        for(int i = 0; i < 26; ++i)
            if( tgt_cnt[i] != 0 && cnt[i] == 0 )
                return -1;

        // determine max times per sticker
        int stickers_mx[stickers_sz];memset(stickers_mx,0,sizeof stickers_mx);
        for(int i = 0; i < stickers_sz; ++i) {
            int need = 0; // how many times do we need sticker i
            for(int c = 0; c < 26; ++c) {
                int t = 0;
                if( tgt_cnt[c] != 0 && stickers_cnt[i][c] != 0 ) {
                        t = tgt_cnt[c]/stickers_cnt[i][c];
                        if( tgt_cnt[c] % stickers_cnt[i][c] != 0 )
                            ++t;
                }
                need = max(need,t);
            }
            stickers_mx[i] = need;
        }
        /*
        // debug
        for(int i = 0; i < stickers_sz; ++i)
            cout << stickers[i] << ":" << stickers_mx[i] << " ";
        cout << endl;
        */

        memset(mem,-1,sizeof mem);
        int mask = (1 << tgt_sz) - 1;
        return rec(stickers_cnt,stickers_sz,0,stickers_mx,target,tgt_sz,mask);
    }
};
