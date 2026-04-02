

_cordic_module = custom_target('_cordicmodule',
    input: '_cordic.pyf',
    output: ['_cordicmodule.c'],
    command: [py, '-m', 'numpy.f2py', '@INPUT@', '--build-dir', '@OUTDIR@'],
)

py.extension_module('_cordic',
    [_cordic_module, '_cordic_helpers.c', fortranobject_c],
    include_directories: cordic_inc,
    c_args: np_compile_args,
    link_with: cordic_lib,
    dependencies: [py_dep, m_dep],
    install: true,
    subdir: 'cordic',
)

py.install_sources(
    '__init__.py',
    subdir: 'cordic',
)
