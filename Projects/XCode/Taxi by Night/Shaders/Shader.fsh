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

/*

precision mediump float;

uniform sampler2D u_diffTex;

uniform vec3 u_specularColor;
uniform float u_opacity;
uniform float u_glossiness; // 0.0 - 64.0
uniform float u_specularLevel; // 0.0 - 10.0

varying vec2 o_coordsDiff;
varying vec3 o_normal;
varying vec3 o_lightDirection;
varying vec3 o_eyeDirection;

void main()
{
	vec3 normal = normalize(o_normal);
	vec3 lightDirection = normalize(o_lightDirection);
	vec3 eyeDirection = normalize(o_eyeDirection);
	
	vec3 halfVector = normalize(lightDirection + eyeDirection);
	
	float diffValue = max(dot(lightDirection, normal), 0.0);
	float specValue = pow(max(dot(halfVector, normal), 0.0), u_glossiness) * u_specularLevel;
	
	vec4 diffColor = texture2D(u_diffTex, o_coordsDiff);
	diffColor.xyz *= diffValue;
	diffColor.w *= u_opacity;
	diffColor.xyz += u_specularColor * specValue;
	
	gl_FragColor = diffColor;
}

*/
