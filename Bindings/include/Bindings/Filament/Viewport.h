//
//  Viewport.h
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef Viewport_h
#define Viewport_h

@interface Viewport : NSObject
@property int left;
@property int bottom;
@property int width;
@property int height;

@end

#define FILAMENT_VIEWPORT(dstViewport) (filament::Viewport(dstViewport.left, dstViewport.bottom, dstViewport.width, dstViewport.height))

#endif /* Viewport_h */
