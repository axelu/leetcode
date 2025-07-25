
# 2889. Reshape Data: Pivot
# https://leetcode.com/problems/reshape-data-pivot/




import pandas as pd

def pivotTable(weather: pd.DataFrame) -> pd.DataFrame:
    weather = weather.pivot(index='month', columns='city', values='temperature')
    return weather
