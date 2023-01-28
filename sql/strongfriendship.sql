

-- 1949. Strong Friendship
-- https://leetcode.com/problems/strong-friendship/




/* Write your T-SQL query statement below */

with users
as
(
select
  user1_id as user_id
from
  friendship
union
select
  user2_id
from
  friendship
),
friends
as
(
select
  u.user_id,
  f.user2_id as friend_id
from
  users u join friendship f on u.user_id = f.user1_id
union
select
  u.user_id,
  f.user1_id as friend_id
from
  users u join friendship f on u.user_id = f.user2_id
)
select
  t.user1_id,
  t.user2_id,
  count(*) as common_friend
from
(
select
  f1.user_id as user1_id,
  f2.user_id as user2_id,
  f1.friend_id
from
  friends f1 join friends f2 on f1.friend_id = f2.friend_id and f1.user_id < f2.user_id
) t join friendship f on t.user1_id = f.user1_id and t.user2_id = f.user2_id -- they have to be friends
group by
  t.user1_id,t.user2_id
having
  count(*) > 2
