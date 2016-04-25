# ============================================================================
# Diplomarbeit - pysfstmorph_prepare_install.sh
# Copyright (C) 2008 Hendrik Buschmeier
# ============================================================================

# Symlink the following .cpp to the corresponding .C files
ln -s fst.C fst.cpp
ln -s alphabet.C alphabet.cpp
ln -s basic.C basic.cpp
ln -s mem.C mem.cpp
ln -s operators.C operators.cpp
ln -s determinise.C determinise.cpp
ln -s utf8.C utf8.cpp

# Patch the file mem.h
patch -p0 < pysfstmorph.patch