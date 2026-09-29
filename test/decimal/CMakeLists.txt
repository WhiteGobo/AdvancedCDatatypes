set(testsuffix "AdvancedCDatatypes::Decimal::")


foreach(x RANGE 15)
	set(exename "test_Datatype_Decimal_add${x}")
	add_executable(${exename}
		"test${x}.c"
	)
	target_link_libraries(${exename}
		AdvancedCDatatypes
	)

	add_test(NAME "${testsuffix}add${x}" COMMAND ${exename})
endforeach()


add_executable(test_decimal_reprint
	test_decimal_reprint.c
)
target_link_libraries(test_decimal_reprint
	AdvancedCDatatypes
	ACDGetCurrentTimezone
)
set(index 0)
foreach(inputstring IN ITEMS
		".5"
		"-2.5"
		"123.567"
		"+3"
	)
	add_test(NAME "${testsuffix}decimal_reprint${index}"
		COMMAND test_decimal_reprint
		"${inputstring}"
	)
	math(EXPR index "${index}+1")
endforeach()
