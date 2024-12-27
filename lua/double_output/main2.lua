local leftCount = 0  -- Count of how many times "Left" has been printed
local rightCount = 0 -- Count of how many times "Right" has been printed

local function output()
	if leftCount < 2 then
		print("Left")
		leftCount = leftCount + 1
	else
		print("Right")
		rightCount = rightCount + 1
		if rightCount == 2 then
			-- Reset counts after printing two "Right"
			leftCount = 0
			rightCount = 0
		end
	end
end

for i = 1, 14 do  -- Adjust this number for more repetitions of the pattern
	output()
end
