
-- 1308. Running Total for Different Genders
-- https://leetcode.com/problems/running-total-for-different-genders/



/* Write your T-SQL query statement below */

select
  t.gender
  ,t.day
  ,sum(daily_total) over (partition by t.gender order by t.day) as total
from
(
select
  gender
  ,day
  ,sum(score_points) as daily_total
from
  scores
group by
  gender,day
) t
order by
  t.gender,t.day
