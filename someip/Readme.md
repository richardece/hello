SOME/IP

Reference:
https://github.com/COVESA/vsomeip/wiki/vsomeip-in-10-minutes#prep
https://github.com/COVESA/vsomeip

Pre-requisites:
1. Install boost 1.55 
	$ wget -O boost_1_55_0.tar.gz https://sourceforge.net/projects/boost/files/boost/1.55.0/boost_1_55_0.tar.gz/download
	$ tar xzvf boost_1_55_0.tar.gz
	$ cd boost_1_55_0/
	$ ./bootstrap.sh --prefix=/usr/
	$ ./b2
	$ sudo ./b2 install
2. Install vsomeip
    $ git clone https://github.com/COVESA/vsomeip.git 
    $ cd vsomeip
    $ git checkout tags/2.14.16
    $ mkdir build && cd build
    $ cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr/ -DCMAKE_PREFIX_PATH=vsomeip -DENABLE_SIGNAL_HANDLING=1 ..
    $ make && make install

3. To run dashboard project (with json file), need to install qt creator
    - download isntaller from https://download.qt.io/archive/qtcreator/4.11/4.11.1/
    $ sudo apt-get install qtdeclarative5-dev qml-module-qtquick-controls
    $ sudo apt-get install -y qml-module-qtquick-extras
    Now vehicle simulator and dashboard are running in intel NUC PC. just need to configure json file (IP{ address}) .!


Improvements:
1.  Boost 1.55 is not available in Conan. Closest version in Conan is 1.69 but it seems that it does not have all the components. Need to upload version 1.55 to Conan
2. Vsomeip must be uploaded to Conan also. Tag 3.1.20.3 cannot be compiled.
3. Wireshark does not seem to see the packets inside parallels ubuntu 20.04. 
    1. Try running the sample code in intel nuc. 
    - still cannot detect some/ip packets
    2. Try running sample code in Mac. 
    - could not even install boost 1.55; Mac is not supported by someip
    3. Perhaps what happened is that the sample code that we run is just using D-bus for local communiation. It uses the socket communication, so there is no packet to be captured by Wireshark. Try an example that run on two different computers. or anything that uses json configuration files

    To use json file,
    $ export VSOMEIP_CONFIGURATION=path_to_json_file
    unicast = host ip address
    Not sure what to put to multicast

    There is an example that uses json file from https://github.com/COVESA/vsomeip/tree/master/examples/hello_world
    - tried to run server in nuc and client in parallels.
    - the 2 cannot see each other
    - parallels can ping nuc, but nuc cannot ping parallels
    - try using another real pc, or change parallels network connection to enpos
        - might need to do this:
        #!/bin/bash
        route add -host 224.224.224.245 dev <interface>
        export VSOMEIP_CONFIGURATION=<config_file>
        export VSOMEIP_APPLICATION_NAME=<application_name>
        ./<executable>
        - or use something like:
        env VSOMEIP_CONFIGURATION=../helloworld-local.json \
        VSOMEIP_APPLICATION_NAME=hello_world_service \
        ./hello_world_service
    - now trying hello-world example using parallels ubuntu 18. this one can ping to nuc and vice versa
        - still can't see each other
        - is it because the instrauction says "must be run in the same machine"?
            - try the other example(request/response, subscribe/notify), had to modify the CmakeLists.txt
            - this example is supposed to work in 2 machines
                - did not work