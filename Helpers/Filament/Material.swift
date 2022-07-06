//
//  Material.swift
//  swift-gltf-viewer
//
//  Created by Stef Tervelde on 30.06.22.
//
import FilamentBindings

extension Material{
    public func setDefaultParameter(_ name: String, _ boolean: Bool){
        setDefaultParameterBool(name, boolean)
    }
    public func setDefaultParameter(_ name: String, _ decimal: Float){
        setDefaultParameterFloat(name, decimal)
    }
    public func setDefaultParameter(_ name: String, _ integer: Int32){
        setDefaultParameterInt(name, integer)
    }
    public func setDefaultParameter(_ name: String, _ boolean1: Bool,_ boolean2: Bool){
        setDefaultParameterBool2(name, boolean1, boolean2)
    }
    public func setDefaultParameter(_ name: String, _ decimal: simd_float2){
        setDefaultParameterFloat2(name, decimal)
    }
    public func setDefaultParameter(_ name: String, _ integer: simd_int2){
        setDefaultParameterInt2(name, integer)
    }
    public func setDefaultParameter(_ name: String, _ boolean1: Bool, _ boolean2: Bool,_ boolean3: Bool){
        setDefaultParameterBool3(name, boolean1, boolean2, boolean3)
    }
    public func setDefaultParameter(_ name: String, _ decimal: simd_float3){
        setDefaultParameterFloat3(name, decimal)
    }
    public func setDefaultParameter(_ name: String, _ integer: simd_int3){
        setDefaultParameterInt3(name, integer)
    }
    public func setDefaultParameter(_ name: String, _ boolean1: Bool, _ boolean2: Bool,_ boolean3: Bool,_ boolean4: Bool){
        setDefaultParameterBool4(name, boolean1, boolean2, boolean3, boolean4)
    }
    public func setDefaultParameter(_ name: String, _ decimal: simd_float4){
        setDefaultParameterFloat4(name, decimal)
    }
    public func setDefaultParameter(_ name: String, _ integer: simd_int4){
        setDefaultParameterInt4(name, integer)
    }
}
