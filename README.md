# The practice part of a webinar with an example of how to use MongoDB C++ API.

This program creates a MongoDB database and inserts some data, and searches for some data by criteria.

It uses http://mongocxx.org/mongocxx-v3/tutorial/ as a base example, but another dataset. Please refer to the tutorial too.

The full reference is available at: https://mongodb.github.io/mongo-cxx-driver/api/current

The file implements example "how to create database and put data into it".

## Build

It uses [Conan package manager](https://conan.io/) to install dependencies.

### Install dependencies

```bash
$ mkdir build && cd build
$ conan install ..
$ cmake ..
```

On error "BinaryMissing" try:
```bash
$ conan install .. --build=missing
```

### Build executable

Run inside "build" directory:
```bash
$ cmake --build .
```

Look for your executable in "build/bin"

## Usage

```bash
$ mongodb_demo < create | update | query >
```
