
-- 2346. Compute the Rank as a Percentage
-- https://leetcode.com/problems/compute-the-rank-as-a-percentage/



/* Write your T-SQL query statement below */

with department_cnt
as
(
select department_id, count(*) as cnt from students group by department_id
),
student_rank
as
(
select
  student_id,
  department_id,
  mark,
  rank() over(partition by department_id order by mark desc) as rnk
from
  students
)
select
  sr.student_id,
  sr.department_id,
  case
    when d.cnt = 1
    then 0.0
    else round(((sr.rnk - 1) * 100.0)/(d.cnt - 1),2)
  end as percentage
from
  student_rank sr join department_cnt d on sr.department_id = d.department_id
