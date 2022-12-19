
-- 2377. Sort the Olympic Table
-- https://leetcode.com/problems/sort-the-olympic-table/


/* Write your T-SQL query statement below */

select
  country,
  gold_medals,
  silver_medals,
  bronze_medals
from
  olympic
order by gold_medals desc, silver_medals desc, bronze_medals desc, country
