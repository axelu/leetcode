
// 690. Employee Importance
// https://leetcode.com/problems/employee-importance/


/*
// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};
*/

class Solution {
private:
    int dfs(unordered_map<int,Employee*> um, int id) {
        Employee* employee = um.find(id)->second;
        int ans = employee->importance;
        for(int i = 0; i < employee->subordinates.size(); ++i)
            ans += dfs(um,employee->subordinates[i]);
        return ans;
    }

public:
    int getImportance(vector<Employee*> employees, int id) {
        unordered_map<int,Employee*> um;
        for(int i = 0; i < employees.size(); ++i)
            um.insert({employees[i]->id,employees[i]});
        return dfs(um,id);
    }
};
