
// 1534. Count good Triplets
// https://leetcode.com/problems/count-good-triplets/


class Solution {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int r = 0;

        auto ae = arr.end();
        for(auto iti = arr.begin(); iti != ae - 2; ++iti) {
            auto itj = iti + 1;

            for(; itj != ae - 1; ++itj) {
                if( abs(*iti - *itj) <= a ) {
                    auto itk = itj + 1;

                    for(; itk != ae; ++itk) {
                        if( abs(*itj - *itk) <= b && abs(*iti - *itk) <= c) {
                            /*
                            cout << "i " << iti - arr.begin() << " arr[i] " << *iti << endl;
                            cout << "j " << itj - arr.begin() << " arr[j] " << *itj << endl;
                            cout << "k " << itk - arr.begin() << " arr[k] " << *itk << endl;
                            */
                            ++r;
                        }
                    }
                }
            }
        }

        return r;
    }
};
