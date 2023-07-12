# Balancing-Scale-Solution
This repo contains solution to the balancing scale problem


***BalancingScale.cpp*** contains 2 map: m_InputDataMap, used to store the input data from a flat file. Data is stored as key-pair format, where, key = scalename and value is pair of left and right wts along with a marker to identify whether the node is balanced or not.

m_OutputDataMap, used to store the output data, which is then used to display to the system output.

parseAndStoreTokens is used to read the data from flat file and stores the tokenised data in m_InputDataMap. balanceScale is the function where the balancing of node happens and updates the m_OutputDataMap. iterateInputDataMap is used to iterate through the input map and inturn invokes balanceScale function.

***InputScaleData.txt*** is the file which contains input data. This file is specified by the user at runtime. The data is read from this file and the same gets processed by the executable.


The  ***Build.jpg*** file contains screenshot after successfull build
The ***Run_1.jpg*** file is screenshot once the executable file is run. It asks for the input filename to be processed.
The ***OutputAfterFileInput.jpg*** contains the actual output. After the input file is processed it displays the balanced output.


***VS_ConsoleApp_Windows.exe*** is the executable file
