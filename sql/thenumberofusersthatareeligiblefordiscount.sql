
-- 2205. The Number of Users That Are Eligible for Discount
-- https://leetcode.com/problems/the-number-of-users-that-are-eligible-for-discount/



CREATE FUNCTION getUserIDs(@startDate DATE, @endDate DATE, @minAmount INT) RETURNS INT AS
BEGIN

    declare @s DATETIME= @startDate;
    declare @e DATETIME= @endDate;

    RETURN (
        select count(*)
        from (
            select  distinct user_id
            from    purchases
            where   amount >= @minAmount
                    and time_stamp >= @s
                    and time_stamp <= @e
        ) as t
    );
END
