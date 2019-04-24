meta:
	ADDON_NAME = ofxCGAL
	ADDON_DESCRIPTION = An utility to bridge CGAL
	ADDON_AUTHOR = Ayumu Nagamatsu
	ADDON_TAGS = cgal
	ADDON_URL = https://github.com/nama-gatsuo/ofxCgalUtil

common:

vs:
	ADDON_INCLUDES += "lib\CGAL-4.14\include"
	ADDON_INCLUDES += "lib\CGAL-4.14\auxiliary\gmp\include"

	ADDON_LIBS     += "lib\CGAL-4.14\auxiliary\gmp\lib\libgmp-10.lib"
	ADDON_LIBS     += "lib\CGAL-4.14\auxiliary\gmp\lib\libmpfr-4.lib"
	ADDON_LIBS     += "lib\CGAL-4.14\libs\ "

	ADDON_DLLS_TO_COPY += "lib\CGAL-4.14\bin\CGAL-vc140-mt-gd-4.14.pdb"
	ADDON_DLLS_TO_COPY += "lib\CGAL-4.14\bin\CGAL-vc140-mt-gd-4.14.dll"
	ADDON_DLLS_TO_COPY += "lib\CGAL-4.14\bin\CGAL-vc140-mt-4.14.dll"
	ADDON_DLLS_TO_COPY += "lib\CGAL-4.14\auxiliary\gmp\lib\libgmp-10.dll"
	ADDON_DLLS_TO_COPY += "lib\CGAL-4.14\auxiliary\gmp\lib\libmpfr-4.dll"
