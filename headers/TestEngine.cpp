//
//  TestEngine.cpp
//  
//
//  Created by Stef Tervelde on 10.09.23.
//

#include "TestEngine.hpp"
#include <filament/Engine.h>
void hii::TestEngine::testFunction(){
    printf("hi!");
    filament::Engine::create();
};
