
-- 1919. Leetcodify Similar Friends
-- https://leetcode.com/problems/leetcodify-similar-friends/



/* Write your T-SQL query statement below */

with listened
as
(
select distinct
  user_id,
  song_id,
  day
from
  listens
),

similar as
(
select
  l.user_id as user1_id,
  l.song_id,
  l.day,
  o.user_id as user2_id
from
  listened l join listened o on l.day = o.day and l.song_id = o.song_id and l.user_id <> o.user_id
),

same_day_listening
as
(
select distinct
  case when s.user1_id < s.user2_id then s.user1_id else s.user2_id end as user1_id,
  case when s.user1_id > s.user2_id then s.user1_id else s.user2_id end as user2_id,
  s.day
from
  similar s
group by
  s.user1_id,
  s.user2_id,
  s.day
having
  count(*) >= 3
)

select distinct
  sdl.user1_id,
  sdl.user2_id
from
  same_day_listening sdl join friendship f on sdl.user1_id = f.user1_id and sdl.user2_id = f.user2_id
