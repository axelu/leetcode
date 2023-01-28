
-- 571. Find Median Given Frequency of Numbers
-- https://leetcode.com/problems/find-median-given-frequency-of-numbers/




/* Write your T-SQL query statement below */

declare @hlf int;
set @hlf = (select sum(frequency) from numbers);

if @hlf % 2 = 0 -- even

with f1
as
(
select
  num,
  frequency,
  sum(frequency) over(order by num) as last
from
  numbers
),

f2
as
(
select
  f1.num,
  f1.frequency,
  isnull(lag(f1.last) over(order by f1.num)+1,1) as start,
  f1.last
from
  f1
),

f3
as
(
select
  num
from
  f2
where
  (start <= @hlf/2 and last >= @hlf/2) or
  (start <= (@hlf/2)+1 and last >= (@hlf/2)+1)
)

select
  case
    when (select count(*) from f3) = 2
    then round(cast((select sum(num) from f3) as decimal)/2,1)
    else (select sum(num) from f3)
  end as median


else -- odd

with f1
as
(
select
  num,
  frequency,
  sum(frequency) over(order by num) as last
from
  numbers
),

f2
as
(
select
  f1.num,
  f1.frequency,
  isnull(lag(f1.last) over(order by f1.num)+1,1) as start,
  f1.last
from
  f1
)

select
  num as median
from
  f2
where
  (start <= (@hlf/2)+1 and last >= (@hlf/2)+1)
