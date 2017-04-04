#!/bin/python

env = Environment(CPPPATH='#/build/include')
env.Append(CXXFLAGS = ['-Wall', '-Wextra', '-Wpedantic', '-O3', '-std=c++14'])

# Define the name of the main executable
appname = 'simulation'

VariantDir('build/include', 'include', duplicate=1)
SConscript('build/include/SConscript', 'env')
VariantDir('build/src', 'src', duplicate=1)
SConscript('build/src/SConscript', 'env')
VariantDir('build/tests', 'tests', duplicate=1)
SConscript('build/tests/SConscript', 'env')

