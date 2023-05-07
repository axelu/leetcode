
-- 2669. Count Artist Occurrences On Spotify Ranking List
-- https://leetcode.com/problems/count-artist-occurrences-on-spotify-ranking-list/




/* Write your T-SQL query statement below */

select
  artist,
  count(*) as occurrences
from
  Spotify
group by
  artist
order by
  count(*) desc, artist
