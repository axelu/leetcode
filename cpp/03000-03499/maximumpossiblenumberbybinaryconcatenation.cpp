
// 3309. Maximum Possible Number by Binary Concatenation
// https://leetcode.com/problems/maximum-possible-number-by-binary-concatenation/




class Solution {
private:
    string binary2string(int n) {
        string s = "";
        while( n ) {
            if( n & 1 )
                s += "1";
            else
                s += "0";
            n >>= 1;
        }
        reverse(s.begin(),s.end());
        return s;
    }

    int binary2int(string s) {
        int ret = 0;
        int f = 1;
        for(int i = s.size()-1; i >= 0; --i) {
            if( s[i] == '1' )
                ret += f;
            f *= 2;
        }
        return ret;
    }
public:
    int maxGoodNumber(vector<int>& nums) {
        // nums.size() == 3

        // brute force

        string a = binary2string(nums[0]); // cout << a << endl;
        string b = binary2string(nums[1]); // cout << b << endl;
        string c = binary2string(nums[2]); // cout << c << endl;

        string s = "";
        // abc
        string abc = a + b + c;
        s = s > abc ? s : abc;
        // acb
        string acb = a + c + b;
        s = s > acb ? s : acb;
        // bac
        string bac = b + a + c;
        s = s > bac ? s : bac;
        // bca
        string bca = b + c + a;
        s = s > bca ? s : bca;
        // cab
        string cab = c + a + b;
        s = s > cab ? s : cab;
        // cba
        string cba = c + b + a;
        s = s > cba ? s : cba;

        return binary2int(s);
    }
};
