# ofxCgalUtil
openFrameworks addon to bridge CGAL. Currently supporting Windows only.

## 0. About CGAL
* The Computational Geometry Algorithms Library [CGAL](https://www.cgal.org/)
  * build binaries along with the instruction [here](https://www.cgal.org/download/windows.html).
    * For now, this addon uses CGAL of x64 without Qt.
    * For compiling, Boost must be needed. openFrameworks also uses boost. To avoid conflict from difference of version or from duplication, replacing all file of lib in oF directory is recommended.
* Boost
  * Common but huge template library. CGAL has dependency on it.
  * It may be simpler to download binaries from [sourceforge](https://sourceforge.net/projects/boost/files/boost-binaries/) than to build from source by yourself.
  * openFrameworks itself also has the dependency on boost only for file-io which isn't sufficient to compile CGAL.

## 1. Build your project
* Locate CGAL files in `ofxCgalUtil\lib\`
* Replace boost libs and includes in `of_root\libs\boost` with files of the same version that you used to build CGAL.
* Using Project Generator(PG), update your oF project directory.
* If using Debug mode, you will need to set `\bigobj` option for compilation since CGAL and boost has so many template function.
  * `properties(configuration: Debug)` > `C/C++` > `All Options` > `Additional Options`, type `\bigobj`.


## 2. Liscene
* This repo: MIT license
* Boost: [Boost license](https://www.boost.org/users/license.html)
* CGAL: [LGPL & GPL license](https://www.cgal.org/license.html)
