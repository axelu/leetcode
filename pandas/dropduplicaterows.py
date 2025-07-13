
# 2882. Drop Duplicate Rows
# https://leetcode.com/problems/drop-duplicate-rows/




import pandas as pd

def dropDuplicateEmails(customers: pd.DataFrame) -> pd.DataFrame:
    customers.drop_duplicates(subset=['email'], keep='first', inplace=True)
    return customers
