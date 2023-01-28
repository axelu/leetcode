
-- 2314. The First Day of the Maximum Recorded Degree in Each City
-- https://leetcode.com/problems/the-first-day-of-the-maximum-recorded-degree-in-each-city/


/* Write your T-SQL query statement below */

select
  t.city_id,
  t.day,
  t.degree
from (
    select
      city_id,
      day,
      degree,
      rank() over(partition by city_id order by degree desc,day) as rnk
    from
      weather
) t
where
  t.rnk = 1
order by
  t.city_id
