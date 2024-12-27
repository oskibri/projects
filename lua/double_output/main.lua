local count = 0

local function output()
	if count < 2 then
		print("Left")
		count = count + 1
	else
		print("Right")
		count = count + 1

		if count >= 4 then
			count = 0
		end
	end
end

for _ = 1, 5 do
	output()
end
