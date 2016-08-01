CMAKE_MINIMUM_REQUIRED(VERSION 2.4.6)

# Path to local modules

PROJECT(db-tins08)

SET(CMAKE_MODULE_PATH ${db-tins08_SOURCE_DIR}/CMake/Modules)

SET(VERSION 1.0)

INCLUDE_DIRECTORIES(${db-tins08_SOURCE_DIR}/src/ 
                    ${db-tins08_SOURCE_DIR}/src/dumb/
		    ${db-tins08_SOURCE_DIR}/src/guichan/)

ADD_DEFINITIONS("-DALLEGRO_USE_CONSOLE")

# Main source
FILE(GLOB db-tins08_src RELATIVE ${db-tins08_SOURCE_DIR} 
	src/*.hpp 
	src/*.cpp)
SOURCE_GROUP(src FILES ${db-tins08_src})
FILE(GLOB db-tins08_src_entities RELATIVE ${db-tins08_SOURCE_DIR} 
	src/entities/*.hpp 
	src/entities/*.cpp)
SOURCE_GROUP(src/entities FILES ${db-tins08_src_entities})
FILE(GLOB db-tins08_src_gui RELATIVE ${db-tins08_SOURCE_DIR} 
	src/gui/*.hpp 
	src/gui/*.cpp)
SOURCE_GROUP(src/gui FILES ${db-tins08_src_gui})

# Guichan source
FILE(GLOB db-tins08_src_guichan RELATIVE ${db-tins08_SOURCE_DIR} 
	src/guichan/*.hpp 
	src/guichan/*.cpp)
SOURCE_GROUP(src/guichan FILES ${db-tins08_src_guichan})
FILE(GLOB db-tins08_src_guichan_allegro RELATIVE ${db-tins08_SOURCE_DIR} 
	src/guichan/allegro/*.hpp 	src/guichan/allegro/*.cpp)
SOURCE_GROUP(src/guichan/allegro FILES ${db-tins08_src_guichan_allegro})
FILE(GLOB db-tins08_src_guichan_widgets RELATIVE ${db-tins08_SOURCE_DIR} 
	src/guichan/widgets/*.hpp 
	src/guichan/widgets/*.cpp)
SOURCE_GROUP(src/guichan/widgets FILES ${db-tins08_src_guichan_widgets})
   
# Dumb source
FILE(GLOB db-tins08_src_dumb RELATIVE ${db-tins08_SOURCE_DIR} 
	src/dumb/*.h 
	src/dumb/*.c)
SOURCE_GROUP(src/dumb FILES ${db-tins08_src_dumb})
FILE(GLOB db-tins08_src_dumb_allegro RELATIVE ${db-tins08_SOURCE_DIR} 
	src/dumb/allegro/*.h 
	src/dumb/allegro/*.c)
SOURCE_GROUP(src/dumb/allegro FILES ${db-tins08_src_dumb_allegro})
FILE(GLOB db-tins08_src_dumb_core RELATIVE ${db-tins08_SOURCE_DIR} 
	src/dumb/core/*.h 
	src/dumb/core/*.c)
SOURCE_GROUP(src/dumb/core FILES ${db-tins08_src_dumb_core})
FILE(GLOB db-tins08_src_dumb_helpers RELATIVE ${db-tins08_SOURCE_DIR} 
	src/dumb/helpers/*.h 
	src/dumb/helpers/*.inc
	src/dumb/helpers/*.c)
SOURCE_GROUP(src/dumb/helpers FILES ${db-tins08_src_dumb_helpers})
FILE(GLOB db-tins08_src_dumb_internal RELATIVE ${db-tins08_SOURCE_DIR} 
	src/dumb/internal/*.h)
SOURCE_GROUP(src/dumb/internal FILES ${db-tins08_src_dumb_internal})
FILE(GLOB db-tins08_src_dumb_it RELATIVE ${db-tins08_SOURCE_DIR} 
	src/dumb/it/*.c)
SOURCE_GROUP(src/dumb/it FILES ${db-tins08_src_dumb_it})

SET(ALLEGRO_CONFIG "allegro-config" CACHE STRING "Path to allegro-config script")

FIND_PACKAGE(Allegro)
INCLUDE_DIRECTORIES(${ALLEGRO_INCLUDE_DIR})
IF(WIN32)
  LINK_LIBRARIES(${ALLEGRO_LIBRARIES})
ELSE(WIN32)
  LINK_LIBRARIES(`${ALLEGRO_CONFIG} --libs`)
ENDIF(WIN32)          
ADD_EXECUTABLE(db-tins08
               ${db-tins08_src}
               ${db-tins08_src_entities}
               ${db-tins08_src_gui}
               ${db-tins08_src_guichan}
               ${db-tins08_src_guichan_allegro}
               ${db-tins08_src_guichan_widgets}
               ${db-tins08_src_dumb}
               ${db-tins08_src_dumb_allegro}
               ${db-tins08_src_dumb_core}
	       ${db-tins08_src_dumb_helpers}
               ${db-tins08_src_dumb_internal}
               ${db-tins08_src_dumb_it})
               
INSTALL(TARGETS db-tins08 RUNTIME DESTINATION ${db-tins08_SOURCE_DIR})
