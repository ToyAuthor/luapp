local std = require "std"

function func(a, b, c)
	local   x=std.sum(a,b,c)
	print( a .. "+" .. b .. "+" .. c .. "=" .. x)
	return x
end
