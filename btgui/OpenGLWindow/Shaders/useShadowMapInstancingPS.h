//this file is autogenerated using stringify.bat (premake --stringify) in the build folder of this project
static const char* useShadowMapInstancingFragmentShader= \
"#version 330 core\n"
"//precision highp float;\n"
"\n"
"in Fragment\n"
"{\n"
"     vec4 color;\n"
"} fragment;\n"
"\n"
"in Vert\n"
"{\n"
"	vec2 texcoord;\n"
"} vert;\n"
"\n"
"uniform sampler2D Diffuse;\n"
"uniform sampler2DShadow shadowMap;\n"
"\n"
"in vec3 lightDir,normal,ambient;\n"
"in vec4 ShadowCoord;\n"
"\n"
"out vec4 color;\n"
"\n"
"\n"
"\n"
"void main(void)\n"
"{\n"
"    vec4 texel = fragment.color*texture(Diffuse,vert.texcoord);//fragment.color;\n"
"	vec3 ct,cf;\n"
"	float intensity,at,af;\n"
"	intensity = max(dot(lightDir,normalize(normal)),0);\n"
"	cf = intensity*vec3(1.0,1.0,1.0)+ambient;\n"
"	af = 1.0;\n"
"		\n"
"	ct = texel.rgb;\n"
"	at = texel.a;\n"
"		\n"
"	float bias = 0.005f;\n"
"	float visibility = texture(shadowMap, vec3(ShadowCoord.xy,(ShadowCoord.z-bias)/ShadowCoord.w));\n"
"	\n"
"	color  = vec4(ct * cf * visibility, at * af);	\n"
"}\n"
"\n"
;
