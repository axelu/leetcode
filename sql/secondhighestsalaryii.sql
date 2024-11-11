
-- 3338. Second Highest Salary II
-- https://leetcode.com/problems/second-highest-salary-ii/




/* Write your T-SQL query statement below */

with cte as
(
select
    emp_id,
    salary,
    dept,
    dense_rank() over(partition by dept order by salary desc) as rnk
from
    employees
)
-- select * from cte

select
    emp_id,
    dept
from
    cte
where
    rnk = 2
order by
    emp_id

