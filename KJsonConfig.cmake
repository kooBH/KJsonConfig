################################################################
#     CMake file for using KJsonConfig  as submodule           #
# 															   #
################################################################

list(APPEND SRC_Qt_MOC
	${CMAKE_CURRENT_LIST_DIR}/KJsonConfig.h
	${CMAKE_CURRENT_LIST_DIR}/ParamCheckBox.h
	${CMAKE_CURRENT_LIST_DIR}/ParamComboBox.h
	${CMAKE_CURRENT_LIST_DIR}/ParamLineEdit.h
	
)

list(APPEND SRC_Qt
	${CMAKE_CURRENT_LIST_DIR}/KJsonConfig.cpp
	${CMAKE_CURRENT_LIST_DIR}/ParamCheckBox.cpp
	${CMAKE_CURRENT_LIST_DIR}/ParamComboBox.cpp
	${CMAKE_CURRENT_LIST_DIR}/ParamLineEdit.cpp
)

list(APPEND SRC_Qt
)
	
list(APPEND INCL
	${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_CURRENT_LIST_DIR}/lib
)

