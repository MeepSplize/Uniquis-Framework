cmake_minimum_required(VERSION 3.15)

file(GLOB SRC_FILES *.h)

target_sources(

	Wesche

	PRIVATE

	${SRC_FILES}
)