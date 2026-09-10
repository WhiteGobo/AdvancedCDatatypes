set(testsuffix "AdvancedCDatatype::Time::")


foreach(x RANGE 33)
	set(exename "test_Datatype_Time${x}")
	add_executable(${exename}
		"test${x}.c"
	)
	target_link_libraries(${exename}
		AdvancedCDatatype
		ACDGetCurrentTimezone
	)

	add_test(NAME "${testsuffix}test${x}" COMMAND ${exename})
endforeach()

add_executable(test_Datatype_Duration_reprint
	test_duration_reprint.c
)
target_link_libraries(test_Datatype_Duration_reprint
	AdvancedCDatatype
	ACDGetCurrentTimezone
)
set(index 0)
foreach(inputstring IN ITEMS
		"PT0S"
		"P0M"
		"P1Y1M1DT1H1M1.1S"
		"-P1Y1M1DT1H1M1.1S"
		"-PT5H"
	)
	add_test(NAME "${testsuffix}duration_reprint${index}"
		COMMAND test_Datatype_Duration_reprint
		"${inputstring}"
	)
	math(EXPR index "${index}+1")
endforeach()


add_executable(test_Datatype_DateTime_reprint
	test_datetime_reprint.c
)
target_link_libraries(test_Datatype_DateTime_reprint
	AdvancedCDatatype
	ACDGetCurrentTimezone
)
set(index 6)
foreach(inputstring IN ITEMS
		"2000-12-13T00:11:11.3"
		"2000-12-13T00:11:11.3Z"
		"-2000-12-13T00:11:11.3"
		"-2000-12-13T00:11:11.3+5:00"
		"-2000-12-13T00:11:11.3-5:00"
	)
	add_test(NAME "${testsuffix}datetime_reprint${index}"
		COMMAND test_Datatype_DateTime_reprint
		"${inputstring}"
	)
	math(EXPR index "${index}+1")
endforeach()

add_executable(test_Datatype_Date_reprint
	test_date_reprint.c
)
target_link_libraries(test_Datatype_Date_reprint
	AdvancedCDatatype
	ACDGetCurrentTimezone
)
set(index 0)
foreach(inputstring IN ITEMS
		"2000-12-13"
		"-2000-12-13"
		"1111-3-4Z"
		"-3-04-13-6:00"
	)
	add_test(NAME "${testsuffix}date_reprint${index}"
		COMMAND test_Datatype_Date_reprint
		"${inputstring}"
	)
	math(EXPR index "${index}+1")
endforeach()

add_executable(test_Datatype_Time_reprint
	test_time_reprint.c
)
target_link_libraries(test_Datatype_Time_reprint
	AdvancedCDatatype
	ACDGetCurrentTimezone
)
set(index 0)
foreach(inputstring IN ITEMS
		"00:11:11.3"
		"1:2:3Z"
		"23:59:59+5:00"
	)
	add_test(NAME "${testsuffix}time_reprint${index}"
		COMMAND test_Datatype_Time_reprint
		"${inputstring}"
	)
	math(EXPR index "${index}+1")
endforeach()
