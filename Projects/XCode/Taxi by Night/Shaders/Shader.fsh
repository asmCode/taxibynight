//
//  Shader.fsh
//  Taxi by Night
//
//  Created by Majak on 12/03/14.
//  Copyright (c) 2014 Semi-Serious Games. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
