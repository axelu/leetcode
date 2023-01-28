
-- 614. Second Degree Follower
-- https://leetcode.com/problems/second-degree-follower/



/* Write your T-SQL query statement below */

-- users who follow at least one other user => candidates
with followers
as
(
select distinct follower from follow
)
select
  f.followee as follower,
  count(*) as num
from
  follow f join followers i on f.followee = i.follower
group by
  f.followee
order by
  f.followee
