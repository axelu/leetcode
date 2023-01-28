
-- 1892. Page Recommendations II
-- https://leetcode.com/problems/page-recommendations-ii/


/* Write your T-SQL query statement below */

with uf -- users and their friends
as
(
select
  user1_id as user_id,
  user2_id as friend_id
from
  friendship
union
select
  user2_id as user_id,
  user1_id as friend_id
from
  friendship
),

page_likes
as
(
select
  uf.user_id,
  uf.friend_id,
  l.page_id
from
  uf join likes l
    on uf.friend_id = l.user_id and
    l.page_id not in (select page_id from likes where user_id = uf.user_id)
)

select
  pl.user_id,
  pl.page_id,
  count(*) as friends_likes
from
  page_likes pl
group by
  pl.user_id,
  pl.page_id
