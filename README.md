# pysfstmorph

Copyright (C) 2008 Hendrik Buschmeier, <hbuschme@uni-bielefeld.de>

pysfstmorph is a Python interface to the Stuttgart Finite State Transducer[^sfst]
(SFST). pysfstmorph consists of two parts: (1) A C++ Python extension, which
wraps the original SFST C++ sources (2) A Python class ("Transducer") for easy
access to the extension.

pysfstmorph provides only a very limited interface to SFST. In fact, it only
allows access to the morphological analysis and generation capabilities.
pysfstmorph makes use of transducers for computational morphology (e.g.,
SMOR), which are build with the SFST C++ tools fst-compiler, fst-compact.

[^sfst]: http://www.ims.uni-stuttgart.de/projekte/gramotron/SOFTWARE/SFST.html


## Installation and Build Instructions

1. Download SFST from [1] and extract it somewhere.
   - Compile SFST [optional]
   - Build morphological transducers (SMOR, XMOR, ...) [optional]
2. Copy the pysfstmorph files pysfstmorph.cpp, pysfstmorph_prepare_install.sh,
   pysfstmorph.patch and setup.py to the directory SFST/src.
3. Run ./pysfstmorph_prepare_install.sh; This will create symbolic links with
   the extension .cpp instead of .C for some SFST source files and  patches
   mem.h.
4. Run python setup.py build to compile the _pysfstmorph Python extension.
5. From the directory SFST/src/build/lib.../ copy the created shared object
   _pysfstmorph.so to wherever you want the pysfstmorph module to be located
   (e.g., the python site-packages directory or the place where you want to
   work with pysfstmorph). Also copy the file pysfstmorph.py to that location.


## A Sample Program

```python
>>> from pysfstmorph import Transducer
>>> t = Transducer('/Users/hendrik/bin/SFST/data/SMOR/smor.a')
>>> t.analyse('Kardinal)
	['Kardinal<+NN><Masc><Akk><Sg>', 'Kardinal<+NN><Masc><Nom><Sg>',
	 'Kardinal<+NN><Masc><Dat><Sg>']
>>> t.generate('Kardinal<+NN><Masc><Dat><Sg>')
	['Kardinal', 'Kardinale']
>>> t.clean_up()
```



## License

pysfstmorph is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
