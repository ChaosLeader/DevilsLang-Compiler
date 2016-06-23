# DevilsLang Compiler
Compiler for DevilsLang. Requires [DevilsLang Framework](https://github.com/ChaosLeader/DevilsLang-Framework).

This project is still in early development. As alwasys, code first, think later. So please bare with me.

## Table of Contents
 - [Language](#language)
 - [Compiler](#compiler)
 - [Framework](#framework)

### Language:
DevilsLang is based on elements from popular languages such as:

 - C++
 - C#
 - Go
 - Python

DevilsLang is designed to write gamehacks, shellcode, ...

### Compiler
#### How to compile
```bash
$ ./compiler DevilsLang Test.Test
```
where `DevilsLang` is the path to [DevilsLang Framework](https://github.com/ChaosLeader/DevilsLang-Framework). `Test.Test` is package & class name containing the entrypoint function.

### Framework
#### Aim
This framework aims to support gamehacking. Contains detour manager, renderer & menu handler.
#### Packages
 - [System](https://github.com/ChaosLeader/DevilsLang-Framework/tree/master/System)
 - [System.Collections](https://github.com/ChaosLeader/DevilsLang-Framework/tree/master/System/Collections)