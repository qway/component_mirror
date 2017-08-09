set(the_description "The UbiTrack Mirror Component for Tracking")
ut_add_component(MirrorComponent DEPS utcore utdataflow )


ut_component_include_directories("src/MirrorComponent" ${TINYXML_INCLUDE_DIR} ${LOG4CPP_INCLUDE_DIR} ${BOOSTBINDINGS_INCLUDE_DIR} ${LAPACK_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
ut_glob_component_sources(HEADERS "src/MirrorComponent/*.h" SOURCES "src/MirrorComponent/*.cpp")
ut_create_single_component()
ut_install_utql_patterns()

