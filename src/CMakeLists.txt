find_library(MATH_LIBRARY m REQUIRED)
set(includepath "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(AdvancedCDatatypes
	decimal.c
	duration.c
	datetime.c
	date.c
	time.c
	number.c
	quotient.c
	"${includepath}/AdvancedCDatatypesTime.h"
	"${includepath}/AdvancedCDatatypesDecimal.h"
)

target_include_directories(AdvancedCDatatypes PUBLIC
	"${includepath}"
)

target_link_libraries(AdvancedCDatatypes PRIVATE
	${MATH_LIBRARY}
)
