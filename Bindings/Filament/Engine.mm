//
//  Engine.mm
//  
//
//  Created by Stef Tervelde on 29.06.22.
//
#import "Bindings/Filament/Engine.h"
#import <filament/Engine.h>
#import <utils/Entity.h>
#import "Bindings/Filament/RenderableManager.h"

@implementation Engine{
    filament::Engine* nativeEngine;
}

+ (instancetype) create{
    auto nativeEngine = filament::Engine::create();
    return [[Engine alloc] init:nativeEngine];;
}
+ (instancetype) create: (Backend) backend{
    auto nativeEngine = filament::Engine::create( (filament::Engine::Backend) backend);
    return [[Engine alloc] init:nativeEngine];;
}

- (id) init: (void *)engine{
    self->_engine = engine;
    self->nativeEngine = (filament::Engine*) engine;
    return self;
}

+ (void) destroy: (Engine*)engine{
    filament::Engine::destroy(engine->nativeEngine);
}

- (void) dealloc{
    filament::Engine::destroy(nativeEngine);
}

- (Backend) getBackend{
    return (Backend) nativeEngine->getBackend();
}

- (SwapChain*) createSwapChain: (CALayer*)layer{
    auto swapchain = nativeEngine->createSwapChain( (__bridge void*) layer);
    return [[SwapChain alloc] init:swapchain];
}

- (SwapChain*) createSwapChain:(uint32_t)width :(uint32_t)height{
    auto swapchain = nativeEngine->createSwapChain(width, height);
    return [[SwapChain alloc] init:swapchain];
}

- (void) destroySwapChain:(SwapChain *)swapchain{
    nativeEngine->destroy( (filament::SwapChain*) swapchain.swapchain);
}

- (Renderer*) createRenderer{
    auto renderer = nativeEngine->createRenderer();
    return [[Renderer alloc] init: renderer];
}

- (void) destroyRenderer:(Renderer *)renderer{
    nativeEngine->destroy( (filament::Renderer*) renderer.renderer);
}


- (Camera*) createCamera:(Entity)entity{
    auto camera = nativeEngine->createCamera(utils::Entity::import(entity));
    return [[Camera alloc] init:camera];
}

- (Camera*) getCameraComponent:(Entity)entity{
    auto camera = nativeEngine->getCameraComponent(utils::Entity::import(entity));
    if (camera){
        return [[Camera alloc] init:camera];
    }
    return nil;
}

- (void) destroyCameraComponent:(Entity)entity{
    nativeEngine->destroyCameraComponent(utils::Entity::import(entity));
}

- (Scene*) createScene{
    auto scene = nativeEngine->createScene();
    return [[Scene alloc] init: scene];
}

- (void) destroyScene:(Scene *)scene{
    nativeEngine->destroy( (filament::Scene*) scene.scene);
}

- (View*) createView{
    auto view = nativeEngine->createView();
    return [[View alloc] init: view];
}

- (void) destroyView:(View *)view{
    nativeEngine->destroy( (filament::View*) view.view);
}

- (void) destroyEntity:(Entity)entity{
    nativeEngine->destroy(utils::Entity::import(entity));
}

- (EntityManager*) getEntityManager{
    auto manager = &nativeEngine->getEntityManager();
    return [[EntityManager alloc] init: manager];
}

- (TransformManager*) getTransformManager{
    auto manager = &nativeEngine->getTransformManager();
    return [[TransformManager alloc] init: manager];
}

- (LightManager*) getLightManager{
    auto manager = &nativeEngine->getLightManager();
    return [[LightManager alloc] init: manager];
}

- (RenderableManager*) getRenderableManager{
    auto manager = &nativeEngine->getRenderableManager();
    return [[RenderableManager alloc] init: manager];
}

@end
