//
//  Shader.vsh
//  Taxi by Night
//
//  Created by Majak on 12/03/14.
//  Copyright (c) 2014 Semi-Serious Games. All rights reserved.
//

attribute vec4 position;
attribute vec3 normal;

varying lowp vec4 colorVarying;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    vec3 eyeNormal = normalize(normalMatrix * normal);
    vec3 lightPosition = vec3(0.0, 0.0, 1.0);
    vec4 diffuseColor = vec4(0.4, 0.4, 1.0, 1.0);
    
    float nDotVP = max(0.0, dot(eyeNormal, normalize(lightPosition)));
                 
    colorVarying = diffuseColor * nDotVP;
    
    gl_Position = modelViewProjectionMatrix * position;
}

/*

attribute vec3 a_position;
attribute vec2 a_coordsDiff;
attribute vec3 a_normal;

uniform mat4 u_worldMatrix;
uniform mat4 u_viewProjMatrix;
uniform vec3 u_lightPosition;
uniform vec3 u_eyePosition;

varying vec2 o_coordsDiff;
varying vec3 o_normal;
varying vec3 o_lightDirection;
varying vec3 o_eyeDirection;

void main()
{
	o_coordsDiff = a_coordsDiff;
	
	vec4 worldPosition = u_worldMatrix * vec4(a_position, 1.0);
	o_normal = mat3(u_worldMatrix) * a_normal;
	
	o_lightDirection = u_lightPosition - worldPosition.xyz;
	o_eyeDirection = u_eyePosition - worldPosition.xyz;
	
	gl_Position = u_viewProjMatrix * worldPosition;
}

*/