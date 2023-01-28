
// 2408. Design SQL
// https://leetcode.com/problems/design-sql/



class SQL {
private:
    unordered_map<string,unordered_map<int,vector<string>>> db;
    unordered_map<string,int> next_id;

public:
    SQL(vector<string>& names, vector<int>& columns) {
       for(auto& name: names)
           next_id.insert({name,1});
    }

    void insertRow(string name, vector<string> row) {
        int id = next_id[name]++;

        /*
        cout << "insert table " << name << " rowId " << id;
        for(int i = 0; i < row.size(); ++i)
            cout << " " << i << ":" << row[i];
        cout << endl;
        */

        db[name][id] = row;
    }

    void deleteRow(string name, int rowId) {
        auto table = db[name];
        table.erase(rowId);
    }

    string selectCell(string name, int rowId, int columnId) {
        return db[name][rowId][columnId-1];
    }
};

/**
 * Your SQL object will be instantiated and called as such:
 * SQL* obj = new SQL(names, columns);
 * obj->insertRow(name,row);
 * obj->deleteRow(name,rowId);
 * string param_3 = obj->selectCell(name,rowId,columnId);
 */
