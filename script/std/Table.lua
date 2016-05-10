
--Transform array<string> into map<string,number>
local function BuildEnum(i,t)

	local result={}

	for key, value in ipairs(t) do
		result[value]=key+i-1
	end

	return result
end

--Delete every each element of the table
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
	Copy(t,t1)
	Merge(t,t2)
	return t
end

--[[
for example

call MakeSeries(2,5,10)
equal fellowing work
t[2]=12
t[3]=13
t[4]=14
t[5]=15

call MakeSeries(4,8,3)
equal fellowing work
t[4]=7
t[5]=8
t[6]=9
t[7]=10
t[8]=11
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
	BuildEnum=BuildEnum,
	ReturnMerge=ReturnMerge,
	MakeSeries=MakeSeries,
	Merge=Merge,
	Clean=Clean,
	Copy=Copy
}
