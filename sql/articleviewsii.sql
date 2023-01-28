
-- 1149. Article Views II
-- https://leetcode.com/problems/article-views-ii/

/* Write your T-SQL query statement below */

with avd
as
(
select distinct
  article_id,
  viewer_id,
  view_date
from
  views
)
select distinct
  viewer_id as id
from
  avd
group by
  viewer_id,view_date
having
  count(*) > 1
order by
  viewer_id
