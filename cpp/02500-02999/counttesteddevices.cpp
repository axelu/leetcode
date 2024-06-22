
// 2960. Count Tested Devices After Test Operations
// https://leetcode.com/problems/count-tested-devices-after-test-operations/




class Solution {
public:
    int countTestedDevices(vector<int>& batteryPercentages) {
        int n = batteryPercentages.size();

        int testedDevices = 0;
        int carry = 0;
        for(int i = 0; i < n; ++i) {
            int t = batteryPercentages[i] - carry;
            if( t > 0 ) {
                ++testedDevices;
                ++carry;
            }
        }

        return testedDevices;
    }
};
