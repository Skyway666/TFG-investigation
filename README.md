# Introduction

Welcome to the Wiki of Mirror, a reflection tool for C++ build by [Lucas García Mateu](https://github.com/Skyway666).

Mirror is a light weight tool, which parses the C++ headers in your code base to then generate C++ code which you can use in your program. It has been build as a Final Degree project for the Balcheor's degree in [Videogame Design and Development](https://www.citm.upc.edu/ing/estudis/graus-videojocs/).

# What is reflection?

Briefly summarized, reflection data is the the information regarding the structure of objects in a program. For more information, feel free to check out the [Memory](https://drive.google.com/file/d/1o4Awh5tqd6IOLrl5_n9FtD0Ba6mU4gCz/view?usp=sharing) developed for this project, where you can also find insights on the development and internal structure of the tool.

# What can I use reflection for?

Reflection in C++, allows us to treat objects as containers, taking advantage of the time that we invest in structuring our data when it is time to use all of it as a single package. Take a look at some of the following examples:

- **Serialization**: Serialization code becomes compact and universal.
- **UI painting**: With a procedural UI system, such as [ImGui](https://github.com/ocornut/imgui), we could easily display pannels that display all the data within an object.
- **Scripting system**: If we wanted to build a C++ scripting system, such as the one featured by Unreal, we should surely need some kind of reflection system, since we need to know which varibles the user will want to set in the editor.
- **Networking**: When we send information through the net, we only get raw memory if we are using C++, and we need to spend time making sense of it. With serialization, this process could also be sped up.

As you can see, serialization is meant to make the coder's lives easier, saving time and leaving a cleaner and less verbose code.

# How does Mirror work?

Mirror is both a **library** and a **tool**. At first, you will need to run a program, which will parse the header files in your project and store the reflection data of your objects (properties and methods). 

Then, the same program will generate files with C++ code to be used in your project. Said code, when executed, will fill a set of C++ objects which will contain the previously parsed reflection data. Finally, since the objects are part of your application, you can use the data and methods at will to implement reflective code.

Parse C++, to generate C++ to reflect C++. All of it coded in C++.

# Want to get started?

If you like what you just heard, and would like to see yourself in the Mirror, head to the following page, where I will teach you [how to install and use the tool](https://github.com/Skyway666/TFG-investigation/wiki/Tool-usage).

# License

Mirror is licensed under the [MIT standard](https://choosealicense.com/licenses/mit/)

MIT License

Copyright (c) 2020 Lucas García Mateu

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.



