
-- 3103. Find Trending Hashtags II
-- https://leetcode.com/problems/find-trending-hashtags-ii/




/* Write your T-SQL query statement below */

with tweet_split as
(
SELECT tweet_id, value
FROM Tweets
    CROSS APPLY STRING_SPLIT(tweet, ' ')
where
    tweet_date between '2024-02-01' and '2024-02-29'
)
select top(3)
    value as hashtag,
    count(*) as [count]
from
    tweet_split
where
    value like '#%'
group by
    value
order by
    count(*) desc, value desc

