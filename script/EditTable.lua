
local tab =
{
	andy = 45,
	ss = "dd"
}

_G.GetTable = function()
	return tab
end

_G.SetTable = function(t)
	tab = t
end

function PrintMyAnswer()
	_G.PrintGlobalTable("table",tab)
end
