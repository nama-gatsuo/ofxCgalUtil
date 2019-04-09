meta:
	ADDON_NAME = ofxCGAL
	ADDON_DESCRIPTION = An utility to bridge CGAL
	ADDON_AUTHOR = Ayumu Nagamatsu
	ADDON_TAGS = cgal
	ADDON_URL = https://github.com/nama-gatsuo/ofxCgalUtil

common:

vs:
	ADDON_INCLUDES += "$(CGAL_DIR)\auxiliary\gmp\include"
	ADDON_INCLUDES += "$(BOOST_INCLUDEDIR)"
	ADDON_INCLUDES += "$(CGAL_DIR)\build\include"
	ADDON_INCLUDES += "$(CGAL_DIR)\include"

	ADDON_LIBS += "$(CGAL_DIR)\auxiliary\gmp\lib\libgmp-10.lib"
	ADDON_LIBS += "$(CGAL_DIR)\auxiliary\gmp\lib\libmpfr-4.lib"
	ADDON_LIBS += "$(CGAL_DIR)\build\lib\ "
	ADDON_LIBS += "$(BOOST_LIBRARYDIR)\ "
