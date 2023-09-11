//
//  Viewport.h

//  Created by Stef Tervelde on 30.06.22.
//
#import <Foundation/Foundation.h>

#ifndef Viewport_h
#define Viewport_h

typedef struct{
    int left;
    int bottom;
    int width;
    int height;
} Viewport;

//#define FILAMENT_VIEWPORT(dstViewport) (filament::Viewport(dstViewport.left, dstViewport.bottom, dstViewport.width, dstViewport.height))

#endif /* Viewport_h */
