project('ahi', 'cpp', version: '0.3')

version = meson.project_version()
conf = configuration_data()
conf.set('VERSION', '"@0@"'.format(version))
configure_file(
  output: 'config.h',
  configuration: conf
)

cmake = import('cmake')
opt_var = cmake.subproject_options()
opt_var.add_cmake_defines({'GLFW_BUILD_WAYLAND': true})
raylib = cmake.subproject('raylib', options: opt_var)
libraylib = raylib.dependency('raylib')

executable(
  'ahi',
  ['ahi.cpp', 'draw.cpp', 'event.cpp'],
  cpp_args: ['-std=c++23', '-Wall', '-Wextra', '-Werror', '-Wpedantic'],
  dependencies: [libraylib]
)
