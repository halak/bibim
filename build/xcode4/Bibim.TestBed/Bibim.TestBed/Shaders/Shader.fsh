//
//  Shader.fsh
//  Bibim.TestBed
//
//  Created by Halak on 13. 3. 27..
//  Copyright (c) 2013년 bibim. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
