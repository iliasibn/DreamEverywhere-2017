   const char*	fragmentSource =
            "#version 130 \n"
            "uniform sampler2D textureA; \n"		// UYVY macropixel texture passed as RGBA format
            "uniform sampler2D textureB; \n"		// UYVY macropixel texture passed as RGBA format
            "uniform sampler2D textureC; \n"		// UYVY macropixel texture passed as RGBA format


            "uniform float alphacoef; \n" //coefficient de transformation en mix
            "uniform int beta; \n" //second coefficient de transformation en mix : en général 1-alpha
               "uniform int seuil; \n" //seuil pour les incrustations
               "uniform int tolerance; \n" //tolerance pour les incrustations
               "uniform vec3 couleurincrust; \n" //Couleur pour l'incrustation
               "uniform int mode; \n" //0 pour un mix, 1 pour une chroma, 2 pour une luma


            "vec4 fairedurgb(sampler2D UYVYtex) \n"
            "{\n"
            "	float tx, ty, Y, Cb, Cr, r, g, b; \n"
                            "	tx = gl_TexCoord[0].x; \n"
                            "	ty = gl_TexCoord[0].y; \n"
                            "	int true_width = textureSize(UYVYtex, 0).x * 2; \n"
                            "	if (fract(floor(tx * true_width + 0.5) / 2.0) > 0.0) \n"
                            "		Y = texture2D(UYVYtex, vec2(tx,ty)).a; \n"		// odd so choose Y1
                            "	else \n"
                            "		Y = texture2D(UYVYtex, vec2(tx,ty)).g; \n"		// even so choose Y0
                            "	Cb = texture2D(UYVYtex, vec2(tx,ty)).b; \n"
                            "	Cr = texture2D(UYVYtex, vec2(tx,ty)).r; \n"
                            "	Y = (Y * 256.0 - 16.0) / 219.0; \n"
                            "	Cb = (Cb * 256.0 - 16.0) / 224.0 - 0.5; \n"
                            "	Cr = (Cr * 256.0 - 16.0) / 224.0 - 0.5; \n"
                            "	r = Y + 1.5748 * Cr; \n"
                            "	g = Y - 0.1873 * Cb - 0.4681 * Cr; \n"
                            "	b = Y + 1.8556 * Cb; \n"
            // Set alpha to 0.7 for partial transparency when GL_BLEND is enabled
            "	return vec4(r, g, b, alphacoef); \n"
            "}\n"

            "void main(void) \n"
            "{\n"

            "vec4 texa; \n"
            "vec4 texb; \n"
            "texa=fairedurgb(textureA); \n"
            "texb=fairedurgb(textureB); \n"
            "	gl_FragColor = mix(texa,texb, alphacoef); \n"
            "}\n";
