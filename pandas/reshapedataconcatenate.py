
# 2888. Reshape Data: Concatenate
# https://leetcode.com/problems/reshape-data-concatenate/






import pandas as pd

def concatenateTables(df1: pd.DataFrame, df2: pd.DataFrame) -> pd.DataFrame:
    return df1.merge(df2,how='outer')
