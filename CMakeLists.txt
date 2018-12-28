cmake_minimum_required(VERSION 3.8.2)
project(ex3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ex3 Main.cpp LexParser.cpp LexParser.h OpenDataServer.cpp OpenDataServer.h Command.h ShuntingYard.cpp
        ShuntingYard.h Expression.h Condition.h Connect.cpp Connect.h Print.cpp Print.h Sleep.cpp Sleep.h Var.cpp Var.h
        Bind.cpp Bind.h Equal.cpp Equal.h While.cpp While.h If.cpp If.h DataBase.cpp DataBase.h ConditionParser.cpp
        ConditionParser.h DoubleFactory.cpp DoubleFactory.h Exit.cpp Exit.h)