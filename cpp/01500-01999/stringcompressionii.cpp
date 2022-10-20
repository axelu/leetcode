
// 1531. String Compression II
// https://leetcode.com/problems/string-compression-ii/



class Solution {
private:
    string run_length_compression(string& s) {
        string ret = "";

        char pre = '#';
        int cnt = 0;
        for(int i = 0; i < s.size(); ++i) {
            if( s[i] != pre ) {
                if( cnt == 1 )
                    ret = ret + pre;
                else if( cnt >= 2 )
                    ret = ret + pre + to_string(cnt);
                pre = s[i];
                cnt = 0;
            }
            ++cnt;
        }
        // finish up
        if( cnt == 1 )
            ret = ret + pre;
        else if( cnt >= 2 )
            ret = ret + pre + to_string(cnt);

        return ret;
    }

    unordered_map<int,int> mem;
    // key:
    // pos   lst_chr   lst_chr_cnt   k

    int rec(string& s, int n, int pos, char lst_chr, int lst_chr_cnt, int k) {
        if( pos == n )
            return 0;

        int key = (pos<<21) + ((lst_chr-'a')<<14) + (lst_chr_cnt<<7) + k;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        // at each index that we arrive, we have a choice
        //     - delete the current char
        //     - keep the current char, meaning add to the string we need to compress

        // delete
        int a = INT_MAX;
        if( k > 0 )
            a = rec(s,n,pos+1,lst_chr,lst_chr_cnt,k-1);

        // keep
        int b;
        if( s[pos] == lst_chr ) {
            b = rec(s,n,pos+1,lst_chr,lst_chr_cnt+1,k);
            if( lst_chr_cnt == 1 || lst_chr_cnt == 9 || lst_chr_cnt == 99 )
                ++b;
        } else {
            b = rec(s,n,pos+1,s[pos],1,k) + 1;
        }

        return mem[key] = min(a,b);
    }

public:
    int getLengthOfOptimalCompression(string& s, int k) {
        int n = s.size();
        if( n == k )
            return 0;

        if( k == 0 )
            return run_length_compression(s).size();

        return rec(s,n,0,'{',0,k);
    }
};
