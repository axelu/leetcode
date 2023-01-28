
// 1279. Traffic Light Controlled Intersection
// https://leetcode.com/problems/traffic-light-controlled-intersection/



class TrafficLight {
private:
    mutex switching;
    bool is_green_1;
public:
    TrafficLight() {
        is_green_1 = true; // initially the traffic light is green on road A, implies red on road B
    }

    void carArrived(
        int carId,                   // ID of the car
        int roadId,                  // ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        int direction,               // Direction of the car
        function<void()> turnGreen,  // Use turnGreen() to turn light to green on current road
        function<void()> crossCar    // Use crossCar() to make car cross the intersection
    ) {
        switching.lock();
        if( roadId == 1 ) {
            if( !is_green_1 ) {
                turnGreen();
                is_green_1 = true;
            }
        } else { // roadId == 2
            if( is_green_1 ) {
                turnGreen();
                is_green_1 = false;
            }
        }
        crossCar();
        switching.unlock();
    }
};
