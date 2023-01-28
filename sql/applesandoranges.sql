
-- 1445. Apples & Oranges
-- https://leetcode.com/problems/apples-oranges/



/* Write your T-SQL query statement below */


-- diff =  apples - oranges

select
  sale_date
  ,apples-oranges as diff
from
(
select sale_date,fruit,sold_num from Sales
) as SourceTable pivot(sum(sold_num) for fruit in (apples,oranges)) as pivot_table
order by
  sale_date
