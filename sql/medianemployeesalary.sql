
-- 569. Median Employee Salary
-- https://leetcode.com/problems/median-employee-salary/




/* Write your T-SQL query statement below */

with emp_count
as
(
    select distinct
      company,
      count(*) over(partition by company) as cnt
    from
      employee
),
odd_emp_salaries
as
(
select
  e.id,
  e.company,
  e.salary,
  rank() over(partition by e.company order by e.salary, e.id) as rnk
from
  employee e join emp_count c on e.company = c.company
where
  c.cnt % 2 = 1
),
even_emp_salaries
as
(
select
  e.id,
  e.company,
  e.salary,
  rank() over(partition by e.company order by e.salary, e.id) as rnk
from
  employee e join emp_count c on e.company = c.company
where
  c.cnt % 2 = 0
)

-- median salary of companies with odd employee count
select
  o.id,
  o.company,
  o.salary
from
  odd_emp_salaries o join emp_count c on o.company = c.company
where
  o.rnk = c.cnt/2 + 1

union

-- median salary of companies with even employee count
select
  e.id,
  e.company,
  e.salary
from
  even_emp_salaries e join emp_count c on e.company = c.company
where
  e.rnk = c.cnt/2 or e.rnk = c.cnt/2 + 1

