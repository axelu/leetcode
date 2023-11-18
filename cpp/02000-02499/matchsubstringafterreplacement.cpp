
// 2301. Match Substring After Replacement
// https://leetcode.com/problems/match-substring-after-replacement/






/*  01234567890123456789012345678901234567890123456789012345678901 62
 *  abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789
 */
class Solution {
private:
    unordered_map<char,int> chrdic{{'a', 0},{'b', 1},{'c', 2},{'d', 3},{'e', 4},{'f', 5},{'g', 6},{'h', 7},{'i', 8},{'j', 9},{'k',10},{'l',11},{'m',12},
                                   {'n',13},{'o',14},{'p',15},{'q',16},{'r',17},{'s',18},{'t',19},{'u',20},{'v',21},{'w',22},{'x',23},{'y',24},{'z',25},
                                   {'A',26},{'B',27},{'C',28},{'D',29},{'E',30},{'F',31},{'G',32},{'H',33},{'I',34},{'J',35},{'K',36},{'L',37},{'M',38},
                                   {'N',39},{'O',40},{'P',41},{'Q',42},{'R',43},{'S',44},{'T',45},{'U',46},{'V',47},{'W',48},{'X',49},{'Y',50},{'Z',51},
                                   {'0',52},{'1',53},{'2',54},{'3',55},{'4',56},{'5',57},{'6',58},{'7',59},{'8',60},{'9',61}};
public:
    bool matchReplacement(string s, string sub, vector<vector<char>>& mappings) {
        int s_sz   = s.size();
        int sub_sz = sub.size();
        int mps_sz = mappings.size();

        unordered_map<char,vector<char>> mappings_mp;
        for(auto& v: mappings)
            mappings_mp[v[0]].push_back(v[1]);

        bool sbm[sub_sz][62];memset(sbm,false,sizeof sbm);
        for(int i = 0; i < sub_sz; ++i) {
            char c = sub[i];
            sbm[i][chrdic[c]] = true;
            for(int j = 0; j < mappings_mp[c].size(); ++j)
                sbm[i][chrdic[mappings_mp[c][j]]] = true;
        }

        for(int k = 0; k <= s_sz - sub_sz; ++k) {   // k: index in s
            int j = 0;                              // j: index in sub
            for(int i = k; j < sub_sz; ++i,++j) {   // i: index in s
                int char_idx_s = chrdic[s[i]];
                if( !sbm[j][char_idx_s] )
                    break;
            }
            if( j == sub_sz )
                return true;
        }

        return false;
    }
};
