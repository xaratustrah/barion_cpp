# barion
<sup> (c) Copyright M. Shahab SANJARI 2014 </sup>

![barion](https://raw.githubusercontent.com/xaratustrah/barion/master/rsrc/icon128.png)

## About

**barion** is a program for the display of scientific information and 
calculations related to periodic table of elements used specifically in the field
of accelerator physics and related sciences. Specifically this program can be used 
in experiments involving mass and lifetime measurements of radioactive ion beams. 
In essence, this program provides a convenient interface to the published data on
atomic masses in the world famous  **Atomic Mass Evaluation by G. Audi and 
colleagues**. It can be used in a variety of applications such as medical radio 
therapy, astrophysics and fundamental physics research, etc. One can perform

- Identification of nuclides 
- Settings of accelerator parameters specially the storage rings
- Design and analysis of beam monitors specially Schottky detectors
- And many more...

## License

barion in its bare form as a code, is distributed under GNU GPL License (see below).
The optional binary release bundle additionally contains the **AME2012 database** 
and binary versions of the **ROOT library** developed at CERN which are needed for the program to run. Different license agreements apply to these as described below:

#### The code

barion is free software: you can redistribute it and/or modify it under the 
terms of the GNU General Public License as published by the Free Software 
Foundation, either version 3 of the License, or (at your option) any later 
version.

barion is distributed in the hope that it will be useful, but WITHOUT ANY 
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with 
barion.  If not, see <http://www.gnu.org/licenses/>.

#### The binary release bundle

The binary release is created for convenience and ease of use. Within the 
binary bundle, a binary version of the needed **ROOT libraries** are packed, so that 
they are linked dynamically with the program at the run time. This program does 
not manipulate or change any code from the ROOT library, and as such it is a 
program that *solely uses the ROOT library*. It should be brought to your 
attention that the complete source code of the ROOT library is available under 
<http://root.cern.ch/drupal/> which is in turn released under the terms of LGPL 
as described in <http://root.cern.ch/drupal/content/license>. For any inquiries
related to **ROOT** please refer to the above mentioned website.

The atomic mass evaluation **AME2012** database is copyrighted material. A 
modified version is included in the binary bundle **with kind permission of 
G. Audi and colleagues**. This program makes NO CLAIMS OF CORRECTNESS OF THE 
DATA AND CALCULATION VALUES WHAT SO EVER, and all works are referred to the 
original publication as the only complete and correct reference:

'G. Audi et al 2012 Chinese Phys. C 36 1287'
<http://dx.doi.org/10.1088/1674-1137/36/12/003>


## Compilation from Source

#### Prerequisites

This program was tested to work under Linux and OSX. It should in principle also
compile under CygWin, but the author didn't check this possibility. A compilation
needs:

- A C++ build environment including usual tools (Make, xxd, sed, ...)
- ROOT Library - *root-config* and *rootcint* executables must be in **PATH**

A local compilation of the ROOT library would suffice. Please follow the 
instructions on ROOT Homepage
<http://root.cern.ch/drupal/content/installing-root-source>
in order to build root. The best would be to use the **git** repository in order 
to keep up to date with the developments. After a successful compilation, you 
should run the script provided by ROOT in order to set the **PATH** variables:

`/path/to/root/bin/thisroot.sh`

Now you are ready for compilation. First get the repositoty 

`git clone https://github.com/xaratustrah/barion`

and then type `make`. For a complete installation for example in a system directory, you may type

`
PREFIX=./path/to/prefix make all db install
`

You also have the possibility to make a symlink in a system directory by

`make symlink`

#### Building the Database

First you need to download the database file **mass12.mass** from the [AME & 
AMDC Homepage](http://amdc.impcas.ac.cn/evaluation/data2012/ame.html). Use the 
helper script *ame_data_extractor.rb* to extract the data like as follows:

`ruby ./ame_data_extractor.rb mass.mass12 > mass12.modified`

Then run the program with the -c option to create the binary database:

`./barion -c mass12.modified`

A file with the name of *database.root* will be created. You may remove the files 
*mass12.mass* and *mass12.modified* since they are no longer needed by the program.

Alternatively you can use the makefile to do the above procedure. Just type:

`make db`

and the rest is done automatically.

## Usage

The program can either be started using the application release bundle under OSX. 
Alternatively on all systems, the program can be started using a command line.
The program accepts three command line patterns:

- Like mentioned above for creating the database `./barion -c mass12.modified`
- By explicitly choosing a database file `./barion PATH/TO/database.root`
- Or just without any options `./barion`, in case the database file is in the current directory.

After the program finds the database file, it will start with a graphical window. The 
program interface allows for navigation around the nuclidic chart and calculation 
of values related with proper settings. The number entry fields can be changed 
by their buttons. Here one can use **shift** or **ctrl** or both to accelerate the 
increment step.




