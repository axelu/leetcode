
-- 603. Consecutive Available Seats
-- https://leetcode.com/problems/consecutive-available-seats/



/* Write your T-SQL query statement below */

select
  t.seat_id
from (
    select
      c.seat_id,
      c.free,
      lag(c.free,1) over(order by c.seat_id) as lft,
      lead(c.free,1) over(order by c.seat_id) as rgt
    from
      cinema as c
) t
where
  t.free = 1 and
  (
      t.lft = 1 or t.rgt = 1
  )
order by
  t.seat_id
