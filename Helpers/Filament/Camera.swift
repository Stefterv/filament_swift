//
//  Camera.swift
//
//  Created by Stef Tervelde on 30.06.22.
//

import Bindings
import simd

extension Camera{
    public func lookAt(_ at: simd_float3, _ center: simd_float3, _ up: simd_float3){
        func simd_float3_double3(_ vector: simd_float3) -> simd_double3{
            return simd_double3(x: Double(vector.x), y: Double(vector.y), z: Double(vector.z))
        }
        self.look(at: simd_float3_double3(at),simd_float3_double3(center) ,simd_float3_double3(up))
    }
    public var position: simd_double3{
        getPosition()
    }
    public var left: simd_double3{
        getLeftVector()
    }
    public var up: simd_double3{
        getUpVector()
    }
    public var forward: simd_double3{
        getForwardVector()
    }
    /**
     * Sets this camera's exposure directly. Calling this method will set the aperture
     * to 1.0, the shutter speed to 1.2 and the sensitivity will be computed to match
     * the requested exposure (for a desired exposure of 1.0, the sensitivity will be
     * set to 100 ISO).
     *
     * This method is useful when trying to match the lighting of other engines or tools.
     * Many engines/tools use unit-less light intensities, which can be matched by setting
     * the exposure manually. This can be typically achieved by setting the exposure to
     * 1.0.
     *
     * @see LightManager
     * @see #setExposure(float, float, float)
     */
    public func setExposure(_ exposure: Double){
        self.setExposure(1.0, 1.2, 100.0 * (1.0 / exposure))
    }
    public var aperture: Double{
        getAperture()
    }
    public var shutterSpeed: Double{
        getShutterSpeed()
    }
    public var focalLength: Double{
        getFocalLength()
    }
    public var focusDistance: Double{
        get{
            getFocusDistance()
        }
        set{
            setFocusDistance(newValue)
        }
    }
    public func setCustomProjection(_ projection: simd_float4x4){
        setCustomProjection(projection.toDouble(), 0, 9999)
    }
    public func setModelMatrix(_ viewMatrix: simd_float4x4){
        setModelMatrix(viewMatrix.toDouble())
    }
}
