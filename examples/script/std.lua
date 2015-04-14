
--It's doesn't work since version 5.2
--module(..., package.seeall)


local function sum(a, b, c)
	print("Count sum")
	local   x=a+b+c
	return x
end

--Do what module() to do.
package.loaded.std={}
package.loaded.std.sum=sum
