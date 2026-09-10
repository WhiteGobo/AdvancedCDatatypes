find_library(MATH_LIBRARY m REQUIRED)
set(includepath "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(AdvancedCDatatype
	decimal.c
	duration.c
	datetime.c
	date.c
	time.c
	number.c
	quotient.c
	"${includepath}/AdvancedCDatatypeTime.h"
	"${includepath}/AdvancedCDatatypeDecimal.h"
)

target_include_directories(AdvancedCDatatype PUBLIC
	"${includepath}"
)

target_link_libraries(AdvancedCDatatype PRIVATE
	${MATH_LIBRARY}
)
