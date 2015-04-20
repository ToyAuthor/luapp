local std = require "std"

function func(a, b, c)

	print("script:func() start")
	print("script:a =", a)
	print("script:b =", b)
	print("script:c =", c)

	local   x=std.sum(a,b,c)

	print("script:x =", x)
	print("script:func() end")

	return x
end
