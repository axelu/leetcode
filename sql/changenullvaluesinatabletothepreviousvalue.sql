
-- 2388. Change Null Values in a Table to the Previous Value
-- https://leetcode.com/problems/change-null-values-in-a-table-to-the-previous-value/



/* Write your T-SQL query statement below */

-- forward fill
-- https://www.andrewvillazon.com/forward-fill-values-t-sql/

with a (rownbr,id,drink)
as
(
select
  row_number() over(order by (select null)) as rownbr,
  id,
  drink
from
  coffeeshop
)
select
  id,
  case
    when drink is null then (
            select top 1
                inner_table.drink
            from
                a as inner_table
            where
                inner_table.rownbr < a.rownbr and
                inner_table.drink is not null
            order by
                inner_table.rownbr desc
        )
    else
        drink
  end as drink
FROM
    a
