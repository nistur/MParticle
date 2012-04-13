-- Particle system project
solution "MParticle"
	configurations { "Debug", "Release" }
	language "C++"

	print(os.getenv("MSDKDIR"))		
	-- make sure we can search and link properly
	libdirs { os.getenv("MSDKDIR") .. "SDK/MCore/Libs",
				os.getenv("MSDKDIR") .. "SDK/MGui/Libs",
				os.getenv("MSDKDIR") .. "SDK/MEngine/Libs"}
	includedirs { os.getenv("MSDKDIR") .. "SDK/MCore/Includes",
				os.getenv("MSDKDIR") .. "SDK/MGui/Includes",
				os.getenv("MSDKDIR") .. "SDK/MEngine/Includes",
				"."}

	-- OS defines
	if os.is("windows") then
		defines { "WIN32" }
	end
		
	project "MParticle"
		kind "SharedLib"
		language "C++"

		-- include all the files, including Maratis SDK ones
		files {
			"**.cpp",
			"**.h",
			"**.md",
			os.getenv("MSDKDIR") .. "SDK/**.h"
		}

		-- split the files up a bit nicer inside Visual Studio
		vpaths { 
			["MCore/*"] = os.getenv("MSDKDIR") .. "SDK/MCore/Includes/**.h",
			["MEngine/*"] = os.getenv("MSDKDIR") .. "SDK/MEngine/Includes/**.h",
			["MGui/*"] = os.getenv("MSDKDIR") .. "SDK/MGui/Includes/**.h",
			["Game/*"] = { "**.h", "**.cpp" },
			["Doc/*"] = { "**.md" }
		}

		-- link to Maratis
		links { "MCore", "MGui", "MEngine" }
	
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
 
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }  
