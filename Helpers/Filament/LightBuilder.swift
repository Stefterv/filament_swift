//
//  LightBuilder.swift
//
//  Created by Stef Tervelde on 30.06.22.
//

import Bindings

extension LightManager.Builder{
    /**
    * Sets the initial intensity of a light in watts.
    *
    *<pre>
    *  Lightbulb type  | Efficiency
    * -----------------+------------
    *     Incandescent |  2.2%
    *         Halogen  |  7.0%
    *             LED  |  8.7%
    *     Fluorescent  | 10.7%
    *</pre>
    *
    *
    * This call is equivalent to:
    *<pre>
    * Builder.intensity(efficiency * 683 * watts);
    *</pre>
    *
    * This method overrides any prior calls to #intensity or #intensityCandela.
    *
    * @param watts         Energy consumed by a lightbulb. It is related to the energy produced
    *                      and ultimately the brightness by the efficiency parameter.
    *                      This value is often available on the packaging of commercial
    *                      lightbulbs.
    *
    * @param efficiency    Efficiency in percent. This depends on the type of lightbulb used.
    *
    * @return This Builder, for chaining calls.
    */
    public func intensity(_ watts: Double, _ efficiency: Double){
        intensity(efficiency * 683.0 * watts)
    }
}
