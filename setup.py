# ============================================================================
# Diplomarbeit - pysfstmorph/setup.py
# Copyright (C) 2008 Hendrik Buschmeier
# ============================================================================

from distutils.core import setup, Extension

_pysfstmorph = Extension(
    name = '_pysfstmorph',
    sources = [
        'pysfstmorph.cpp',
        'fst.cpp',
        'alphabet.cpp',
        'basic.cpp',
         'mem.cpp',
        'operators.cpp',
        'determinise.cpp',
        'utf8.cpp'],
    define_macros = [('SGIext', None)],
    language = 'c++'
)

setup(
    name = 'pysfstmorph',
    version = '1.0',
    description = 'An interface to Stuttgart Finite State Transducer (SFST).',
    author = 'Hendrik Buschmeier',
    author_email = 'hbuschme@FastMail.FM',
    ext_modules = [_pysfstmorph],
    license = 'GNU General Public License, Version 2 or higher',
)