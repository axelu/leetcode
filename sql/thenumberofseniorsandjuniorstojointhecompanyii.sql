
-- 2010. The Number of Seniors and Juniors to Join the Company II
-- https://leetcode.com/problems/the-number-of-seniors-and-juniors-to-join-the-company-ii/



/* Write your T-SQL query statement below */

declare @budget int;
set @budget = 70000;

with candidate_details
as
(
select
  employee_id,
  case when experience = 'Senior' then 1 else 2 end as exp, -- Seniors first
  salary
from
  candidates
),
seniors
as
(
select
  cd.employee_id,
  cd.exp,
  cd.salary,
  sum(cd.salary) over(order by cd.salary) as running_senior_salary_sum
from
  candidate_details cd
where
  cd.exp = 1
),
seniors_to_hire
as
(
select
  s.employee_id,
  s.exp,
  s.salary,
  s.running_senior_salary_sum
from
  seniors s
where
  s.running_senior_salary_sum <= @budget
),
seniors_to_hire_and_juniors
as
(
select
  cd.employee_id,
  cd.exp,
  cd.salary,
  sum(cd.salary) over(order by cd.exp,cd.salary) as running_salary_sum
from
  candidate_details cd
where
  cd.employee_id in (select sth.employee_id from seniors_to_hire sth) or
  cd.exp = 2
)
select
  employee_id
from
  seniors_to_hire_and_juniors
where
  running_salary_sum <= @budget
