print("Hello, world!")
os.execute("ls")
local file = io.open("hello.lua", "r")
if file then
	local content = file:read("*a")
	print(content)
	file:close()
else
	print("Couldn't open file")
end
