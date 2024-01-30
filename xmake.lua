add_rules("mode.debug", "mode.release")

target("zemu")
    set_languages("cxx17")
    set_kind("binary")
    add_files("src/**.cpp")
    add_includedirs("include")
    add_defines("CONFIG_ISA64")
