
local t = require ("module")

local a = 1
local b = 2

print(a .. "+" .. b .. "=" .. t.count(a,b))

local obj = t.NewObject()
print("Message frome C++: " .. obj:name())
