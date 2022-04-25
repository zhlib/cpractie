-- A solution contains projects, and defines the available configurations
solution ("practice")
configurations {"Release","Debug"}
location "build"
targetdir "build/bin"

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


p3 = project("openat")
basedir(p3.name)
location("build/" .. p3.name)
kind "ConsoleApp"
language "c"
files { p3.name .. "/*.h", p3.name .. "/*.c", "common/*.h", "common/*.c" }

filter "configurations:Debug"
defines { "DEBUG" }
symbols "On"

filter "configurations:Release"
defines { "NDEBUG" }
optimize "On"

p4 = project("dup2")
basedir(p4.name)
location("build/" .. p4.name)
kind "ConsoleApp"
language "c"
files { p4.name .. "/*.h", p4.name .. "/*.c", "common/*.h", "common/*.c" }

filter "configurations:Debug"
defines { "DEBUG" }
symbols "On"

filter "configurations:Release"
defines { "NDEBUG" }
optimize "On"



p5 = project("uid")
basedir(p5.name)
location("build/" .. p5.name)
kind "ConsoleApp"
language "c"
files { p5.name .. "/*.h", p5.name .. "/*.c", "common/*.h", "common/*.c" }

filter "configurations:Debug"
defines { "DEBUG" }
symbols "On"

filter "configurations:Release"
defines { "NDEBUG" }
optimize "On"

p6 = project("game")
basedir(p6.name)
location("build/" .. p6.name)
kind "ConsoleApp"
language "c"
links { "curses" }
files { p6.name .. "/*.h", p6.name .. "/*.c", "common/*.h", "common/*.c" }

filter "configurations:Debug"
defines { "DEBUG" }
symbols "On"

filter "configurations:Release"
defines { "NDEBUG" }
optimize "On"