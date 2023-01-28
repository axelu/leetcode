
-- 2004. The Number of Seniors and Juniors to Join the Company
-- https://leetcode.com/problems/the-number-of-seniors-and-juniors-to-join-the-company/


/* Write your T-SQL query statement below */

declare @budget int;
set @budget = 70000;

with experience_level
as
(
    select * from ( values
        ('Senior',1),('Junior',2) -- Seniors first
    ) t(experience,exp)
),

candidate_details
as
(
select
  c.employee_id,
  e.exp,
  c.salary
from
  candidates c join experience_level e on c.experience = e.experience
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
),

hire as
(
select
  e.experience,
  count(*) as cnt
from
  seniors_to_hire_and_juniors h join experience_level e on h.exp = e.exp
where
  h.running_salary_sum <= @budget
group by
  e.experience
)

select
  e.experience,
  isnull(h.cnt,0) as accepted_candidates
from
  experience_level e left join hire h on e.experience = h.experience
