
# 512. Game Play Analysis II
# https://leetcode.com/problems/game-play-analysis-ii/




# Write your MySQL query statement below


select
    player_id,
    device_id
from (

    select
        player_id,
        device_id,
        rank() over (partition by player_id order by event_date) rnk
    from
        Activity

) _activity
where rnk = 1
