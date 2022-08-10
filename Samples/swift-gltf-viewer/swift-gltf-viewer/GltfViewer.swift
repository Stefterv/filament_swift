//
//  GltfViewer.swift

//  Created by Stef Tervelde on 29.06.22.
//

import SwiftUI
import Filament

@main
struct GltfViewer: App{
    @State var engine: Engine?
    
    var body: some SwiftUI.Scene{
        WindowGroup{
            FilaScene(){
                Spacer()
                    .frame(maxWidth: .infinity, maxHeight: .infinity)
            }
            .ignoresSafeArea()
        }
    }
}
