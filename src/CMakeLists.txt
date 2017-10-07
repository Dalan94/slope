set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SLOPE_MAJOR_VERSION 2)
set(SLOPE_MINOR_VERSION 5)
set(SLOPE_PATCH_VERSION 0)


set(slope_HDRS
   drawing.h
   figure.h
   global.h
   item.h
   scale.h
   slope.h
   view.h
   xyscale.h
   xyseries.h
   xyaxis.h
   legend.h
   sampler.h
)

if(SLOPE_USE_GTK MATCHES "TRUE")
   set(slope_HDRS
      ${slope_HDRS}
      view.h
      chart.h
   )
endif()
   
set(slope_SRCS
   drawing.c
   figure.c
   item.c
   scale.c
   xyscale.c
   xyseries.c
   xyaxis.c
   legend.c
   sampler.c
)

if(SLOPE_USE_GTK MATCHES "TRUE")
   set(slope_SRCS
      ${slope_SRCS}
      view.c
      chart.c
   )
endif()

configure_file(
   config.h.in
   ${CMAKE_BINARY_DIR}/config.h
)

add_library(slope STATIC ${slope_SRCS}  ${slope_HDRS})


TARGET_LINK_LIBRARIES(
	slope
	${CAIRO_LIBRARIES}
	${GLIB_LIBRARIES}
	${GOBJECT_LIBRARIES}
)
