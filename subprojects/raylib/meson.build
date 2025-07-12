project('raylib', 'c', version: '5.5', default_options: ['c_std=c99', 'warning_level=0'])

wl = import('unstable-wayland')

incdir = include_directories('src/external/glfw/include')

add_project_arguments('-DPLATFORM_DESKTOP_GLFW', language : 'c')
add_project_arguments('-D_GLFW_X11', language : 'c')
add_project_arguments('-D_GLFW_WAYLAND', language : 'c')

protocols = wl.scan_xml(
  'src/external/glfw/deps/wayland/fractional-scale-v1.xml',
  'src/external/glfw/deps/wayland/idle-inhibit-unstable-v1.xml',
  'src/external/glfw/deps/wayland/pointer-constraints-unstable-v1.xml',
  'src/external/glfw/deps/wayland/relative-pointer-unstable-v1.xml',
  'src/external/glfw/deps/wayland/viewporter.xml',
  'src/external/glfw/deps/wayland/wayland.xml',
  'src/external/glfw/deps/wayland/xdg-activation-v1.xml',
  'src/external/glfw/deps/wayland/xdg-decoration-unstable-v1.xml',
  'src/external/glfw/deps/wayland/xdg-shell.xml',
)

raylib = static_library('raylib',
  'src/raudio.c',
  'src/rcore.c',
  'src/rglfw.c',
  'src/rmodels.c',
  'src/rshapes.c',
  'src/rtext.c',
  'src/rtextures.c',
  'src/utils.c',
  protocols, 
  include_directories : incdir
)

raylib_dep = declare_dependency(include_directories: 'src', link_with: raylib)
