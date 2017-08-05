find_program(REDIS_BINARY NAMES redis-server)
find_path(REDIS_INCLUDE_PATH NAMES Redis/redismodule.h)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(redis REQUIRED_VARS REDIS_BINARY REDIS_INCLUDE_PATH)

if(REDIS_FOUND)
    message(STATUS "Found Redis binary - ${REDIS_BINARY}, Redis Include dir - ${REDIS_INCLUDE_PATH}")
else(REDIS_FOUND)
    message(WARNING "Redis not found")
endif(REDIS_FOUND)
