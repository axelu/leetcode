
# 2880. Select Data
# https://leetcode.com/problems/select-data/description/




import pandas as pd

def selectData(students: pd.DataFrame) -> pd.DataFrame:
    student_101 = students[students["student_id"] == 101]
    student_101 = student_101[["name", "age"]]
    return student_101
