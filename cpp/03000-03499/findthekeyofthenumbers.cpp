
// 3270. Find the Key of the Numbers
// https://leetcode.com/problems/find-the-key-of-the-numbers/





class Solution {
private:
    string int2string(int x) {
        string s = to_string(x);
        while( s.size() < 4 )
            s.insert(0,1,'0');
        return s;
    }

public:
    int generateKey(int num1, int num2, int num3) {
        string s1 = int2string(num1);
        string s2 = int2string(num2);
        string s3 = int2string(num3);

        int key = 0;

        for(int i = 0; i < 4; ++i) {
            char c = '9';
            if( s1[i] < c )
                c = s1[i];
            if( s2[i] < c )
                c = s2[i];
            if( s3[i] < c )
                c = s3[i];

            key = key * 10 + (c-'0');
        }

        return key;
    }
};
