
// Design Parking System
// https://leetcode.com/problems/design-parking-system/


class ParkingSystem {
private:
    int b; // number of big parking spaces
    int m; // number of medium parking spaces
    int s; // number of small  parking spaces
public:
    ParkingSystem(int big, int medium, int small) {
        b = big;
        m = medium;
        s = small;
    }

    bool addCar(int carType) {
        // carType: 1 = big, 2 = medium, 3 = small

        bool r = true;
        if( carType == 1 ) {
            if( b == 0 ) return false;
            --b;
        } else if ( carType == 2 ) {
            if( m == 0 ) return false;
            --m;
        } else {
            // carType == 3
            if( s == 0 ) return false;
            --s;

        }

        return r;
    }
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */
