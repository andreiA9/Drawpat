#add_library(EditorLib_static
#    # add the CPP FILES
#    ${EditorModule_SRC}
#    ${Utils_SRC}
##    ${Misc_SRC}
#    # add the RESOURCES
#    ${APP_RESOURCES}
#    )

## just these LIBRARIES were being needed for EditorLib_static
## FROM set(Qt5_COMPONENTS Core Widgets Sql REQUIRED)
#target_link_libraries(EditorLib_static
#    Qt5::Core           # -> Core
#    Qt5::Sql            # -> Sql
#    )
