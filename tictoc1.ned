//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


simple Txc1
{
    parameters:
        double delay = default(0.3)   //parameter with a default value
        //changing style from tutorial
        @display("i=block/routing");
    gates:
        input in;
        output out;
}

//
// Adding module parameters.
//
network Tictoc1
{
    submodules:
        tic: Txc1 {
            parameters:
                //changing style from tutorial
                @display("i=,cyan");
        }
        toc: Txc1 {
            parameters:
                //changing style from tutorial
                @display("i=,gold");
        }
    connections:
        tic.out --> {  delay = 100ms; } --> toc.in;
        tic.in <-- {  delay = 100ms; } <-- toc.out;
}