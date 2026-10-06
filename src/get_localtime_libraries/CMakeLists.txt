add_library(ACDGetCurrentTimezone
	TestGetCurrentTimezone.c
)

target_include_directories(ACDGetCurrentTimezone PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../include/"
)

add_library(GetCurrentTimezonePosixA
	GetCurrentTimezonePosixA.c
)

target_include_directories(GetCurrentTimezonePosixA PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../include/"
)
