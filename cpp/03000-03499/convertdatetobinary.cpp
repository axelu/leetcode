
// 3280. Convert Date to Binary
// https://leetcode.com/problems/convert-date-to-binary/





class Solution {
private:
    string printIntBinary(unsigned int x) {
        string ret = "";
        while( x != 0 ) {
            if( x & 1 )
                ret.push_back('1');
            else
                ret.push_back('0');
            x = x >> 1;
        }
        reverse(ret.begin(),ret.end());
        return ret;
    }

public:
    string convertDateToBinary(string date) {
        // date in the yyyy-mm-dd format

        string byear = printIntBinary(stoi(date.substr(0, 4)));
        string bmonth = printIntBinary(stoi(date.substr(5, 2)));
        string bday = printIntBinary(stoi(date.substr(8, 2)));


        return byear + "-" + bmonth + "-" +  bday;
    }
};
