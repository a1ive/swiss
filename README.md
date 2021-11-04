# Swiss -- Unix-in-a-box on Windows

Swiss is a Unix multitool that runs on Windows. It is a single binary that contains many of the basic core POSIX utilities, including a Bourne shell (sh), cp, mv, sed, and many more.

### Installation

No installation is necessary. The entire release is a single executable, and it makes no registry changes. Simply run `swiss` or `swiss sh` to fire up a shell. The swiss sh shell knows how to execute the other applications built into the binary. To specialize swiss into a particular utility, simply rename swiss.exe to that utility. For instance, copy `swiss.exe` to `sed.exe`, and it will always act directly as sed when run.

If you'd like to copy swiss out to each of its individual apps, run the following from a command prompt (assuming swiss.exe is accessible):

```
swiss.exe sh -c 'for app in `swiss.exe --list`; do cp -pv swiss.exe $app.exe ; done'
```

### Tools Included
* basename
* cat
* cecho (color echo)
* chmod
* cmp
* comm
* cp
* cut
* date
* dd
* diff
* dirname
* echo
* env
* expr
* find
* grep/egrep/fgrep
* head
* id
* install
* kill
* ln
* ls
* mkdir
* mktemp
* mv
* nl
* nproc
* od
* printf
* ps
* pwd
* reboot
* rm
* rmdir
* sed
* seq
* sh (Bourne shell compatible)
* sleep
* soko (Sokoban game)
* sort
* split
* sum
* tail
* tee
* test (aka [ )
* time
* touch
* tr
* true/false
* uname
* uniq
* wc
* xargs

### Notes About Paths on Windows
A couple of notes about how paths work in sh on Windows:
   * The separator character of the PATH environment variable in sh is a semicolon `;`, not the traditional Unix colon. This is because Windows uses colon characters as part of paths, a la `C:\Windows`. This may throw off some scripts, but many scripts that manipulate the path offer something like a PATH_SEPARATOR variable. See below for specific directions on "configure" style scripts.
   * Backslashes must be escaped in sh, like `\\` or `'\'`. Upon initialization, sh converts backslashes to forward slashes in the PATH variable. Automatic path completion in sh also delimits with forward slashes. We recommend using forward slashes in paths on sh wherever possible.
   * Swiss is a native app, and uses native paths rather than MSYS or cygwin style paths. Where MSYS might have a path like `/c/Windows/system32`, swiss simply uses paths like `C:/Windows/system32` or `/Windows/system32`, if you're already in the C: drive.

### Working with autoconf
Swiss is compatible enough to successfully run autoconf scripts. In fact we regularly build many packages, including binutils and GCC, using Swiss on Windows as part of Minoca's nightly automation. That said, it can be tricky to get autoconf to play nicely in Windows. Here are a few things we've learned.

* Make sure to copy out all the swiss binaries into their own executables. This is necessary because autoconf explicitly goes spelunking through the path looking for executables with names like sed and pwd. The command to copy out all the binaries is in the Installation section. Make sure that directory is in your PATH.
* A couple of extra binaries are usually needed by autoconf. The two most common (besides a compiler and make) are awk and m4. Make sure to find native versions of these, not MSYS or cygwin versions.

* Export the following variables prior to running a configure script:
```
export CONFIG_SHELL='sh' # Or the complete C:/path/to/my/sh.exe
export TMPDIR=`echo $TEMP | sed -e 's_\\\\_/_g'` # Sets TMPDIR to TEMP, converting backslashes to forward slashes.
export PATH_SEPARATOR=';'
export ac_executable_extensions='.exe .bat'
```
* If a configure script is misbehaving, check the output of config.log to find out exactly where it gave up. If you need more detail than that, run configure with the -x flag (sh -x ./configure ...). It prints out each line the shell executes, with line numbers.

### Compiling Swiss
Swiss should compile just fine on Windows with the basic MinGW toolset and either a pre-compiled version of swiss or something like git-bash for a build environment. Simply run 'make' in the source directory. Swiss is currently a 32-bit only binary. 64-bit compilation has not been tested.
Important Makefile variables:
* `CC` - Target compiler
* `AS` - Target assembler
* `RCC` - Resource compiler (Windows only).
* `SRCROOT` - The path to the source repository. Defaults to the current working directory.
* `OUTROOT` - The path to the build directory. Defaults to `$(SRCROOT)/out`.
* `CPPFLAGS` - Command line options passed to the C preprocessor.
* `CFLAGS` - Command line options passed to the C compiler.
* `LDFLAGS` - Command line options passed to the linker (CC).
* `ARCH` - Build architecture. Automatically detected, can be forced (in conjunction with CC) for cross-compilation.

### License
Swiss is licensed under GPLv3. Alternate licensing arrangements are available, contact us (below) for details. See the LICENSE file for complete information.
