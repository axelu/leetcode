
-- 2159. Order Two Columns Independently
-- https://leetcode.com/problems/order-two-columns-independently/




/* Write your T-SQL query statement below */

with a
as
(
select
  first_col,
  row_number() over(order by first_col) as rnk
from
  data
),
b
as
(
select
  second_col,
  row_number() over(order by second_col desc) as rnk
from
  data
)
select
  a.first_col,
  b.second_col
from
  a join b on a.rnk = b.rnk
order by
  a.first_col
