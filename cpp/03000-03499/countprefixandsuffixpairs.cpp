
// 3045. Count Prefix and Suffix Pairs II
// https://leetcode.com/problems/count-prefix-and-suffix-pairs-ii/





// initialize once
long long p_pow[100001];
bool init = false;

class Solution {
private:

public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        // 1 <= words[i].length <= 1e5

        const int p = 31;
        const int m = 1e9 + 9;

        if( !init ) {
            init = true;
            p_pow[0] = 1;
            for (int i = 1; i < 100001; i++)
                p_pow[i] = (p_pow[i-1] * p) % m;
        }

        int words_sz = words.size();
        if( words_sz == 1 )
            return 0LL;

        unordered_map<long long,pair<int,long long>> hashes; // hash, {length of word, count}

        // create the hash for the 1st word
        long long h_s = 0LL;
        int l_s = words[0].size();
        for(int i = 0; i < l_s; ++i)
            h_s = (h_s + (words[0][i] - 'a' + 1) * p_pow[i]) % m;
        hashes[h_s] = {l_s, 1LL};

        // for each word create a rolling hash
        // along the way we check if we have seen this hash before,
        // which will tell us that there is a word we have already passed,
        // that is a prefix
        // if there is at least one word we passed that is a prefix, we will
        // create suffix hashes to determine if it is also a suffix hash

        long long ans = 0;

        for(int k = 1; k < words_sz; ++k) {
            l_s = words[k].size();
            vector<unordered_map<long long,pair<int,long long>>::iterator> prefix_hashes;
            long long h[l_s + 1];
            h[0] = 0LL;
            for(int i = 0; i < l_s; ++i) {
                int c = words[k][i] - 'a';
                h[i+1] = (h[i] + (c + 1) * p_pow[i]) % m;
                auto hashes_it = hashes.find(h[i+1]);
                if( hashes_it != hashes.end() )
                    prefix_hashes.push_back(hashes_it);
            }
            for(auto it: prefix_hashes) {
                h_s = it->first;          // pattern hash
                int S = it->second.first; // pattern size
                long long cur_h = (h[l_s] + m - h[l_s - S]) % m;
                if (cur_h == h_s * p_pow[l_s-S] % m)
                    ans += it->second.second;
            }
            auto p = hashes.insert({h[l_s],{l_s, 1LL}});
            if( !p.second )
                ++p.first->second.second;
        }

        return ans;
    }
};
