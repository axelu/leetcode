
# 2881. Create a New Column
# https://leetcode.com/problems/create-a-new-column/description/





import pandas as pd

def createBonusColumn(employees: pd.DataFrame) -> pd.DataFrame:
    employees.insert(2, 'bonus', employees['salary']*2)
    return employees
