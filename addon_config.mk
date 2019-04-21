meta:
	ADDON_NAME = ofxCGAL
	ADDON_DESCRIPTION = An utility to bridge CGAL
	ADDON_AUTHOR = Ayumu Nagamatsu
	ADDON_TAGS = cgal
	ADDON_URL = https://github.com/nama-gatsuo/ofxCgalUtil

common:

vs:
	ADDON_INCLUDES += "boost_1_69_0\include"
	ADDON_INCLUDES += "CGAL-4.14-beta2\include"
	ADDON_INCLUDES += "CGAL-4.14-beta2\auxiliary\gmp\include"
	ADDON_LIBS += "CGAL-4.14-beta2\auxiliary\gmp\lib\libgmp-10.lib"
	ADDON_LIBS += "CGAL-4.14-beta2\auxiliary\gmp\lib\libmpfr-4.lib"
	ADDON_LIBS += "boost_1_69_0\libs\ "
	ADDON_LIBS += "CGAL-4.14-beta2\libs\ "
