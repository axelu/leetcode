
# 2891. Method Chaining
# https://leetcode.com/problems/method-chaining/description/



import pandas as pd

def findHeavyAnimals(animals: pd.DataFrame) -> pd.DataFrame:
    heavy_animals = animals[animals["weight"] > 100].sort_values(by=['weight'], ascending=False)
    heavy_animals = heavy_animals[["name"]]
    return heavy_animals
