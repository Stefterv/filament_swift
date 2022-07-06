//
//  Viewport.swift
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
import FilamentBindings

extension Viewport{
    public convenience init(left: Int32, bottom: Int32, width: Int32, height: Int32){
        self.init()
        self.left = left
        self.bottom = bottom
        self.width = width
        self.height = height
    }
}
