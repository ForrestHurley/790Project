set(RANDOM_SOURCES
    xorshift.cxx
    halton.cxx
    sobol.cxx
    xoshiro256plus.c)

add_library(random_generation ${RANDOM_SOURCES})
target_include_directories(random_generation PUBLIC
    ${random_SOURCE_DIR}/include/)
