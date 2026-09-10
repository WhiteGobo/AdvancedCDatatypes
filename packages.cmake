include(FetchContent)

FetchContent_Declare(
        cwalk
        GIT_REPOSITORY https://github.com/likle/cwalk.git
	GIT_TAG v1.2.9
	FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(cwalk)
