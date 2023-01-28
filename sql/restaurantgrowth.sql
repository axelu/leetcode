
-- 1321. Restaurant Growth
-- https://leetcode.com/problems/restaurant-growth/


/* Write your T-SQL query statement below */

with a
as
(
select
  row_number() over(order by visited_on) as rownbr,
  visited_on,
  sum(amount) as amount
from
  customer
group by
  visited_on
),
b as
(
select
  visited_on,
  (select
     sum(inner_table.amount)
   from
     a as inner_table
   where
     inner_table.rownbr between a.rownbr - 6 and a.rownbr
  ) as amount
from
  a
where
  a.rownbr > 6
)
select
  visited_on,
  amount,
  round(cast(amount as decimal)/7,2) as average_amount
from
  b
order by
  visited_on
