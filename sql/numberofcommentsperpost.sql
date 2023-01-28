
-- 1241. Number of Comments per Post
-- https://leetcode.com/problems/number-of-comments-per-post/


/* Write your T-SQL query statement below */

with t (post_id,comment_id)
as
(
    select
      distinct
      p.post_id,
      c.sub_id


    from
      (
        select
           distinct s.sub_id as post_id
        from
           submissions as s
        where
           s.parent_id is null
      ) as p left outer join submissions as c on p.post_id = c.parent_id
)
select t.post_id, 0 as number_of_comments
from t
where t.comment_id is null
union
select t.post_id,count(*)
from t
where t.comment_id is not null
group by t.post_id

order by post_id
