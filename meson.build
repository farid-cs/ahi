project('ahi', 'cpp',
  version: '0.5',
  default_options: ['werror=true', 'warning_level=3']
)

version = meson.project_version()
conf = configuration_data()
conf.set('VERSION', '"@0@"'.format(version))
configure_file(
  output: 'config.h',
  configuration: conf
)

sdl3_dep = subproject('sdl3', default_options: ['default_library=static', 'warning_level=0']).get_variable('sdl3_dep')
sdl3_ttf_dep = subproject('sdl3_ttf', default_options: ['default_library=static', 'warning_level=0']).get_variable('sdl3_ttf_dep')

source = files(
  'src/ahi.cpp',
  'src/draw.cpp',
  'src/event.cpp',
)

executable(
  'ahi',
  source,
  cpp_args: '-std=c++23',
  dependencies: [sdl3_dep, sdl3_ttf_dep]
)
