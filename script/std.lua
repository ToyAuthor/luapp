
--The function module() is doesn't work since version 5.2
--module(..., package.seeall)


local function sum(a, b, c)
	local   x=a+b+c
	return x
end


--Do what module() to do.
return {sum=sum}
