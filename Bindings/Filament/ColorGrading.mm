//
//  ColorGrading.mm

//  Created by Stef Tervelde on 30.06.22.
//
#import "Bindings/Filament/ColorGrading.h"
#import <filament/ColorGrading.h>

/**
 * <code>ColorGrading</code> is used to transform (either to modify or correct) the colors of the
 * HDR buffer rendered by Filament. Color grading transforms are applied after lighting, and after any
 * lens effects (bloom for instance), and include tone mapping.
 *
 * <h1>Performance</h1>
 *
 * Creating a new ColorGrading object may be more expensive than other Filament objects as a
 * 3D LUT may need to be generated. The generation of a 3D LUT, if necessary, may happen on
 * the CPU.
 *
 * <h1>Ordering</h1>
 *
 * The various transforms held by ColorGrading are applied in the following order:
 * <ul>
 * <li>Exposure</li>
 * <li>Night adaptation</li>
 * <li>White balance</li>
 * <li>Channel mixer</li>
 * <li>Shadows/mid-tones/highlights</li>
 * <li>Slope/offset/power (CDL)</li>
 * <li>Contrast</li>
 * <li>Vibrance</li>
 * <li>Saturation</li>
 * <li>Curves</li>
 * <li>Tone mapping</li>
 * <li>Luminance scaling</li>
 * <li>Gamut mapping</li>
 * </ul>
 *
 * <h1>Defaults</h1>
 *
 * Here are the default color grading options:
 * <ul>
 * <li>Exposure: 0.0</li>
 * <li>Night adaptation: 0.0</li>
 * <li>White balance: temperature <code>0.0</code>, and tint <code>0.0</code></li>
 * <li>Channel mixer: red <code>{1,0,0}</code>, green <code>{0,1,0}</code>, blue <code>{0,0,1}</code></li>
 * <li>Shadows/mid-tones/highlights: shadows <code>{1,1,1,0}</code>, mid-tones <code>{1,1,1,0}</code>,
 * highlights <code>{1,1,1,0}</code>, ranges <code>{0,0.333,0.550,1}</code></li>
 * <li>Slope/offset/power: slope <code>1.0</code>, offset <code>0.0</code>, and power <code>1.0</code></li>
 * <li>Contrast: <code>1.0</code></li>
 * <li>Vibrance: <code>1.0</code></li>
 * <li>Saturation: <code>1.0</code></li>
 * <li>Curves: gamma <code>{1,1,1}</code>, midPoint <code>{1,1,1}</code>, and scale <code>{1,1,1}</code></li>
 * <li>Tone mapping: {@link ToneMapper.ACESLegacy}</li>
 * <li>Luminance scaling: false</li>
 * <li>Gamut mapping: false</li>
 * </ul>
 *
 * @see View
 * @see ToneMapper
 */
@implementation ColorGrading{
    filament::ColorGrading* nativeGrading;
}

- (id) init:(void *)grading{
    self->_grading = grading;
    self->nativeGrading = (filament::ColorGrading*)grading;
    return self;
}

@end
