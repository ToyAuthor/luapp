local std = require "std"

function func(a, b, c)
	print("func start")
	print("script:func() start")
	print("script:a =", a)
	print("script:b =", b)
	print("script:c =", c)

	local   x=std.sum(a,b,c)

	print("script:x =", x)
	print("script:func() end")

	print("func end")

	return x
end

function func2(a, b, c)
	print("func2 start")
	print("script:a =", a)
	print("script:b =", b)
	print("script:c =", c)
	print("func2 end")
end
