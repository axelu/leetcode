
// 1307. Verbal Arithmetic Puzzle
// https://leetcode.com/problems/verbal-arithmetic-puzzle/

class Solution {
private:
    int chr2idx[26];
    int chrmap[10];
    bool is_first[10];
    int lft_map[10][7];
    bool used[10];
    bool is_left[10];
    
    int assign(string& s) {
        int ret = 0;
        for(int i = 0; i < s.size(); ++i) {
            int idx = chr2idx[s[i]-'A'];
            ret = 10 * ret + chrmap[idx];
        }
        return ret;
    }
    
    bool rec2(int idx, int k, int target) {
        
        // k is running sum
        if( k > target )
            return false;
        
        if( idx == 10 )
            return k == target;
        
        if( !is_left[idx] )
            return rec2(idx+1,k,target);
        
        if( chrmap[idx] != -1 ) {
            int x = 0;
            for(int i = 0; i < 7; ++i)
                x += pow(10,i) * lft_map[idx][i] * chrmap[idx];
            return rec2(idx+1,k+x,target);
            
        } else {
            
            for(int j = 0; j < 10; ++j) {
                if( used[j] )
                    continue;
                if( j == 0 && is_first[idx] )
                    continue;
                
                int x = 0;
                for(int i = 0; i < 7; ++i)
                    x += pow(10,i) * lft_map[idx][i] * j;
                                
                used[j] = true;
                if( rec2(idx+1,k+x,target) )
                    return true;
                
                // backtrack
                used[j] = false;
            }
        }
        
        return false;
    }

    bool rec1(string& result, const int pos) {
        if( pos == result.size() ) {
            int target = assign(result);
            return rec2(0,0,target);
        }
        
        int idx = chr2idx[result[pos]-'A'];
        if( chrmap[idx] != -1 ) {
            return rec1(result,pos+1);   
            
        } else {
                
            for(int i = 0; i < 10; ++i) {
                if( used[i]  )
                    continue;
                if( i == 0 && is_first[idx] )
                    continue;

                // assign i to current char mark as used
                chrmap[idx] = i;
                used[i] = true;

                if( rec1(result,pos+1) )
                    return true;

                // backtrack
                // chrmap[result[pos]] = -1;
                used[i] = false;
            }
        
        }
        // backtrack
        chrmap[idx] = -1;
        return false;
    }
    
public:
    bool isSolvable(vector<string>& words, string result) {
        int rs_sz = result.size();
        
        // collect the unique chars used in expression
        // per constraint: 
        //     The number of different characters used in the expression is at most 10.
        
        memset(chr2idx,-1,sizeof chr2idx);
        int idx = 0;
        memset(is_first,false,sizeof is_first);
        
        // process result
        for(int i = 0; i < rs_sz; ++i) {
            int cur_idx = chr2idx[result[i]-'A'];
            if( cur_idx == -1 ) {
                cur_idx = idx++;
                chr2idx[result[i]-'A'] = cur_idx;
            }
            if( i == 0 && rs_sz > 1 )
                is_first[cur_idx] = true;
        }
        
        // process words
        memset(lft_map,0,sizeof lft_map); 
        memset(is_left,false,sizeof is_left);
        for(string& s: words) {
            for(int i = s.size()-1; i >= 0; --i) {
                int cur_idx = chr2idx[s[i]-'A'];
                if( cur_idx == -1 ) {
                    cur_idx = idx++;
                    chr2idx[s[i]-'A'] = cur_idx;
                }
                if( i == 0 && s.size() > 1 )
                    is_first[cur_idx] = true;
                
                ++lft_map[cur_idx][s.size()-1-i];
                is_left[cur_idx] = true;
            }
        }
        
        memset(chrmap,-1,sizeof chrmap);
        memset(used,false,sizeof used);
        return rec1(result,0);
    }
};

// 34 / 34 test cases passed, but took too long. as of 11/21/2023

class Solution {
private:
    unordered_map<char,int> chrmap;
    unordered_set<char> is_first;
    bool used[10];
    
    int assign(string& s) {
        int ret = 0;
        for(int i = 0; i < s.size(); ++i)
            ret = 10 * ret + chrmap[s[i]];
        return ret;
    }
    
    bool rec2(unordered_map<char,vector<int>>& lft_map, 
              unordered_map<char,vector<int>>::iterator it, int k, int target) {
        
        // k is running sum
        if( k > target )
            return false;
        
        if( it == lft_map.end() )
            return k == target;
        
        auto f = chrmap.find(it->first);
        if( f->second != -1 ) {
            int x = 0;
            for(int i = 0; i < 7; ++i)
                x += pow(10,i) * it->second[i] * f->second;
            return rec2(lft_map,next(it),k+x,target);
            
        } else {
            
            for(int j = 0; j < 10; ++j) {
                if( used[j] )
                    continue;
                if( j == 0 && is_first.count(it->first) )
                    continue;
                
                used[j] = true;
                int x = 0;
                for(int i = 0; i < 7; ++i)
                    x += pow(10,i) * it->second[i] * j;
                
                if( rec2(lft_map,next(it),k+x,target) )
                    return true;
                
                // backtrack
                used[j] = false;
            }
        }
        
        return false;
    }

    bool rec1(string& result, int pos, unordered_map<char,vector<int>>& lft_map) {
        if( pos == result.size() ) {
            int target = assign(result);
            return rec2(lft_map,lft_map.begin(),0,target);
        }
        
        if( chrmap[result[pos]] != -1 ) {
            return rec1(result,pos+1,lft_map);   
            
        } else {
                
            for(int i = 0; i < 10; ++i) {
                if( used[i]  )
                    continue;
                if( i == 0 && is_first.count(result[pos]) )
                    continue;

                // assign i to current char mark as used
                chrmap[result[pos]] = i;
                used[i] = true;

                if( rec1(result,pos+1,lft_map) )
                    return true;

                // backtrack
                chrmap[result[pos]] = -1;
                used[i] = false;
            }
        
        }
        return false;
    }
    
public:
    bool isSolvable(vector<string>& words, string result) {
        int rs_sz = result.size();
        
        // collect the unique chars used in expression
        // per constraint: 
        //     The number of different characters used in the expression is at most 10.
        
        // process result
        for(int i = 0; i < rs_sz; ++i) {
            auto p = chrmap.insert({result[i],-1});
            if( i == 0 && rs_sz > 1 )
                is_first.insert(result[i]);
        }
        // process words
        unordered_map<char,vector<int>> lft_map;
        for(string& s: words) {
            for(int i = s.size()-1; i >= 0; --i) {
                auto p = chrmap.insert({s[i],-1});
                if( i == 0 && s.size() > 1 )
                    is_first.insert(s[i]);
                auto f = lft_map.find(s[i]);
                if( f == lft_map.end() ) {
                    lft_map.insert({s[i],{0,0,0,0,0,0,0}});
                    ++lft_map[s[i]][s.size()-1-i];
                } else {
                    ++lft_map[s[i]][s.size()-1-i];
                }
            }
        }
        
        memset(used,false,sizeof used);
        return rec1(result,0,lft_map);
    }
};
