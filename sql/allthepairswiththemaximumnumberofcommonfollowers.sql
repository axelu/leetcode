
-- 1951. All the Pairs With the Maximum Number of Common Followers
-- https://leetcode.com/problems/all-the-pairs-with-the-maximum-number-of-common-followers/



/* Write your T-SQL query statement below */

select
  t.user1_id,
  t.user2_id
from (
    select
      t.user1_id,
      t.user2_id,
      rank() over(order by t.cnt desc) as rnk
    from (
        select
          t.user1_id,
          t.user2_id,
          count(*) as cnt
        from (
            select
              a.user_id as user1_id,
              b.user_id as user2_id,
              a.follower_id as follower_a,
              b.follower_id as follower_b
            from
              relations a, relations b
            where
              a.user_id < b.user_id and
              a.follower_id = b.follower_id
          ) t
        group by
          t.user1_id,t.user2_id
      ) t
  ) t
where
  t.rnk = 1
