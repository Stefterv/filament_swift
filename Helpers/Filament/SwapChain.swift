//
//  SwapChain.swift
//
//
//  Created by Stef Tervelde on 12.09.23.
//

import Bindings
extension SwapChain{
    public var nativeWindow: UnsafeMutableRawPointer{
        getNativeWindow()
    }
}
