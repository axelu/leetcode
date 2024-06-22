
-- 3089. Find Bursty Behavior
-- https://leetcode.com/problems/find-bursty-behavior/




/* Write your T-SQL query statement below */

-- per problem description: Only include the dates from February 1 to February 28.

with feb2024_posts as
(
select user_id, post_date, count(post_id) as nbr_posts from Posts where post_date between '2024-02-01' and '2024-02-28' group by user_id, post_date
),
weekly_average as
(
select
    user_id,
    sum(nbr_posts) / 4.0 as avg_weekly_posts
from
    feb2024_posts
group by
    user_id
),
rolling_posts as
(
select
    o.user_id,
    o.post_date,
    case
        when DATEADD(dd, -6, o.post_date) < '2024-02-01'
        then '2024-02-01'
        else DATEADD(dd, -6, o.post_date)
    end as start_date
from
   feb2024_posts o
),
rolling_posts_count as
(
select
    o.user_id,
    (select sum(i.nbr_posts) from feb2024_posts i where i.post_date >= o.start_date and i.post_date <= o.post_date and i.user_id = o.user_id) as cnt
from
    rolling_posts o
),
rolling_posts_mx as
(
select
    user_id,
    max(cnt) as max_7day_posts
from
    rolling_posts_count
group by
    user_id
)
select
    m.user_id,
    m.max_7day_posts,
    a.avg_weekly_posts
from
    rolling_posts_mx as m join weekly_average as a on m.user_id = a.user_id
where
    m.max_7day_posts >= 2 * a.avg_weekly_posts
order by
    m.user_id
