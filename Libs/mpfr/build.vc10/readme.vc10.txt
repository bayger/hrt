======================
A. A Note On Licensing
======================

Where files in this distribution have been derived from files licensed
under Gnu GPL or LGPL license terms, their headers have been preserved 
in order to ensure that these terms will continue to be honoured.  

Other files in this distribution that have been created by me for use
in building MPIR and MPFR using Microsoft Visual Studio 2010 are 
provided under the terms of the LGPL version 2.1

Running the MPFR tests automatically uses Python, which must hence be 
installed if you want to run them.  

=============================================
B. Compiling MPFR with the Visual Studio 2010
=============================================

The VC++ project files are intended for use with Visual Studio 
2010 Professional, but they can also be used with Visual C++ 2010 
Express to build win32 applications. If the WIndows 7.1 SDK is 
installed, the Express version can also build the 64-bit versions. 

Building MPFR
-------------

These VC++ build projects are based on MPIR 2.0 and MPFR-3.0.0. It
is assumed that MPIR has already been built and that the directories
containing MPIR and MPFR are at the same level in the directory 
structure:

    mpir
        build.vc10
            dll     MPIR Dynamic Link Libraries 
            lib     MPIR Static Libraries
            ....
    mpfr
        build.vc10
            dll     MPFR Dynamic Link Libraries
            lib     MPFR Static Libraries
            ....

The root directory name of the MPIR version that is to be used in 
building MPFR should be 'mpir' with any version number such as in
'mpir-3.0' removed.
 
The MPFR source distribution should be obtained and expanded into the
MPFR root directory (e.g. mpfr-3.0.0). After this the build project 
files should be added so that the build.vc10 sub-directory is in the
MPFR root directory as shown above.  After this the root directory 
should be renamed to 'mpfr'.

The root directory names 'mpir' and 'mpfr' are used because this makes 
it easier to use the latest version of MPIR and MPFR without having to 
update MPIR and MPFR library names and locations when new versions are 
released.
        
There are two build projects, one for static libraries and one for 
dynaimic link libraries:

    dll_mpfr.sln    for dynamic link libraries
    lib_mpfr.sln    for static libraries

After loading the appropriate solution file the Visual Studio IDE allows
the project configuration to be chosen:

    win32 or x64
    release or debug
    
after which the lib_mpfr library should be built first, followed by 
lib_tests and then the tests.

If you wish to use the Intel compiler, you need to convert the build files
by right clicking on the MPFR top level Solution and then selecting the 
conversion option.

Any of the following projects and configurations can now be built:

    dll_mpfr    the DLL (uses the MPIR DLL) 
      Win32
        Debug
        Release
      x64
        Debug
        Release

    lib_mpfr    the static library (uses the MPIR static library) 
      Win32
        Debug
        Release
      x64
        Debug
        Release

Test Automation
----------------

Once the tests have been built the Python scripts run_dll_tests.py or
run_lib_tests.py found in the build.vc10 folder can be used to run the
tests (if Python is not installed the tests have to be run manually).

Notes
-----

The SVN version of MPFR has source code that is not in the current 
release (ai2.c). It also has a test - tstdint - that is not in this
release.  The file ai2.c is listed in this build but it has been
excluded in the Visual Studio solution explorer. The tstdint has 
also been included but its output is not relevant for the MPFR
release. 

===================
C. Acknowledgements
===================

My thanks to:

1. The GMP team for their work on GMP and the MPFR team for their work 
   on MPFR
2. Patrick Pelissier, Vincent Lefèvre and Paul Zimmermann for helping
   to resolve VC++ issues in MPFR.
3. The MPIR team for their work on the MPIR fork of GMP.
4  Jeff Gilcrist for his help in testing, debugging and improving the
   readme.txt file giving the build instructions
 
       Brian Gladman, February 2011
