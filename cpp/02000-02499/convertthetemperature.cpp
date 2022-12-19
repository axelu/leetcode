
// 2469. Convert the Temperature
// https://leetcode.com/problems/convert-the-temperature/




class Solution {
public:
    vector<double> convertTemperature(double celsius) {

        double kelvin = celsius + 273.15;
        double fahrenheit = celsius * 1.8 + 32;

        return {kelvin,fahrenheit};
    }
};
