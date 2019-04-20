# ofxCgalUtil
openFrameworks addon to bridge CGAL. Currently supporting Windows only.

## 0. About CGAL
* The Computational Geometry Algorithms Library [CGAL](https://www.cgal.org/)
  * This repo contains pre-compiled lib files
* Boost
  * Since this repo doesn't contain lib files from boost, compiled lib files should be located in `boost_xx/`.
  * It may be simpler to download binaries from [sourceforge](https://sourceforge.net/projects/boost/files/boost-binaries/) than to build from source by yourself.
  * openFrameworks has the dependency on boost but it's only about file-io and isn't sufficient to compile CGAL.

## 1. Build your project
* Using Project Generator(PG), update your oF project directory.
* Change the order of the list on `properties` > `C/C++` > `General` > `Additional Include Directories` to have the boost path upper than `%(AdditionalIncludeDirectories)`. Otherwise, you can't build because of conflict coming from Boost version of oF's and one used by CGAL.
