include(CTest)

add_library(ACDGetCurrentTimezone GetCurrentTimezone.c)

add_subdirectory(decimal)
add_subdirectory(time)
