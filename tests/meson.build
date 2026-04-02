# ===========================================================================
# CORDIC test suite
# ===========================================================================

test_cordic = executable('test_cordic',
    'test_cordic.c',
    include_directories: cordic_inc,
    link_with: cordic_lib,
    dependencies: m_dep,
)

test('cordic_tests', test_cordic)
