
-- 2230. The Users That Are Eligible for Discount
-- https://leetcode.com/problems/the-users-that-are-eligible-for-discount/




CREATE PROCEDURE getUserIDs(@startDate DATE, @endDate DATE, @minAmount INT) AS
BEGIN
    /* Write your T-SQL query statement below. */

    declare @s DATETIME= @startDate;
    declare @e DATETIME= @endDate;

    select  distinct user_id
    from    purchases
    where   amount >= @minAmount
            and time_stamp >= @s
            and time_stamp <= @e;
END
