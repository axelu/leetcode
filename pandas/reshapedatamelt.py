
# 2890. Reshape Data: Melt
# https://leetcode.com/problems/reshape-data-melt/




import pandas as pd

def meltTable(report: pd.DataFrame) -> pd.DataFrame:
    # unpivot
    report = report.melt(id_vars=['product'], value_vars=['quarter_1','quarter_2','quarter_3','quarter_4'], var_name='quarter', value_name='sales')
    return report
