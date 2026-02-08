#include <iostream>

using namespace std;

void passFunc(int ***a) {
    cout << a[3][4][2] << endl;
}




// Driver program
int main()
{

    int _n = 4;
    int _max_picks = 4;

    int ***array;
    array = new int **[_n];
    for(int i = 0; i < _n; i++) {
        array[i] = new int *[_max_picks+1];
        for(int j = 0; j < _max_picks+1; ++j) {
            array[i][j] = new int[3];
        }
    }

    array[_n-1][_max_picks][2] = 101;
    passFunc(array);

    return 0;
}
