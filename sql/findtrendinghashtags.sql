
-- 3087. Find Trending Hashtags
-- https://leetcode.com/problems/find-trending-hashtags/




/* Write your T-SQL query statement below */

-- it is guaranteed that each tweet only contains one hashtag.

with hashtags as
(
select
    tweet_id,
    CASE
        when CHARINDEX(' ', tweet, CHARINDEX('#', tweet)) = 0
        then SUBSTRING(tweet, CHARINDEX('#', tweet), LEN(tweet) - CHARINDEX('#', tweet) + 1)
        else SUBSTRING(tweet, CHARINDEX('#', tweet), CHARINDEX(' ', tweet, CHARINDEX('#', tweet)) - CHARINDEX('#', tweet))
    END as hashtag
from
    Tweets
where
    tweet_date between '2024-02-01' and '2024-02-29'
)
select TOP(3)
    hashtag as HASHTAG,
    count(hashtag) as HASHTAG_COUNT
from
    hashtags
group by
    hashtag
order by
    count(hashtag) desc, hashtag desc
