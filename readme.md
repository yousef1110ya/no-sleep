# Minimal `sleep` Utility — C + x86-64 Assembly (No libc)

## Overview

This repository contains a minimal command-line `sleep` implementation written in C with inline x86-64 assembly. The program intentionally avoids the C standard library and interfaces directly with the operating system via raw system calls.

The objective is not convenience or portability. The objective is **control**.

This project demonstrates:

- Direct syscall invocation
- A custom program entry point
- Manual argument handling
- Zero runtime or libc dependencies

**Target platform:** Linux only  
**Architecture:** x86-64

---

## Why This Exists

To be completely honest with you , I did this after seeing the safe-sleep that github action runner used

The code:

- Bypasses the C runtime entirely
- Defines its own `_start` entry point
- Implements syscall wrappers manually
- Manages stack alignment explicitly
- Handles strings, parsing, I/O, sleeping, and exit logic from scratch

This is about understanding what actually happens between process start and process exit — and owning every instruction along the way.

---

## Program Behavior

### Usage

```bash
sleep NUMBER

```
