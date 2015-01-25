set (Lamps_SRCS
	ControlPanel.cpp
	Experiment.cpp
	Lamp.cpp
	Lamps.cpp
	main.cpp
)

set (Lamps_HDRS
	ControlPanel.h
	Experiment.h
	Lamp.h
	Lamps.h
)

qt5_wrap_cpp (Lamps_SRCS ${Lamps_HDRS})

add_executable (Lamps ${Lamps_SRCS})
target_link_libraries (Lamps ${Qt5Widgets_LIBRARIES})
