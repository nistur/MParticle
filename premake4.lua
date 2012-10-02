-- Particle system project
solution "MParticle"
	configurations { "Debug", "Release" }
	language "C++"
	
	-- make sure we can search and link properly
	libdirs { os.getenv("MSDKDIR") .. "/SDK/MCore/Libs",
		  os.getenv("MSDKDIR") .. "/SDK/MEngine/Libs",
		  "." }
	includedirs { os.getenv("MSDKDIR") .. "/SDK/MCore/Includes",
		      os.getenv("MSDKDIR") .. "/SDK/MEngine/Includes",
		      os.getenv("MSDKDIR") .. "/SDK/MIngEd/Includes",
		      "src/common/" }

	defines { "MPLUGIN_DYNAMIC" }
	targetprefix ""
	
	-- OS defines
	if os.is("windows") then
		defines { "WIN32" }
	end
		
	project "MParticle"
		kind "SharedLib"
		language "C++"

		-- include all the files, including Maratis SDK ones
		files {
			"src/plugin/**.cpp",
			"src/plugin/**.h",
			"**.md",
			os.getenv("MSDKDIR") .. "SDK/**.h"
		}
		includedirs { "src/plugin" }

		-- split the files up a bit nicer inside Visual Studio
		vpaths { 
			["MCore/*"] = os.getenv("MSDKDIR") .. "/SDK/MCore/Includes/**.h",
			["MEngine/*"] = os.getenv("MSDKDIR") .. "/SDK/MEngine/Includes/**.h",
			["MIngEd/*"] = os.getenv("MSDKDIR") .. "/SDK/MIngEd/Includes/**.h",
			["Plugin/*"] = { "**.h", "**.cpp" },
			["Doc/*"] = { "**.md" }
		}

		prebuildcommands  ("Mnpk src/plugin/MParticle.npk src/plugin/data")
		prebuildcommands  ("MEmbedder src/plugin/MParticle.npk src/plugin/MParticle_npk.h MParticle_npk")
		postbuildcommands ("MPlugin install MParticle.so")

		-- link to Maratis
		links { "MCore", "MEngine" }
	
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
 
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }  
		
	project "MParticleEditor"
		kind "SharedLib"
		language "C++"

		-- include all the files, including Maratis SDK ones
		files {
			"src/editor/**.cpp",
			"src/editor/**.h",
			"**.md",
			os.getenv("MSDKDIR") .. "SDK/**.h"
		}
		includedirs { "src/editor" }

		-- split the files up a bit nicer inside Visual Studio
		vpaths { 
			["MCore/*"] = os.getenv("MSDKDIR") .. "/SDK/MCore/Includes/**.h",
			["MEngine/*"] = os.getenv("MSDKDIR") .. "/SDK/MEngine/Includes/**.h",
			["MIngEd/*"] = os.getenv("MSDKDIR") .. "/SDK/MIngEd/Includes/**.h",
			["Editor/*"] = { "src/editor/**.h", "src/editor/**.h" },
			["Data/*"] = { "src/editor/data/**.lua" },
			["Doc/*"] = { "**.md" }
		}

		prebuildcommands  ("Mnpk src/editor/MParticleEditor.npk src/editor/data")
		prebuildcommands  ("MEmbedder src/editor/MParticleEditor.npk src/editor/MParticleEditor_npk.h MParticleEditor_npk")
		postbuildcommands ("MPlugin install-sys MParticleEditor.so")

		-- link to Maratis
		links { "MCore", "MEngine" }
	
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
 
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }  

		
