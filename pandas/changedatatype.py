
# 2886. Change Data Type
# https://leetcode.com/problems/change-data-type/




import pandas as pd

def changeDatatype(students: pd.DataFrame) -> pd.DataFrame:
    # print(students.dtypes)
    students = students.astype({'grade': 'Int64'})
    # print(students.dtypes)
    return students
