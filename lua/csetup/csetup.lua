#!/usr/bin/env lua

if #arg < 2 then
	print(string.format("Usage: %s <bin>", arg[0]))
end

if arg[2] == "clean" then
	os.remove(arg[1])
	os.remove(arg[1] .. ".c")
	os.remove("makefile")
	os.remove("compile_commands.json")
	os.execute("rm -rf .ccls-cache")
	os.exit()
end

local bin = io.open(arg[1] .. ".c", "w")
if bin then
	bin:write("#include <stdlib.h>\n")
	bin:write("#include <stdio.h>\n")
	bin:write("#include <string.h>\n")
	bin:write("#include <unistd.h>\n")
	bin:write("\nint main(void) {\n\n\treturn EXIT_SUCCESS;\n}")
	bin:close()
end

local makefile = io.open("makefile", "w")
if makefile then
	makefile:write("cc=clang\n\n")
	makefile:write("all: " .. arg[1] .. "\n")
	makefile:write("\n%: %.c\n")
	makefile:write("\t$(cc) -o $@ $^")
	makefile:close()
end

os.execute("bear -- make")
