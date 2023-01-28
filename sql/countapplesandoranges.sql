
-- 1715. Count Apples and Oranges
-- https://leetcode.com/problems/count-apples-and-oranges/



/* Write your T-SQL query statement below */

select
  sum(t.apple_count) as apple_count,
  sum(t.orange_count) as orange_count
from
(
select
  b.box_id,
  case
    when c.chest_id is not null then b.apple_count + c.apple_count else b.apple_count
  end as apple_count,
  case
    when c.chest_id is not null then b.orange_count + c.orange_count else b.orange_count
  end as orange_count
from
  boxes b left outer join chests c on b.chest_id = c.chest_id
) t
