
local function PrintGlobalTable(t)

	local indent_dev =
	{
		str = function (self)
			return string.rep(self._text,self._size)
		end,

		move = function (self,offset)
			self._size = self._size + offset
		end,

		_size = 0,
		_text = "    "     -- Tab size
	}

	local function modify_key(key)
		if type(key)=="string" then
			key = [["]] .. key .. [["]]
		elseif type(key)=="boolean" then
			if key then
				key = "true"
			else
				key = "false"
			end
		end

		return key
	end

	local function print_table(tt,indent)

		print(indent:str() .. "{")
		indent:move(1)

		for key, value in pairs(tt) do

			key = modify_key(key)

			if type(value)=="table" then
				print(indent:str() .. key .. " =")
				print_table(value,indent)
			elseif type(value)=="string" then
				print(indent:str() .. key .. [[ = "]] .. value .. [["]])
			elseif type(value)=="boolean" then
				if value then
					print(indent:str() .. key .. " = " .. "true")
				else
					print(indent:str() .. key .. " = " .. "false")
				end
		--	elseif type(value)=="userdata" then     No, no such option. Too bad.
			else
				print(indent:str() .. key .. " = " .. value)
			end
		end

		indent:move(-1)
		print(indent:str() .. "}")
	end

	print(t .. " =")
	print_table(_G[t],indent_dev)
end

print("cpp_number = " .. _G.cpp_number)

print("----------------------------------")

PrintGlobalTable("cpp_table")
