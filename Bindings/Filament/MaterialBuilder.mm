//
//  MaterialBuilder.mm
//
//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/MaterialBuilder.h"
#import <filament/Material.h>
#import <filament/Engine.h>

@implementation MaterialBuilder{
    filament::Material::Builder* nativeBuilder;
}

- (id)init{
    auto builder = new filament::Material::Builder();
    self->nativeBuilder = builder;
    self->_builder = builder;
    return self;
}
- (nonnull instancetype)constantFloat:(nonnull NSString *)name :(float)value {
    nativeBuilder->constant(name.UTF8String, value);
    return self;
}

- (nonnull instancetype)constantInt:(nonnull NSString *)name :(int)value {
    nativeBuilder->constant(name.UTF8String, value);
    return self;
}

- (nonnull instancetype)constantBool:(nonnull NSString *)name :(bool)value {
    nativeBuilder->constant(name.UTF8String, value);
    return self;
}
- (instancetype)payload:(NSData *)buffer{
    nativeBuilder->package(buffer.bytes, buffer.length);
    return self;
}
- (Material*)build:(Engine *)engine{
    auto nEngine = (filament::Engine*) engine.engine;
    auto material = nativeBuilder->build(*nEngine);
    return [[Material alloc] init:material];
}
@end
