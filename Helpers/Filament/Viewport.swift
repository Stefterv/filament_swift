//
//  Viewport.swift

//  Created by Stef Tervelde on 30.06.22.
//
import Bindings

extension Viewport{
    public init(left: Int32, bottom: Int32, width: Int32, height: Int32){
        self.init()
        self.left = left
        self.bottom = bottom
        self.width = width
        self.height = height
    }
}
