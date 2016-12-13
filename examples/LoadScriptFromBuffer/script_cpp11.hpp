
#pragma once

inline lua::Str GetSubFileScript()
{
	lua::Str   str = R"(
		return
		{
			double = function(x)
				return x*2
			end
		}
	)";

	return str;
}

inline lua::Str GetMainFileScript()
{
	lua::Str   str = R"(
		local tt = require "ssd.subfile"
		local obj = NewClass()
		print( tt.double(obj:add(1,2,3)) )
	)";

	return str;
}
