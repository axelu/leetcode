
-- 1264. Page Recommendations
-- https://leetcode.com/problems/page-recommendations/



/* Write your T-SQL query statement below */

-- we will assume that friendship.user1_id <> friendship.user2_id

with cte
as
(
select
  user2_id as user_id
from
  friendship
where
  user1_id = 1
union
select
  user1_id as user_id
from
  friendship
where
  user2_id = 1
)
select distinct
  page_id as recommended_page
from
  likes
where
  user_id in (select user_id from cte) and
  page_id not in (select page_id from likes where user_id = 1)

