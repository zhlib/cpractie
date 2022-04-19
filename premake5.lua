-- A solution contains projects, and defines the available configurations
solution ("practice")
configurations {"Release","Debug"}
location "build"
targetdir "output"

-- A project defines one build target
p1 = project("hello1")
basedir(p1.name)
location("build/" .. p1.name)
kind "ConsoleApp"
language "c"
files { p1.name .. "/*.h", p1.name .. "/*.c", "common/*.h", "common/*.c" }

filter "configurations:Debug"
defines { "DEBUG" }
symbols "On"

filter "configurations:Release"
defines { "NDEBUG" }
optimize "On"


-- A project defines one build target
p2 = project("hello2")
basedir(p2.name)
location("build/" .. p2.name)
kind "ConsoleApp"
language "c"
files { p2.name .. "/*.h", p2.name .. "/*.c", "common/*.h", "common/*.c" }

filter "configurations:Debug"
defines { "DEBUG" }
symbols "On"

filter "configurations:Release"
defines { "NDEBUG" }
optimize "On"