
local tab = require "std.Table"

function func(a, b, c)
	local   x=5
	a, b, c=1,2,3
	print( a .. "+" .. b .. "+" .. c .. "=" .. x)
	return x
end
