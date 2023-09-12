//
//  Renderer.swift
//
//  Created by Stef Tervelde on 30.06.22.
//
import Bindings

extension RenderTarget{
    public var supportedColorAttachmentsCount: UInt8{
        getSupportedColorAttachmentsCount()
    }
}
