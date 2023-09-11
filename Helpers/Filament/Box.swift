//
//  Box.swift
//
//  Created by Stef Tervelde on 30.06.22.
//
import Bindings

extension Box{
    /**
     * Whether the box is empty, i.e.: it's volume is null.
     * @return true if the volume of the box is null
     */
    func isEmpty() -> Bool {
        return halfExtent.sum() == 0;
    }

    /**
     * Computes the lowest coordinates corner of the box.
     * @return center - halfExtent
     */
    func getMin() -> simd_float3 {
        return center - halfExtent;
    }

    /**
     * Computes the largest coordinates corner of the box.
     * @return center + halfExtent
     */
    func getMax() -> simd_float3 {
        return center + halfExtent;
    }

    /**
     * Initializes the 3D box from its min / max coordinates on each axis
     * @param min lowest coordinates corner of the box
     * @param max largest coordinates corner of the box
     * @return This bounding box
     */
    init(min: simd_float3, max: simd_float3){
        self.init()
        center     = (max + min) * 0.5
        halfExtent = (max - min) * 0.5
    }

    /**
     * Computes the bounding box of the union of two boxes
     * @param box The box to be combined with
     * @return The bounding box of the union of *this and box
     */
    func unionSelf(box: Box) -> Box {
        return Box(min: min(getMin(), box.getMin()), max: max(getMax(), box.getMax()));
    }

    /**
     * Translates the box *to* a given center position
     * @param tr position to translate the box to
     * @return A box centered in \p tr with the same extent than *this
     */
    func translateTo(tr: simd_float3) -> Box {
        var box = Box()
        box.halfExtent = halfExtent
        box.center = tr
        return box
    }

    /**
     * Computes the smallest bounding sphere of the box.
     * @return The smallest sphere defined by its center (.xyz) and radius (.w) that contains *this
     */
    func getBoundingSphere() -> simd_float4 {
        return simd_float4(center, length(halfExtent));
    }

    /**
     * Transform a Box by a linear transform and a translation.
     *
     * @param m a 3x3 matrix, the linear transform
     * @param t a float3, the translation
     * @param box the box to transform
     * @return the bounding box of the transformed box
     */
    static func transform(m: simd_float3x3, t: simd_float3, box: Box) -> Box {
        var box = Box();
        box.center =  m * box.center + t
        box.halfExtent = simd_float3x3(columns: (simd_abs(m.columns.0), simd_abs(m.columns.1), simd_abs(m.columns.2))) * box.halfExtent
        return box
    }
}
extension Aabb{
#warning("TODO: Implement aabb methods")
}
