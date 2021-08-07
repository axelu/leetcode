#include <iostream>

using namespace std;

void passFunc(int **a) {
    cout << a[5][5] << endl;
}




// Driver program
int main()
{

    int **array;
    array = new int *[10];
    for(int i = 0; i <10; i++)
        array[i] = new int[10];
    array[5][5] = 101;
    passFunc(array);

    return 0;
}
