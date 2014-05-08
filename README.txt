wiresting
=========

Overview
--------

Packet injection utility, using libpcap.

Wiresting is essentially a libpcap translation of wirefang.

Wiresting reads bytes from a file and then writes those bytes to the data link 
layer (layer 2) of a network interface.

Compatibility
-------------

    * Linux
    * Unix
    * OS X

Installation
------------

Full installation of wiresting is a 2 step process. However, the second step is 
optional.

Firstly, navigate to the src directory and run the following command:

    $ bash build.sh

Once this has completed, you can run wiresting by navigating to the bin 
directory and running the following command:

    # ./wiresting

Secondly, and optionally, you can install wiresting system-wide by copying the 
contents of the bin directory into your path. For example, you could execute a 
command such as:

    # cp bin/* /usr/local/bin/

License
-------

Copyright (c) 2014 Damian Jason Lapidge

Licensing terms and conditions can be found within the file LICENSE.txt.

