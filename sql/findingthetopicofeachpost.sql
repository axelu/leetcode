
-- 2199. Finding the Topic of Each Post
-- https://leetcode.com/problems/finding-the-topic-of-each-post/




/* Write your T-SQL query statement below */

with post_keywords
as
(
select
  post_id,
  cs.Value as word --SplitData
from
  posts
cross apply STRING_SPLIT (content, ' ') cs
),

post_topics
as
(
select distinct
  p.post_id,
  k.topic_id
from
  post_keywords p join keywords k on p.word = k.word
)

select
  p.post_id,
  stuff((
        select ',' + convert(varchar,i.topic_id)
        from post_topics i
        where p.post_id = i.post_id
        order by i.topic_id asc
        for xml path('')
    ), 1, 1, ''
  ) as topic
from
  post_topics p
group by
  p.post_id

union
select
  post_id,
  'Ambiguous!'
from
  posts
where
  post_id not in (select distinct post_id from post_topics)
