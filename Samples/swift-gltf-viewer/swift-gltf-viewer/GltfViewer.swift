//
//  GltfViewer.swift

//  Created by Stef Tervelde on 29.06.22.
//

import SwiftUI

@main
struct GltfViewer: App{
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
