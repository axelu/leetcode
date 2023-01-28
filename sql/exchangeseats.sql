
-- 626. Exchange Seats
-- https://leetcode.com/problems/exchange-seats/



/* Write your T-SQL query statement below */

select
  t.id,
  case when t.next_student is null and row_number() over(ORDER BY id) % 2 = 1 then student
       when row_number() over(ORDER BY id) % 2 = 1 then t.next_student else t.previous_student
  end as student
from (
select
  row_number() over(ORDER BY id) as row_nbr,
  id,
  student,
  LAG(student,1) OVER (ORDER BY id) AS previous_student,
  LEAD(student,1) OVER (ORDER BY id) AS next_student
from
  seat
) t
order by
  id
