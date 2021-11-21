
// 383. Ransom Note
// https://leetcode.com/problems/ransom-note/



class Solution {
public:
    bool canConstruct(string& ransomNote, string& magazine) {
        
        int cntMagazine[26]; memset(cntMagazine,0,sizeof cntMagazine);
        int cntRansomNote[26]; memset(cntRansomNote,0,sizeof cntRansomNote);
        
        for(int i = 0; i < magazine.size(); ++i)
            ++cntMagazine[magazine[i]-'a'];
        for(int i = 0; i < ransomNote.size(); ++i)
            ++cntRansomNote[ransomNote[i]-'a'];
        
        for(int i = 0; i < 26; ++i)
            if( cntMagazine[i] < cntRansomNote[i] ) return false;
        
        return true;
    }
};
