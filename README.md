# Undecided-Name

## How to install & compile for Windows

### Step 1: Clone repository

You can either go File -> Download .zip to download the repository. Otherwise if you have Git, you can enter this command:
``git clone https://github.com/mangathemango/Operation-Null-Mind/``

### Step 2: Install cmake and MingW.

These should be available with a Google search. Afterwards, you can run `cmake --version` and `gcc --version` to verify.

### Step 3: Build, Compile and Run

To build, there are 2 ways you can do this

If you have vscode, just `Ctrl+Shift+B`. It should all run fine.

Otherwise, you can run these 3 commands:

```
cmake -S . -B build "MinGW Makefiles"
cmake --build build
```

Right now, the .exe file should be inside the `build/` folder, which you can run straight away

```
./build/Operation-Ruinam-Dei
```

#### Note:

Sometimes github does a weird thingy where the .c files turn into .C, which, automatically detects it as a C++ file instead of C @v@ goofy ah.

In that case, you can enter this command into terminal:

```
Get-ChildItem -Path .\src -Filter *.C -Recurse | Rename-Item -NewName {$_.name -replace '\.C$','.c'}
```

Ctrl + Alt + I = Open up Github copilot.

Explaining errors = /explain #terminalLastComment