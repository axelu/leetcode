
// 1108. Defanging an IP Address
// https://leetcode.com/problems/defanging-an-ip-address/


class Solution {
public:
    string defangIPaddr(string& address) {
        size_t n = address.size();
        int i = 0;
        while( i < n ) {
            if( address[i] != '.' ) {
                ++i;
                continue;
            }
            address.insert(begin(address)+i,'[');
            address.insert(begin(address)+i+2,']');
            n += 2;
            i += 2;
        }
        return address;
    }
};
