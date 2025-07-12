project('ahi', 'cpp',
  version: '0.3',
  default_options: ['werror=true', 'warning_level=3']
)

version = meson.project_version()
conf = configuration_data()
conf.set('VERSION', '"@0@"'.format(version))
configure_file(
  output: 'config.h',
  configuration: conf
)

raylib_dep = subproject('raylib').get_variable('raylib_dep')

source = files(
  'src/ahi.cpp',
  'src/draw.cpp',
  'src/event.cpp',
)

executable(
  'ahi',
  source,
  cpp_args: '-std=c++23',
  dependencies: raylib_dep
)
