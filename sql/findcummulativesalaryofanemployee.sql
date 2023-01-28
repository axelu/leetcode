
-- 579. Find Cumulative Salary of an Employee
-- https://leetcode.com/problems/find-cumulative-salary-of-an-employee/





/* Write your T-SQL query statement below */

with cte
as
(
select
  id,
  month,
  salary,
  case
    when lag(month,1) over(partition by id order by month) is null
    then 0
    else
      case
        when lag(month,1) over(partition by id order by month) = month-1
        then lag(salary,1) over(partition by id order by month)
        else 0
      end
  end as prior_month,
  case
    when lag(month,2) over(partition by id order by month) is null
    then 0
    else
      case
        when lag(month,2) over(partition by id order by month) = month-2
        then lag(salary,2) over(partition by id order by month)
        else 0
      end
  end as prior_prior_month,
  case
    when lead(month,1) over(partition by id order by month) is null
    then 1
    else 0
  end as last_month
from
  employee
)

select
  id,
  month,
  salary + prior_month + prior_prior_month as salary
from
  cte
where
  last_month = 0
order by
  id,
  month desc
