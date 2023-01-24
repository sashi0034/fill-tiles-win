
local function fixReadonly(table)
    return setmetatable({}, {
      __index = table,
      __newindex = function(table, key, value)
                     error("Attempt to modify read-only table")
                   end,
      __metatable = false
    });
 end

return fixReadonly
