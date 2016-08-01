#!/usr/bin/env bash

#libpng
pushd extsrc/loadpng
make
popd

#TmxParser dependencies
pushd extsrc/TmxParser

#base 64
pushd base64
g++ -c *.cpp
ar cr libbase64.a *.o
popd

#tinyxml
pushd tinyxml
g++ -c *.cpp
ar cr libtinyxml.a *.o
popd

#zlib
pushd zlib
gcc -c *.c
ar cr libzlib.a
popd

#build TmxParser
g++ -DTIXML_USE_STL -Ibase64 -Itinyxml -Izlib -Lbase64 -lbase64 -Ltinyxml -ltinyxml -Lzlib -lzlib -c *.cpp
ar cr libtmxparser.a *.o

popd

pushd src

#math3d
pushd math3d
g++ -c *.cpp
ar cr libmath3d.a *.o
popd

g++ -I../extsrc/math3d -I../extsrc/dumb -I../extsrc/TmxParser -I../extsrc/loadpng/ -c *.cpp

g++ -o db-tins12 -Lmath3d -L../extsrc/TmxParser -L../extsrc/TmxParser/base64 -L../extsrc/loadpng -L. Util.o Music.o Resource.o Font.o Animation.o Blending.o Input.o Screen.o Portal.o Intro.o End.o Outro.o Title.o SplashScreen.o Sound.o Time.o ScreenManager.o Game.o Tile.o EnemyDragon.o Shooter.o EnemyBoss.o Savepoint.o Background.o PowerUpScreen.o Powerup.o MovableBox.o MusicPlayer.o Hero.o EntityFactory.o RoomLoader.o Shot.o GameState.o Camera.o Layer.o Entity.o Room.o World.o TINS12Game.o Main.o -lldpng -lpng -lmath3d -ldumb -laldmb -ltmxparser -ltinyxml -lbase64 `/usr/bin/allegro-config --libs`

popd

mv src/db-tins12 .
