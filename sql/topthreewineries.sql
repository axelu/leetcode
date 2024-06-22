
-- 2991. Top Three Wineries
-- https://leetcode.com/problems/top-three-wineries/





/* Write your T-SQL query statement below */

-- assume points, winery will give unique rank

with wineries_sumd as
(
select
    country,
    winery,
    SUM(points) as points
from
    Wineries
group by
    country, winery
),
wineries_ranked as
(
select
    country,
    points,
    winery,
    RANK() over(partition by country order by points desc, winery) as rnk
from
    wineries_sumd
),
countries as
(
select distinct country from Wineries
)
select
    c.country,
    (select
        wr.winery + ' (' + CAST(wr.points as nvarchar) + ')' as top_winery
     from
        wineries_ranked as wr
     where
        wr.country = c.country and
        wr.rnk = 1
    ) as top_winery,
    CASE
        when (select count(*) from wineries_ranked as wr where wr.country = c.country and wr.rnk = 2) <> 0
        then
            (select
                wr.winery + ' (' + CAST(wr.points as nvarchar) + ')'
             from
                wineries_ranked as wr
             where
                wr.country = c.country and
                wr.rnk = 2
            )
        else 'No second winery'
    END as second_winery,
    CASE
        when (select count(*) from wineries_ranked as wr where wr.country = c.country and wr.rnk = 3) <> 0
        then
            (select
                wr.winery + ' (' + CAST(wr.points as nvarchar) + ')'
             from
                wineries_ranked as wr
             where
                wr.country = c.country and
                wr.rnk = 3
            )
        else 'No third winery'
    END as third_winery
from
    countries as c
order by
    c.country
