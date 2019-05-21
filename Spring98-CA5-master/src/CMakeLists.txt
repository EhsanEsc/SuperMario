cmake_minimum_required(VERSION 3.13)
project(src)

set(CMAKE_CXX_STANDARD 11)

add_executable(src main.cpp AssetsAddresses.h Game.cpp Game.h Mario.cpp Mario.h Block.cpp Block.h rsdl.cpp rsdl.hpp Object.h ExactRectangle.cpp ExactRectangle.h Object.cpp utility.cpp utility.h Brick.cpp Brick.h AnimationIndexHandler.cpp AnimationIndexHandler.h Enemy.cpp Enemy.h Coin.cpp Coin.h Mushroom.cpp Mushroom.h AutomaticMovingObject.cpp AutomaticMovingObject.h Collision.cpp Collision.h FlagBlock.cpp FlagBlock.h PipeBlock.cpp PipeBlock.h MapReader.cpp MapReader.h)