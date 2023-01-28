

/*

1917. Leetcodify Friends Recommendations
https://leetcode.com/problems/leetcodify-friends-recommendations/


Note: couldn't make TSQL solution pass, had it as passing all test cases but taking to long

*/




# Write your MySQL query statement below

select distinct
  l1.user_id,
  l2.user_id as recommended_id
from
  listens l1 join listens l2 on l1.song_id = l2.song_id and l1.day = l2.day and l1.user_id <> l2.user_id
        left join friendship f1 on l1.user_id = f1.user1_id and l2.user_id = f1.user2_id
        left join friendship f2 on l1.user_id = f2.user2_id and l2.user_id = f2.user1_id
where
  f1.user1_id is null and
  f2.user1_id is null
group by
  l1.user_id,
  l2.user_id,
  l1.day
having
  count(distinct l1.song_id) >= 3

