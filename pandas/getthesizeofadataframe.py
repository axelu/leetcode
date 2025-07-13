
# 2878. Get the Size of a DataFrame
# https://leetcode.com/problems/get-the-size-of-a-dataframe/description/





import pandas as pd

def getDataframeSize(players: pd.DataFrame) -> List[int]:
    t = players.shape
    return [t[0],t[1]]
