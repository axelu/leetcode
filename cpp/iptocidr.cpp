
// 751. IP to CIDR
// https://leetcode.com/problems/ip-to-cidr/




class Solution {
private:
    void printIntBinary(unsigned int x) {
        for(int i = 31; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        cout << endl;
        //cout << x << endl;
    }

    unsigned int ip2uint(string ip) {
        unsigned int x = 0, octet = 32;
        stringstream ss(ip);
        string s;
        while( getline(ss,s,'.') ) {
            octet -= 8;
            x |= (((unsigned int)(stoi(s))) << octet);
        }
        return x;
    }

    string uint2ip(unsigned int x) {
        string s = "";
        for(int i = 24; i >= 0; i -= 8) {
            if( !s.empty() ) s += '.';
            s += to_string(255 & (x >> i));
        }
        return s;
    }

    int lowestSetBit(unsigned int x) {
        for(int i = 0; i < 32; ++i) {
            if( x & (1 << i) ) return 32-i;
        }
        return -1;
    }

    int highestSetBit(unsigned int x) {
        for(int i = 31; i >= 0; --i) {
            if( x & (1 << i) ) return 32-i;
        }
        return -1;
    }

    unsigned int ipsNetworkmask(int netmask) {
        // netmask = count of leading 1 bits
        // returns the number of IP addresses given the netmask
        unsigned int res = 0;
        for(int i = 0; i < 32-netmask; ++i) {
            res |= (1 << i);
        }
        return res+1; // TODO overflow, consider unsigned long instead
    }

public:
    vector<string> ipToCIDR(string ip, int n) {

        // idea:
        // find the lowest set bit of the current IP address
        // determine how many addresses it woud deliver, if we fix said bit
        // if the number of IP address we would get is lower than n, fix it there, and continue
        // if the number of IP address we would get is equal to n, we are done
        // if the number of IP address we would get is higher than n, fix it on a lower bit

        unsigned int currIp = ip2uint(ip);
        vector<string> ans;
        int lb;
        unsigned int nbrIps;
        while( n > 0 ) {
            // get lowest bit set in currIp
            lb = lowestSetBit(currIp);
            if( lb == -1 ) {
                // edge case: our initial IP address was 0.0.0.0,
                // meaning our currIp = 0, meaning no bit is set
                // in this case we can fix it on the highest set bit of n
                lb = highestSetBit(n); // !!! this is correct way, but bug in solution
                // lb = 32; // !!! this is incorrect, but used to work around bug in solution
            }
            // how many IP addresses do we get if we fix it at the lowest set bit of the currIp?
            nbrIps = ipsNetworkmask(lb);
            while(nbrIps > n) {
                ++lb;
                nbrIps = ipsNetworkmask(lb);
            }
            ans.push_back(uint2ip(currIp)+"/"+to_string(lb));
            currIp += nbrIps;
            n -= nbrIps;
        }
        return ans;
    }
};
