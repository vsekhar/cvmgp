# add additional user code [sub]directories to this list, relative to the repository root

usrdirs = Split("""
src
""")

### END USER MODIFIABLES ###

lib_target  = '_vmgp'
subdirs = usrdirs

Import('env')
env.Append(CPPPATH = ['include', '/usr/include/python3.1'])
env.Append(LIBS = ['boost_thread', 'boost_python3'])
env.Append(CCFLAGS = ['-Wall', '-fmessage-length=0'])

globpatterns = [s+'/*.cpp' for s in subdirs]
filelist = map(Glob, globpatterns)
files = reduce(lambda x,y:x+y, filelist)

lib = env.SharedLibrary(target = lib_target, source = files, SHLIBPREFIX='')
#lib = env.Program(target = lib_target, source = files)
Default(lib)

