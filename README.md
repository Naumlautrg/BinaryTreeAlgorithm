This program autocompletes words input by the user and allows for searching for words within a target language file.
With an internet connection, the user can also search definitions of any words listed in both the dictionary text file and the Free Dictionary API (https://dictionaryapi.dev/)

English word list file source https://github.com/dwyl/english-words<br>
Spanish word list file source https://github.com/xavier-hernandez/spanish-wordlist

This program requires three libraries/packages in order to successfully build and compile.<br>
Each library was installed using the package manager "vcpkg"

vcpkg install icu (for unicode)<br>
vcpkg install cpr (C++ requests, wrapper around libcurl for http requests)<br>
vcpkg install nlohmann-json (for reading json files, in our case the data provided from the Free Dictionary API)
