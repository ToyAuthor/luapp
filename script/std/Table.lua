
-- Transform array<string> into map<string,number>. Return table will look like C/C++ enum.
local function MakeEnum(i,t)
	local result={}

	for key, value in ipairs(t) do
		result[value]=key+i-1
	end

	return result
end

-- Delete every each element of the table
local function Clean(t)
	for k in pairs(t) do
		t[k]=nil
	end
end

-- t1 = t1 + t2
local function Merge(t1,t2)
	for key, value in pairs(t2) do
		t1[key]=value
	end
end

-- t1 = t2
local function Copy(t1,t2)
	Clean(t1)
	Merge(t1,t2)
end

-- return t1 + t2
local function ReturnMerge(t1,t2)
	local t={}
	Merge(t,t1)
	Merge(t,t2)
	return t
end

--[[
	Call MakeSeries(x,y,z) will return this table:
	t =
	{
		[x  ] = z + x ,
		[x+1] = z + x + 1,
		[x+2] = z + x + 2,
		[x+3] = z + x + 3,
		...
		[y  ] = z + y
	}
]]
local function MakeSeries(start,ending,offset)
	local t={}

	for i=start,ending do
		t[i]=i+offset
	end

	return t
end

return
{
	mix = ReturnMerge,
	enum = MakeEnum,
	copy = Copy,
	merge = Merge,
	clean = Clean,
	series = MakeSeries
}
