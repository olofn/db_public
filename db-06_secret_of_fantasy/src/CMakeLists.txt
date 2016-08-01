include_directories(. guichan dumb)

# Game
FILE(GLOB SrcMain "*.cpp")
FILE(GLOB SrcEntities "entities/*.cpp")
FILE(GLOB SrcItems "items/*.cpp")
FILE(GLOB SrcGui "gui/*.cpp")
LIST(APPEND SrcGame ${SrcMain} ${SrcEntities} ${SrcItems} ${SrcGui})

# Guichan
FILE(GLOB SrcGuichanMain "guichan/*.cpp")
FILE(GLOB SrcGuichanAllegro "guichan/allegro/*.cpp")
FILE(GLOB SrcGuichanWidgets "guichan/widgets/*.cpp")
LIST(APPEND SrcGuichan ${SrcGuichanMain} ${SrcGuichanAllegro} ${SrcGuichanWidgets})

# DUMB
FILE(GLOB SrcDumbAllegro "dumb/allegro/*.c")
FILE(GLOB SrcDumbCore "dumb/core/*.c")
FILE(GLOB SrcDumbHelpers "dumb/helpers/*.c")
FILE(GLOB SrcDumbIt "dumb/it/*.c")
LIST(APPEND SrcDumb ${SrcDumbAllegro} ${SrcDumbCore} ${SrcDumbHelpers} ${SrcDumbIt})

LIST(APPEND Src ${SrcGame} ${SrcGuichan} ${SrcDumb})

link_libraries(alleg-4.2.2)
add_executable(secret_of_fantasy ${Src})
set(EXECUTABLE_OUTPUT_PATH ..)
