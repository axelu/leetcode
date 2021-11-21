
// 1826. Faulty Sensor
// https://leetcode.com/problems/faulty-sensor/



class Solution {
public:
    int badSensor(vector<int>& sensor1, vector<int>& sensor2) {
        int n = sensor1.size(); // sensor1.length == sensor2.length, 1 <= sensor1.length <= 100
        if( n == 1 ) return -1;

        for(int i = 0; i < n; ++i) {
            //cout << i << endl;
            if( sensor1[i] == sensor2[i] )
                continue;

            // 1st discrepancy between sensor1 and sensor2
            // if we are at the end, we don't know which sensor is a fault
            if( i == n-1 ) return -1;

            if( sensor2[i] != sensor1[i+1] && sensor1[i] == sensor2[i+1] )
                return 1;
            if( sensor1[i] != sensor2[i+1] && sensor2[i] == sensor1[i+1] )
                return 2;

            if( sensor2[n-2] != sensor1[n-1] && sensor1[n-2] == sensor2[n-1] )
                return 1;
            if( sensor1[n-2] != sensor2[n-1] && sensor2[n-2] == sensor1[n-1] )
                return 2;

            break;
        }
        return -1;
    }
};
