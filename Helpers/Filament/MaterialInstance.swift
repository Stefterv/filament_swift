//
//  MaterialInstance.swift
//
//  Created by Stef Tervelde on 30.06.22.
//
import Bindings

extension MaterialInstance{
    public func setParameter(_ name: String, _ boolean: Bool){
        setParameterBool(name, boolean)
    }
    public func setParameter(_ name: String, _ decimal: Float){
        setParameterFloat(name, decimal)
    }
    public func setParameter(_ name: String, _ integer: Int32){
        setParameterInt(name, integer)
    }
    public func setParameter(_ name: String, _ boolean1: Bool,_ boolean2: Bool){
        setParameterBool2(name, boolean1, boolean2)
    }
    public func setParameter(_ name: String, _ decimal: simd_float2){
        setParameterFloat2(name, decimal)
    }
    public func setParameter(_ name: String, _ integer: simd_int2){
        setParameterInt2(name, integer)
    }
    public func setParameter(_ name: String, _ boolean1: Bool, _ boolean2: Bool,_ boolean3: Bool){
        setParameterBool3(name, boolean1, boolean2, boolean3)
    }
    public func setParameter(_ name: String, _ decimal: simd_float3){
        setParameterFloat3(name, decimal)
    }
    public func setParameter(_ name: String, _ integer: simd_int3){
        setParameterInt3(name, integer)
    }
    public func setParameter(_ name: String, _ boolean1: Bool, _ boolean2: Bool,_ boolean3: Bool,_ boolean4: Bool){
        setParameterBool4(name, boolean1, boolean2, boolean3, boolean4)
    }
    public func setParameter(_ name: String, _ decimal: simd_float4){
        setParameterFloat4(name, decimal)
    }
    public func setParameter(_ name: String, _ integer: simd_int4){
        setParameterInt4(name, integer)
    }
    public func setParameter(_ name: String, _ matrix: simd_float3x3){
        setParameterMat3f(name, matrix)
    }
    public func setParameter(_ name: String, _ matrix: simd_float4x4){
        setParameterMat4f(name, matrix)
    }
    public func setParameter(_ name: String, _ matrix: CGAffineTransform){
        setParameterMat3f(name, simd_float3x3([
            simd_float3(x: Float(matrix.a), y: Float(matrix.b), z: 0),
            simd_float3(x: Float(matrix.c), y: Float(matrix.d), z: 0),
            simd_float3(x: Float(matrix.tx), y: Float(matrix.ty), z: 1)
        ]))
    }
    public func setParameter(_ name: String, _ texture: Texture, _ sampler: TextureSampler){
        setParameterTexture(name, texture, sampler)
    }
    public var name: String{
        getName()
    }
}
