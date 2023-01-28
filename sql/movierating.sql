
-- 1341. Movie Rating
-- https://leetcode.com/problems/movie-rating/



/* Write your T-SQL query statement below */

with [user]
as
(
select top 1
 u.name as results
from
  (
    select
      user_id,
      rank() over(order by count(*) desc) as rnk
    from
      movierating
    group by
      user_id
  ) mr join users u on mr.user_id = u.user_id
where
  mr.rnk = 1
order by
  u.name
),
movie
as
(
select top 1
  m.title as results
from
  (
    select
      movie_id,
      rank() over (order by (cast(sum(rating) as decimal) / count(*)) desc) as rnk
    from
      movierating
    where
      datepart(year,created_at) = 2020 and
      datepart(month,created_at) = 2
    group by
      movie_id
  ) mr join movies m on mr.movie_id = m.movie_id
where
  mr.rnk = 1
order by
  m.title
)
select results from [user]
union all
select results from movie
