
-- 2720. Popularity Percentage
-- https://leetcode.com/problems/popularity-percentage/





/* Write your T-SQL query statement below */


declare @user_cnt int;
set @user_cnt = (
select count(*) from
(
select user1 as userid from friends
union
select user2 from friends
) as t
);

with friends_cte
as
(
select user1 as userid, user2 as friendid from friends
union
select user2, user1 from friends
),
friendcount
as
(
select userid, count(*) as friend_cnt
from friends_cte
group by userid
)
select
  userid as user1,
  round(cast(sum(friend_cnt) as decimal)/@user_cnt*100,2) as percentage_popularity
from
  friendcount
group by
  userid
order by
  userid

