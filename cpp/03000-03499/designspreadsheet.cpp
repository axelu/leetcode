
// 3484. Design Spreadsheet
// https://leetcode.com/problems/design-spreadsheet/




class Spreadsheet {
private:
    // rows max 1000, cols A-Z
    int wb[1001][26];

public:
    Spreadsheet(int rows) {
        memset(wb,0,sizeof wb);
    }

    void setCell(string cell, int value) {
        int j = cell[0] - 'A';
        int i = stoi(cell.substr(1));
        wb[i][j] = value;
    }

    void resetCell(string cell) {
        int j = cell[0] - 'A';
        int i = stoi(cell.substr(1));
        wb[i][j] = 0;
    }

    int getValue(string formula) {
        formula.erase(formula.begin()); // remove = from begin
        int plussignpos = formula.find('+');

        string str_A = formula.substr(0, plussignpos);
        int A;
        if( isdigit(str_A[0]) ) {
            A = stoi(str_A);
        } else {
            int j = str_A[0] - 'A';
            int i = stoi(str_A.substr(1));
            A = wb[i][j];
        }

        string str_B = formula.substr(plussignpos+1);
        int B;
        if( isdigit(str_B[0]) ) {
            B = stoi(str_B);
        } else {
            int j = str_B[0] - 'A';
            int i = stoi(str_B.substr(1));
            B = wb[i][j];
        }

        return A + B;
    }
};

/**
 * Your Spreadsheet object will be instantiated and called as such:
 * Spreadsheet* obj = new Spreadsheet(rows);
 * obj->setCell(cell,value);
 * obj->resetCell(cell);
 * int param_3 = obj->getValue(formula);
 */
