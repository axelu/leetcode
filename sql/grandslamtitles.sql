
-- 1783. Grand Slam Titles
-- https://leetcode.com/problems/grand-slam-titles/



/* Write your T-SQL query statement below */


select
  t.winner as player_id
  ,p.player_name
  ,count(*) as grand_slams_count
from (
    SELECT year, tournament, winner
    FROM
       (SELECT year, wimbledon, fr_open, us_open, au_open
       FROM championships) p
    UNPIVOT
       (winner FOR tournament IN
          (wimbledon, fr_open, us_open, au_open)
    ) AS unpvt
  ) t inner join players p on p.player_id = t.winner
group by
  t.winner,p.player_name
