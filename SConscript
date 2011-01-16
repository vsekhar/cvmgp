# add additional user code [sub]directories to this list, relative to the repository root

usrdirs = Split("""
.
""")

### END USER MODIFIABLES ###

lib_target  = 'vmgp'
subdirs = usrdirs

Import('env')
#env.Append(CPPPATH = ['include', '/usr/include/python3.1'])
env.Append(CPPPATH = [])
env.Append(LIBS = ['boost_thread'])
env.Append(CCFLAGS = ['-Wall', '-fmessage-length=0'])

globpatterns = [s+'/*.cpp' for s in subdirs]
filelist = map(Glob, globpatterns)
files = reduce(lambda x,y:x+y, filelist)

#lib = env.SharedLibrary(target = lib_target, source = files)
lib = env.Program(target = lib_target, source = files)
Default(lib)

