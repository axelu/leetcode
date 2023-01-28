
-- 2253. Dynamic Unpivoting of a Table
-- https://leetcode.com/problems/dynamic-unpivoting-of-a-table/



CREATE PROCEDURE UnpivotProducts AS
BEGIN
    /* Write your T-SQL query statement below. */

    declare @colsunpivot as nvarchar(MAX);
    set @colsunpivot = STUFF((
        SELECT ',' + store
        FROM (
            select
                COLUMN_NAME as store
            from
                INFORMATION_SCHEMA.COLUMNS
            where
                TABLE_NAME = 'Products' and column_name <> 'product_id'
            ) t
        FOR XML PATH(''))
    ,1,1,'');

    -- select @colsunpivot;

    declare @query as nvarchar(MAX);
    set @query = '
        SELECT product_id, store, price
        FROM
          (
            SELECT * FROM products
          ) p
        UNPIVOT (price FOR store IN (' + @colsunpivot + ')
        )AS unpvt';

    execute(@query);
END
