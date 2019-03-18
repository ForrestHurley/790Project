set(MAIN_SOURCES
    coordinate.cxx
    mc_integration.cxx
    radial_distribution.cxx
    generate_points.cxx
    generate_random_points.cxx
    generate_sobol_points.cxx
    generate_halton_points.cxx
    generate_moldyn_points.cxx
    generate_grid_points.cxx
    KDTree.cxx
    main.cxx)

add_executable(main ${MAIN_SOURCES})
target_link_libraries(main random_generation)
target_include_directories(main PUBLIC ${main_SOURCE_DIR}/include/)
