# ===========================================================================
# Build CORDIC C library as a static archive
# ===========================================================================

cordic_sources = files(
    'cordic.c',
)

cordic_inc = include_directories('.')

cordic_lib = static_library('cordic',
    cordic_sources,
    include_directories: cordic_inc,
    dependencies: m_dep,
)
