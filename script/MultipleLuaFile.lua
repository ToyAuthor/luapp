local std = require "std"

function func(a, b, c)
	local   x=std.sum(a,b,c)
	print( a .. "+" .. b .. "+" .. c .. "=" .. x)
	return x
end

print("Return value is " .. func(1,2,3))
