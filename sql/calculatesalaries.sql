
-- 1468. Calculate Salaries
-- https://leetcode.com/problems/calculate-salaries/



/* Write your T-SQL query statement below */

with cte (company_id,bracket)
as
(
select
  company_id,
  case when max(salary) > 10000 then 49
       when max(salary) > 999 then 24 else 0
  end as bracket
from
  salaries
group by
  company_id
)
select
  s.company_id,
  s.employee_id,
  s.employee_name,
  round(s.salary - cast(cte.bracket as decimal)/100*s.salary,0) as salary
from
  salaries s inner join cte on s.company_id = cte.company_id
